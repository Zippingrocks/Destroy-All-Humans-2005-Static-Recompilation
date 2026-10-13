#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "dah_run_evidence.h"

static char evidence_directory[MAX_PATH];
static char evidence_run_id[96];
static char evidence_started_utc[32];
static uint64_t evidence_executable_hash;

static void dah_evidence_json_string(FILE *file, const char *text)
{
    fputc('"', file);
    for (; text && *text; ++text) {
        unsigned char value = (unsigned char)*text;
        if (value == '"' || value == '\\') fputc('\\', file);
        if (value >= 32u) fputc(value, file);
    }
    fputc('"', file);
}

int dah_run_evidence_path(char *destination, size_t capacity,
                          const char *filename)
{
    int written;
    if (!destination || !capacity || !filename || !evidence_directory[0])
        return 0;
    written = snprintf(destination, capacity, "%s\\%s",
                       evidence_directory, filename);
    return written > 0 && (size_t)written < capacity;
}

const char * dah_run_evidence_directory(void)
{
    return evidence_directory;
}

void dah_run_evidence_update_status(const char *status,
                                    const char *log_path,
                                    const char *event_path)
{
    char session_manifest[MAX_PATH];
    const char *paths[2];
    FILE *files[2];
    unsigned index;
    if (!dah_run_evidence_path(session_manifest, sizeof(session_manifest),
                               "manifest.json"))
        return;
    paths[0] = session_manifest;
    paths[1] = "dah_current_run.json";
    files[0] = fopen(paths[0], "wb");
    files[1] = fopen(paths[1], "wb");
    for (index = 0; index < 2u; ++index) {
        FILE *file = files[index];
        if (!file) continue;
        fprintf(file, "{\n  \"schema\": 2,\n  \"runId\": ");
        dah_evidence_json_string(file, evidence_run_id);
        fprintf(file, ",\n  \"pid\": %lu,\n  \"startedUtc\": ",
                GetCurrentProcessId());
        dah_evidence_json_string(file, evidence_started_utc);
        fprintf(file,
                ",\n  \"executableFnv1a64\": \"%016llX\","
                "\n  \"evidenceDirectory\": ",
                (unsigned long long)evidence_executable_hash);
        dah_evidence_json_string(file, evidence_directory);
        fprintf(file, ",\n  \"logPath\": ");
        dah_evidence_json_string(file, log_path);
        fprintf(file, ",\n  \"eventTracePath\": ");
        dah_evidence_json_string(file, event_path);
        fprintf(file, ",\n  \"anomalyPath\": ");
        {
            char anomaly_path[MAX_PATH];
            if (dah_run_evidence_path(anomaly_path, sizeof(anomaly_path),
                                      "anomalies.jsonl"))
                dah_evidence_json_string(file, anomaly_path);
            else
                dah_evidence_json_string(file, "");
        }
        fprintf(file, ",\n  \"summaryPath\": ");
        {
            char summary_path[MAX_PATH];
            if (dah_run_evidence_path(summary_path, sizeof(summary_path),
                                      "summary.json"))
                dah_evidence_json_string(file, summary_path);
            else
                dah_evidence_json_string(file, "");
        }
        fprintf(file, ",\n  \"status\": ");
        dah_evidence_json_string(file, status);
        fprintf(file, "\n}\n");
        fclose(file);
    }
}

int dah_run_evidence_initialize(const char *run_id, const char *started_utc,
                                uint64_t executable_hash)
{
    int directory_length;
    if (!CreateDirectoryA("debug-runs", NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS)
        return 0;
    directory_length = snprintf(evidence_directory, sizeof(evidence_directory),
                                "debug-runs\\%s", run_id);
    if (directory_length <= 0 ||
        (size_t)directory_length >= sizeof(evidence_directory)) {
        evidence_directory[0] = '\0';
        return 0;
    }
    if (!CreateDirectoryA(evidence_directory, NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) {
        evidence_directory[0] = '\0';
        return 0;
    }
    strcpy_s(evidence_run_id, sizeof(evidence_run_id), run_id);
    strcpy_s(evidence_started_utc, sizeof(evidence_started_utc), started_utc);
    evidence_executable_hash = executable_hash;
    return 1;
}
