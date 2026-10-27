/* Deterministic player input recorder/replayer.
 *
 * This is included once by recomp_manual.c. It records the final logical Xbox
 * pad packet at the retail XInputGetState boundary, once per port-0 poll. A
 * replay owns that same boundary and rejects loop-timeline divergence instead
 * of continuing in an unknown game state. No game state is patched or skipped.
 */
#include "dah_player_recording.h"

enum dah_player_recorder_mode {
    DAH_PLAYER_RECORDER_IDLE,
    DAH_PLAYER_RECORDER_RECORD_ARMED,
    DAH_PLAYER_RECORDER_RECORDING,
    DAH_PLAYER_RECORDER_REPLAY_ARMED,
    DAH_PLAYER_RECORDER_REPLAYING
};

static enum dah_player_recorder_mode g_dah_player_recorder_mode;
static FILE *g_dah_player_record_file;
static dah_player_recording_header g_dah_player_record_header;
static dah_player_recording_sample *g_dah_player_replay_samples;
static uint32_t g_dah_player_replay_index;
static uint32_t g_dah_player_record_start_loop;
static uint32_t g_dah_player_replay_start_loop;
static char g_dah_player_record_path[1024];
static char g_dah_player_record_name[64];

static int dah_player_recorder_path(const char *name, char *path, size_t size)
{
    char local[768], root[896], recordings[960];
    DWORD length;
    int written;
    if (!dah_player_recording_name_valid(name)) return 0;
    length = GetEnvironmentVariableA("LOCALAPPDATA", local, (DWORD)sizeof(local));
    if (!length || length >= sizeof(local)) return 0;
    written = snprintf(root, sizeof(root), "%s\\DestroyAllHumansRecomp", local);
    if (written < 0 || (size_t)written >= sizeof(root)) return 0;
    if (!CreateDirectoryA(root, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
        return 0;
    written = snprintf(recordings, sizeof(recordings), "%s\\recordings", root);
    if (written < 0 || (size_t)written >= sizeof(recordings)) return 0;
    if (!CreateDirectoryA(recordings, NULL) &&
        GetLastError() != ERROR_ALREADY_EXISTS) return 0;
    written = snprintf(path, size, "%s\\%s.dahrec", recordings, name);
    return written >= 0 && (size_t)written < size;
}

static void dah_player_recorder_release_replay(void)
{
    free(g_dah_player_replay_samples);
    g_dah_player_replay_samples = NULL;
    g_dah_player_replay_index = 0u;
}

static void dah_player_recorder_finish_recording(const char *reason)
{
    if (g_dah_player_record_file) {
        fflush(g_dah_player_record_file);
        if (fseek(g_dah_player_record_file, 0, SEEK_SET) == 0)
            fwrite(&g_dah_player_record_header,
                   sizeof(g_dah_player_record_header), 1u,
                   g_dah_player_record_file);
        fflush(g_dah_player_record_file);
        fclose(g_dah_player_record_file);
        g_dah_player_record_file = NULL;
    }
    if (g_dah_player_record_header.sample_count) {
        dah_console_write("Player recording '%s' saved: %u exact pad polls.",
                          g_dah_player_record_name,
                          g_dah_player_record_header.sample_count);
        fprintf(stderr,
                "[DAH-PLAYER-RECORD] stopped name=%s samples=%u checksum=%08X reason=%s path=%s\n",
                g_dah_player_record_name,
                g_dah_player_record_header.sample_count,
                g_dah_player_record_header.sample_checksum,
                reason ? reason : "requested", g_dah_player_record_path);
    } else {
        DeleteFileA(g_dah_player_record_path);
        dah_console_write("Player recording stopped before gameplay input began.");
    }
    fflush(stderr);
    g_dah_player_recorder_mode = DAH_PLAYER_RECORDER_IDLE;
}

static int dah_player_recorder_checkpoint(void)
{
    long end;
    if (!g_dah_player_record_file) return 0;
    end = ftell(g_dah_player_record_file);
    if (end < 0 || fflush(g_dah_player_record_file) != 0 ||
        fseek(g_dah_player_record_file, 0, SEEK_SET) != 0 ||
        fwrite(&g_dah_player_record_header,
               sizeof(g_dah_player_record_header), 1u,
               g_dah_player_record_file) != 1u ||
        fflush(g_dah_player_record_file) != 0 ||
        fseek(g_dah_player_record_file, end, SEEK_SET) != 0) return 0;
    return 1;
}

static void dah_player_recorder_stop_replay(const char *reason)
{
    uint32_t completed = g_dah_player_replay_index;
    uint32_t total = g_dah_player_record_header.sample_count;
    fprintf(stderr,
            "[DAH-PLAYER-REPLAY] stopped name=%s completed=%u total=%u reason=%s\n",
            g_dah_player_record_name, completed, total,
            reason ? reason : "requested");
    fflush(stderr);
    dah_console_write("Player replay '%s' stopped at %u/%u: %s.",
                      g_dah_player_record_name, completed, total,
                      reason ? reason : "requested");
    dah_player_recorder_release_replay();
    g_dah_player_recorder_mode = DAH_PLAYER_RECORDER_IDLE;
}

static int dah_player_recorder_start_recording(const char *name)
{
    float x, y, z;
    if (g_dah_player_recorder_mode != DAH_PLAYER_RECORDER_IDLE) {
        dah_console_write("Stop the current player recording or replay first.");
        return 0;
    }
    if (!dah_player_recording_name_valid(name)) {
        dah_console_write("Recording names use 1-48 letters, numbers, '-' or '_'.");
        return 0;
    }
    if (dah_console_level_is_busy() ||
        !dah_dev_npc_player_position(&x, &y, &z)) {
        dah_console_write("Start recording from stable on-foot gameplay with Crypto loaded.");
        return 0;
    }
    if (!dah_player_recorder_path(name, g_dah_player_record_path,
                                  sizeof(g_dah_player_record_path))) {
        dah_console_write("Could not create the player recordings folder.");
        return 0;
    }
    if (GetFileAttributesA(g_dah_player_record_path) != INVALID_FILE_ATTRIBUTES) {
        dah_console_write("Recording '%s' already exists; choose a new name.", name);
        return 0;
    }
    g_dah_player_record_file = fopen(g_dah_player_record_path, "w+b");
    if (!g_dah_player_record_file) {
        dah_console_write("Could not create recording '%s'.", name);
        return 0;
    }
    setvbuf(g_dah_player_record_file, NULL, _IOFBF, 1024u * 1024u);
    dah_player_recording_header_initialize(&g_dah_player_record_header);
    g_dah_player_record_header.start_x = x;
    g_dah_player_record_header.start_y = y;
    g_dah_player_record_header.start_z = z;
    if (fwrite(&g_dah_player_record_header, sizeof(g_dah_player_record_header),
               1u, g_dah_player_record_file) != 1u) {
        fclose(g_dah_player_record_file);
        g_dah_player_record_file = NULL;
        DeleteFileA(g_dah_player_record_path);
        dah_console_write("Could not initialize recording '%s'.", name);
        return 0;
    }
    strcpy(g_dah_player_record_name, name);
    g_dah_player_recorder_mode = DAH_PLAYER_RECORDER_RECORD_ARMED;
    dah_console_write("Recording '%s' armed. Close the console and play; use player_record stop when done.", name);
    fprintf(stderr,
            "[DAH-PLAYER-RECORD] armed name=%s position=%.6g,%.6g,%.6g path=%s\n",
            name, (double)x, (double)y, (double)z, g_dah_player_record_path);
    fflush(stderr);
    return 1;
}

static int dah_player_recorder_load_replay(const char *name)
{
    FILE *file;
    dah_player_recording_header header;
    dah_player_recording_sample *samples;
    uint32_t checksum;
    size_t bytes;
    float x, y, z, dx, dy, dz;
    if (g_dah_player_recorder_mode != DAH_PLAYER_RECORDER_IDLE) {
        dah_console_write("Stop the current player recording or replay first.");
        return 0;
    }
    if (!dah_player_recorder_path(name, g_dah_player_record_path,
                                  sizeof(g_dah_player_record_path))) {
        dah_console_write("Invalid recording name.");
        return 0;
    }
    if (dah_console_level_is_busy() ||
        !dah_dev_npc_player_position(&x, &y, &z)) {
        dah_console_write("Start replay from stable on-foot gameplay with Crypto loaded.");
        return 0;
    }
    file = fopen(g_dah_player_record_path, "rb");
    if (!file) {
        dah_console_write("Recording '%s' was not found.", name);
        return 0;
    }
    if (fread(&header, sizeof(header), 1u, file) != 1u ||
        !dah_player_recording_header_valid(&header)) {
        fclose(file);
        dah_console_write("Recording '%s' has an invalid header.", name);
        return 0;
    }
    bytes = (size_t)header.sample_count * sizeof(*samples);
    samples = (dah_player_recording_sample *)malloc(bytes);
    if (!samples || fread(samples, sizeof(*samples), header.sample_count, file) !=
                    header.sample_count) {
        free(samples);
        fclose(file);
        dah_console_write("Recording '%s' is truncated or too large.", name);
        return 0;
    }
    fclose(file);
    checksum = dah_player_recording_checksum(DAH_PLAYER_RECORDING_CHECKSUM_SEED,
                                             samples, bytes);
    if (checksum != header.sample_checksum) {
        free(samples);
        dah_console_write("Recording '%s' failed its checksum.", name);
        return 0;
    }
    dx = x - header.start_x;
    dy = y - header.start_y;
    dz = z - header.start_z;
    if (dx * dx + dy * dy + dz * dz > 4.0f) {
        free(samples);
        dah_console_write("Replay start rejected: Crypto is %.1f units from the recorded start.",
                          sqrtf(dx * dx + dy * dy + dz * dz));
        return 0;
    }
    g_dah_player_record_header = header;
    g_dah_player_replay_samples = samples;
    g_dah_player_replay_index = 0u;
    strcpy(g_dah_player_record_name, name);
    g_dah_player_recorder_mode = DAH_PLAYER_RECORDER_REPLAY_ARMED;
    dah_console_write("Replay '%s' armed: %u polls. Close the console to begin.",
                      name, header.sample_count);
    fprintf(stderr,
            "[DAH-PLAYER-REPLAY] armed name=%s samples=%u checksum=%08X position_error=%.6g\n",
            name, header.sample_count, checksum,
            (double)sqrtf(dx * dx + dy * dy + dz * dz));
    fflush(stderr);
    return 1;
}

static void dah_player_recorder_status(void)
{
    const char *mode = "idle";
    if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_RECORD_ARMED)
        mode = "record armed";
    else if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_RECORDING)
        mode = "recording";
    else if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAY_ARMED)
        mode = "replay armed";
    else if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAYING)
        mode = "replaying";
    dah_console_write("Player recorder: %s%s%s; sample %u/%u.", mode,
                      g_dah_player_record_name[0] ? " " : "",
                      g_dah_player_record_name,
                      g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAYING ?
                          g_dah_player_replay_index :
                          g_dah_player_record_header.sample_count,
                      g_dah_player_record_header.sample_count);
}

static int dah_player_recorder_command(const char *command, const char *arg,
                                       int tokens)
{
    if (tokens < 1) return 0;
    if (!_stricmp(command, "player_record")) {
        if (tokens == 1) {
            dah_player_recorder_status();
            return 1;
        }
        if (tokens != 2) {
            dah_console_write("Usage: player_record <name> or player_record stop.");
            return 1;
        }
        if (!_stricmp(arg, "stop")) {
            if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_RECORD_ARMED ||
                g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_RECORDING)
                dah_player_recorder_finish_recording("requested");
            else dah_console_write("No player recording is active.");
            return 1;
        }
        dah_player_recorder_start_recording(arg);
        return 1;
    }
    if (!_stricmp(command, "player_replay")) {
        if (tokens == 1) {
            dah_player_recorder_status();
            return 1;
        }
        if (tokens != 2) {
            dah_console_write("Usage: player_replay <name> or player_replay stop.");
            return 1;
        }
        if (!_stricmp(arg, "stop")) {
            if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAY_ARMED ||
                g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAYING)
                dah_player_recorder_stop_replay("requested");
            else dah_console_write("No player replay is active.");
            return 1;
        }
        dah_player_recorder_load_replay(arg);
        return 1;
    }
    return 0;
}

static void dah_player_recorder_automation_poll(void)
{
    static int initialized;
    static int pending;
    static int request_consumed;
    static char name[64];
    float x, y, z;
    if (!initialized) {
        const char *value = getenv("DAH_PLAYER_REPLAY");
        initialized = 1;
        if (value && dah_player_recording_name_valid(value)) {
            strcpy(name, value);
            pending = 1;
            fprintf(stderr,
                    "[DAH-PLAYER-REPLAY] automation waiting name=%s\n", name);
            fflush(stderr);
        } else if (value && *value) {
            fprintf(stderr,
                    "[DAH-PLAYER-REPLAY] automation rejected invalid name\n");
            fflush(stderr);
        }
    }
    if (!pending && !request_consumed &&
        g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_IDLE) {
        const char *request_path = getenv("DAH_PLAYER_REPLAY_REQUEST");
        if (request_path && *request_path) {
            FILE *request = fopen(request_path, "r");
            if (request) {
                char requested_name[64];
                int extra;
                requested_name[0] = '\0';
                extra = fscanf(request, "%63s", requested_name);
                fclose(request);
                request_consumed = 1;
                if (extra == 1 &&
                    dah_player_recording_name_valid(requested_name)) {
                    strcpy(name, requested_name);
                    pending = 1;
                    fprintf(stderr,
                            "[DAH-PLAYER-REPLAY] external request waiting name=%s path=%s\n",
                            name, request_path);
                } else {
                    fprintf(stderr,
                            "[DAH-PLAYER-REPLAY] external request rejected path=%s\n",
                            request_path);
                }
                fflush(stderr);
            }
        }
    }
    if (!pending || g_dah_player_recorder_mode != DAH_PLAYER_RECORDER_IDLE ||
        dah_console_level_is_busy() ||
        !dah_dev_npc_player_position(&x, &y, &z)) return;
    {
        const char *barrier = getenv("DAH_PLAYER_REPLAY_BARRIER");
        if (barrier && *barrier &&
            GetFileAttributesA(barrier) == INVALID_FILE_ATTRIBUTES) return;
    }
    pending = 0;
    dah_player_recorder_load_replay(name);
}

static void dah_player_recorder_sample_from_state(
    dah_player_recording_sample *sample, const XBOX_INPUT_STATE *state,
    uint32_t port, uint32_t loop_delta)
{
    memset(sample, 0, sizeof(*sample));
    sample->loop_delta = loop_delta;
    sample->packet_number = state->dwPacketNumber;
    sample->buttons = state->Gamepad.wButtons;
    memcpy(sample->analog, state->Gamepad.bAnalogButtons,
           sizeof(sample->analog));
    sample->left_x = state->Gamepad.sThumbLX;
    sample->left_y = state->Gamepad.sThumbLY;
    sample->right_x = state->Gamepad.sThumbRX;
    sample->right_y = state->Gamepad.sThumbRY;
    sample->port = (uint8_t)port;
}

static void dah_player_recorder_state_from_sample(
    XBOX_INPUT_STATE *state, const dah_player_recording_sample *sample)
{
    memset(state, 0, sizeof(*state));
    state->dwPacketNumber = sample->packet_number;
    state->Gamepad.wButtons = sample->buttons;
    memcpy(state->Gamepad.bAnalogButtons, sample->analog,
           sizeof(sample->analog));
    state->Gamepad.sThumbLX = sample->left_x;
    state->Gamepad.sThumbLY = sample->left_y;
    state->Gamepad.sThumbRX = sample->right_x;
    state->Gamepad.sThumbRY = sample->right_y;
}

static void dah_player_recorder_process(XBOX_INPUT_STATE *state, uint32_t port)
{
    uint32_t loop;
    if (port != 0u || g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_IDLE)
        return;
    /* Opening the console always retains control and pauses arming. A replay
     * that was already running will fail its loop guard after the console is
     * closed, making the interruption explicit rather than silently drifting. */
    if (dah_console_is_open()) return;
    loop = MEM32(0x0025B1DCu);
    if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_RECORD_ARMED) {
        g_dah_player_record_start_loop = loop;
        g_dah_player_recorder_mode = DAH_PLAYER_RECORDER_RECORDING;
        fprintf(stderr, "[DAH-PLAYER-RECORD] started name=%s loop=%u\n",
                g_dah_player_record_name, loop);
        fflush(stderr);
    }
    if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_RECORDING) {
        dah_player_recording_sample sample;
        if (g_dah_player_record_header.sample_count >=
            DAH_PLAYER_RECORDING_MAX_SAMPLES) {
            dah_player_recorder_finish_recording("sample limit reached");
            return;
        }
        dah_player_recorder_sample_from_state(
            &sample, state, port, loop - g_dah_player_record_start_loop);
        if (fwrite(&sample, sizeof(sample), 1u,
                   g_dah_player_record_file) != 1u) {
            dah_player_recorder_finish_recording("write failed");
            return;
        }
        g_dah_player_record_header.sample_checksum =
            dah_player_recording_checksum(
                g_dah_player_record_header.sample_checksum,
                &sample, sizeof(sample));
        ++g_dah_player_record_header.sample_count;
        /* Commit a checksum-verified prefix about every ten seconds at the
         * retail 30 Hz target. A process crash can therefore replay the last
         * durable prefix instead of losing the whole test. */
        if ((g_dah_player_record_header.sample_count % 300u) == 0u &&
            !dah_player_recorder_checkpoint())
            dah_player_recorder_finish_recording("checkpoint failed");
        return;
    }
    /* Holding BACK+START on the physical state is an emergency escape before
     * replay takes ownership of the packet. */
    if ((state->Gamepad.wButtons &
         (XBOX_GAMEPAD_BACK | XBOX_GAMEPAD_START)) ==
        (XBOX_GAMEPAD_BACK | XBOX_GAMEPAD_START)) {
        dah_player_recorder_stop_replay("BACK+START abort");
        memset(state, 0, sizeof(*state));
        return;
    }
    if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAY_ARMED) {
        g_dah_player_replay_start_loop = loop;
        g_dah_player_recorder_mode = DAH_PLAYER_RECORDER_REPLAYING;
        fprintf(stderr, "[DAH-PLAYER-REPLAY] started name=%s loop=%u\n",
                g_dah_player_record_name, loop);
        fflush(stderr);
    }
    if (g_dah_player_recorder_mode == DAH_PLAYER_RECORDER_REPLAYING) {
        const dah_player_recording_sample *sample;
        uint32_t relative_loop;
        if (g_dah_player_replay_index >=
            g_dah_player_record_header.sample_count) {
            dah_player_recorder_stop_replay("completed");
            memset(state, 0, sizeof(*state));
            return;
        }
        sample = &g_dah_player_replay_samples[g_dah_player_replay_index];
        relative_loop = loop - g_dah_player_replay_start_loop;
        if (sample->port != port || sample->loop_delta != relative_loop) {
            char reason[96];
            snprintf(reason, sizeof(reason),
                     "timeline divergence (expected loop +%u, observed +%u)",
                     sample->loop_delta, relative_loop);
            dah_player_recorder_stop_replay(reason);
            memset(state, 0, sizeof(*state));
            return;
        }
        dah_player_recorder_state_from_sample(state, sample);
        ++g_dah_player_replay_index;
    }
}
