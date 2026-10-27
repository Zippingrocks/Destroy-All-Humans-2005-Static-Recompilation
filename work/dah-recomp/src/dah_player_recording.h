#ifndef DAH_PLAYER_RECORDING_H
#define DAH_PLAYER_RECORDING_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define DAH_PLAYER_RECORDING_VERSION 1u
#define DAH_PLAYER_RECORDING_MAX_SAMPLES 5000000u
#define DAH_PLAYER_RECORDING_CHECKSUM_SEED 2166136261u

typedef struct dah_player_recording_header {
    char magic[8];
    uint32_t version;
    uint32_t header_size;
    uint32_t sample_size;
    uint32_t sample_count;
    uint32_t sample_checksum;
    uint32_t flags;
    float start_x;
    float start_y;
    float start_z;
    uint32_t reserved[5];
} dah_player_recording_header;

typedef struct dah_player_recording_sample {
    uint32_t loop_delta;
    uint32_t packet_number;
    uint16_t buttons;
    uint8_t analog[8];
    int16_t left_x;
    int16_t left_y;
    int16_t right_x;
    int16_t right_y;
    uint8_t port;
    uint8_t reserved[3];
} dah_player_recording_sample;

static uint32_t dah_player_recording_checksum(uint32_t checksum,
                                              const void *data,
                                              size_t size)
{
    const uint8_t *bytes = (const uint8_t *)data;
    size_t index;
    for (index = 0; index < size; ++index) {
        checksum ^= bytes[index];
        checksum *= 16777619u;
    }
    return checksum;
}

static int dah_player_recording_name_valid(const char *name)
{
    size_t index, length;
    if (!name) return 0;
    length = strlen(name);
    if (!length || length > 48u) return 0;
    for (index = 0; index < length; ++index) {
        unsigned char value = (unsigned char)name[index];
        if (!((value >= 'a' && value <= 'z') ||
              (value >= 'A' && value <= 'Z') ||
              (value >= '0' && value <= '9') ||
              value == '-' || value == '_')) return 0;
    }
    return 1;
}

static void dah_player_recording_header_initialize(
    dah_player_recording_header *header)
{
    memset(header, 0, sizeof(*header));
    memcpy(header->magic, "DAHREC1", 7u);
    header->version = DAH_PLAYER_RECORDING_VERSION;
    header->header_size = (uint32_t)sizeof(*header);
    header->sample_size = (uint32_t)sizeof(dah_player_recording_sample);
    header->sample_checksum = DAH_PLAYER_RECORDING_CHECKSUM_SEED;
}

static int dah_player_recording_header_valid(
    const dah_player_recording_header *header)
{
    return header &&
           memcmp(header->magic, "DAHREC1", 7u) == 0 &&
           header->version == DAH_PLAYER_RECORDING_VERSION &&
           header->header_size == sizeof(*header) &&
           header->sample_size == sizeof(dah_player_recording_sample) &&
           header->sample_count > 0u &&
           header->sample_count <= DAH_PLAYER_RECORDING_MAX_SAMPLES;
}

#endif
