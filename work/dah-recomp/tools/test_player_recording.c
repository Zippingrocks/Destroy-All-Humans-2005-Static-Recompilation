#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "dah_player_recording.h"

int main(void)
{
    dah_player_recording_header header;
    dah_player_recording_sample samples[2];
    uint32_t checksum_a, checksum_b;

    assert(dah_player_recording_name_valid("farm_combat_01"));
    assert(dah_player_recording_name_valid("Rockwell-test"));
    assert(!dah_player_recording_name_valid(""));
    assert(!dah_player_recording_name_valid("../escape"));
    assert(!dah_player_recording_name_valid("name with spaces"));

    dah_player_recording_header_initialize(&header);
    assert(!dah_player_recording_header_valid(&header));
    header.sample_count = 2u;
    assert(dah_player_recording_header_valid(&header));
    header.sample_size++;
    assert(!dah_player_recording_header_valid(&header));
    header.sample_size--;

    memset(samples, 0, sizeof(samples));
    samples[0].buttons = 0x10u;
    samples[1].analog[0] = 255u;
    checksum_a = dah_player_recording_checksum(
        DAH_PLAYER_RECORDING_CHECKSUM_SEED, samples, sizeof(samples));
    checksum_b = dah_player_recording_checksum(
        dah_player_recording_checksum(DAH_PLAYER_RECORDING_CHECKSUM_SEED,
                                      &samples[0], sizeof(samples[0])),
        &samples[1], sizeof(samples[1]));
    assert(checksum_a == checksum_b);
    samples[1].left_x = 1;
    assert(checksum_a != dah_player_recording_checksum(
        DAH_PLAYER_RECORDING_CHECKSUM_SEED, samples, sizeof(samples)));
    return 0;
}
