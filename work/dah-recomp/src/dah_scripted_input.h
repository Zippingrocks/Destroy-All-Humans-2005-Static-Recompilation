/* Explicit internal or hidden-script test input only. Rows:
 * start duration hex_buttons A B LX LY RX RY [X [Y BLACK WHITE LT RT]].
 * Times count logical controller polls.  A line containing "@gameplay"
 * makes subsequent row starts relative to a stable active-Crypto state and
 * interprets their start/duration values as retail main-loop frames;
 * this keeps accelerated tests deterministic across variable movie/load
 * completion. "@frame" uses the absolute retail main-loop counter at
 * 0025B1DC for subsequent rows, also observable in xemu. This mode does not
 * run the gameplay movement probe. No host input devices are accessed. */
static void dah_apply_scripted_input(XBOX_INPUT_STATE *state)
{
    struct dah_input_event { unsigned start, duration, buttons, a, b, x, y, black, white, lt, rt; int lx, ly, rx, ry; int logged, relative_gameplay, absolute_frame; };
    static struct dah_input_event events[128];
    static unsigned count;
    static int loaded;
    static int has_gameplay_relative;
    static unsigned gameplay_ready_polls;
    static uint64_t gameplay_anchor_frame;
    static float gameplay_initial_x, gameplay_initial_y, gameplay_initial_z;
    static int gameplay_position_baseline, gameplay_position_moved;
    static unsigned gameplay_probe_settle, gameplay_probe_phase;
    static int gameplay_probe_logged;
    static FILETIME last_write;
    static DWORD last_size;
    static unsigned char *memdiff_before;
    static int memdiff_target = -2;
    static uint64_t memdiff_finish_frame;
    static int memdiff_reported;
    unsigned i;
    extern ptrdiff_t g_xbox_mem_offset;
    if (!dah_input_uses_neutral_pad()) return;
    if (g_dah_input_state_calls % 300 == 0)
        fprintf(stderr, "[DAH-INPUT-TICK] call=%u\n", g_dah_input_state_calls);
    /* Background test driver may append future events while the game runs. */
    if (!loaded || g_dah_input_state_calls % 30 == 0) {
        const char *path = getenv("DAH_INPUT_SCRIPT");
        WIN32_FILE_ATTRIBUTE_DATA info;
        if (path && *path && GetFileAttributesExA(path, GetFileExInfoStandard, &info) &&
            (!loaded || CompareFileTime(&last_write, &info.ftLastWriteTime) != 0 || last_size != info.nFileSizeLow)) {
            last_write = info.ftLastWriteTime;
            last_size = info.nFileSizeLow;
            count = 0;
            loaded = 0;
            has_gameplay_relative = 0;
            gameplay_ready_polls = 0;
            gameplay_anchor_frame = 0;
            gameplay_position_baseline = 0;
            gameplay_position_moved = 0;
            gameplay_probe_settle = 0;
            gameplay_probe_phase = 0;
            gameplay_probe_logged = 0;
        }
    }
    if (!loaded) {
        const char *path = getenv("DAH_INPUT_SCRIPT");
        loaded = 1;
        if (path && *path) {
            FILE *file = fopen(path, "r");
            if (file) {
                char line[256];
                int relative_gameplay = 0;
                int absolute_frame = 0;
                while (fgets(line, sizeof(line), file)) {
                    struct dah_input_event event = {0};
                    if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;
                    if (!strncmp(line, "@gameplay", 9) &&
                        (line[9] == '\0' || line[9] == '\n' || line[9] == '\r' || line[9] == ' ' || line[9] == '\t')) {
                        relative_gameplay = 1;
                        absolute_frame = 0;
                        has_gameplay_relative = 1;
                        continue;
                    }
                    if (!strncmp(line, "@frame", 6) &&
                        (line[6] == '\0' || line[6] == '\n' || line[6] == '\r' || line[6] == ' ' || line[6] == '\t')) {
                        relative_gameplay = 0;
                        absolute_frame = 1;
                        continue;
                    }
                    char extra;
                    int fields = sscanf(line, "%u %u %x %u %u %d %d %d %d %u %u %u %u %u %u %c", &event.start, &event.duration,
                        &event.buttons, &event.a, &event.b, &event.lx, &event.ly, &event.rx, &event.ry,
                        &event.x, &event.y, &event.black, &event.white, &event.lt, &event.rt, &extra);
                    if (count >= 128 || (fields != 9 && fields != 10 && fields != 15) ||
                        event.duration == 0 || event.duration > 100000 || event.start > 10000000 ||
                        event.buttons > 0xffff || event.a > 255 || event.b > 255 || event.x > 255 ||
                        event.y > 255 || event.black > 255 || event.white > 255 ||
                        event.lt > 255 || event.rt > 255 ||
                        event.lx < -32768 || event.lx > 32767 || event.ly < -32768 || event.ly > 32767 ||
                        event.rx < -32768 || event.rx > 32767 || event.ry < -32768 || event.ry > 32767) {
                        fprintf(stderr, "[DAH-INPUT-SCRIPT] invalid row; input schedule disabled\n");
                        count = 0;
                        break;
                    }
                    event.relative_gameplay = relative_gameplay;
                    event.absolute_frame = absolute_frame;
                    events[count++] = event;
                }
                fclose(file);
                fprintf(stderr, "[DAH-INPUT-SCRIPT] loaded %u events\n", count);
            } else fprintf(stderr, "[DAH-INPUT-SCRIPT] cannot read schedule\n");
        }
    }
    if (has_gameplay_relative && !gameplay_anchor_frame) {
        float x, y, z;
        if (!dah_console_level_is_busy() && dah_dev_npc_player_position(&x, &y, &z)) {
            if (!gameplay_position_baseline) {
                gameplay_initial_x = x;
                gameplay_initial_y = y;
                gameplay_initial_z = z;
                gameplay_position_baseline = 1;
            }

            /* A rendered world or a moving Crypto object does not prove that
             * the player owns it: opening cutscenes move the same actor.  The
             * anchor therefore requires a stationary neutral window followed
             * by motion that occurs specifically during our bounded forward
             * pulse.  This works for every site and rejects autonomous world
             * motion instead of treating it as control. */
            if (!gameplay_position_moved) {
                if (gameplay_probe_settle < 300u) {
                    float dx = x - gameplay_initial_x;
                    float dy = y - gameplay_initial_y;
                    float dz = z - gameplay_initial_z;
                    if (dx * dx + dy * dy + dz * dz <= 0.0025f) {
                        ++gameplay_probe_settle;
                    } else {
                        gameplay_probe_settle = 0;
                        gameplay_probe_phase = 0;
                        gameplay_initial_x = x;
                        gameplay_initial_y = y;
                        gameplay_initial_z = z;
                    }
                } else {
                    unsigned phase = gameplay_probe_phase++ % 120u;
                    if (phase == 0u) {
                        gameplay_initial_x = x;
                        gameplay_initial_y = y;
                        gameplay_initial_z = z;
                        if (!gameplay_probe_logged) {
                            fprintf(stderr,
                                    "[DAH-INPUT-SCRIPT] gameplay-control-probe armed call=%u frame=%llu\n",
                                    g_dah_input_state_calls,
                                    (unsigned long long)dah_frame_serial());
                            gameplay_probe_logged = 1;
                        }
                    }
                    if (phase < 15u)
                        state->Gamepad.sThumbLY = 32767;
                    if (phase == 30u) {
                        float dx = x - gameplay_initial_x;
                        float dy = y - gameplay_initial_y;
                        float dz = z - gameplay_initial_z;
                        if (dx * dx + dy * dy + dz * dz >= 0.25f)
                            gameplay_position_moved = 1;
                    }
                }
            }

            if (gameplay_position_moved)
                ++gameplay_ready_polls;
            else
                gameplay_ready_polls = 0;
            if (gameplay_ready_polls >= 30u) {
                gameplay_anchor_frame = dah_frame_serial();
                fprintf(stderr, "[DAH-INPUT-SCRIPT] gameplay-anchor call=%u frame=%llu position=%.3f,%.3f,%.3f source=control-probe\n",
                        g_dah_input_state_calls, (unsigned long long)gameplay_anchor_frame, x, y, z);
            }
        } else {
            gameplay_ready_polls = 0;
        }
    }
    /* One-shot, internal-only RAM differencing for proving whether a scripted
     * menu input reaches retail state.  This is deliberately opt-in and never
     * active in a player's normal launch. */
    if (memdiff_target == -2) {
        const char *value = getenv("DAH_INPUT_MEMDIFF_EVENT");
        char *end = NULL;
        unsigned long parsed = value && *value ? strtoul(value, &end, 10) : 0;
        memdiff_target = value && *value && end && !*end && parsed < 128 ? (int)parsed : -1;
        if (memdiff_target >= 0)
            fprintf(stderr, "[DAH-INPUT-MEMDIFF] armed event=%d\n", memdiff_target);
    }
    for (i = 0; i < count; ++i) {
        struct dah_input_event *event = &events[i];
        uint64_t clock_value, event_start;
        if (event->relative_gameplay && !gameplay_anchor_frame) continue;
        clock_value = event->relative_gameplay ? dah_frame_serial() : g_dah_input_state_calls;
        /* Menu code polls more than once per frame. @frame uses the retail
         * loop counter at driver+0xC, also directly readable in xemu. */
        if (event->absolute_frame) clock_value = MEM32(0x0025B1DCu);
        event_start = event->relative_gameplay ? gameplay_anchor_frame + event->start : event->start;
        if (clock_value < event_start || clock_value - event_start >= event->duration) continue;
        if ((int)i == memdiff_target && !memdiff_before) {
            const size_t ram_size = 0x08000000u;
            memdiff_before = (unsigned char *)malloc(ram_size);
            if (memdiff_before) {
                memcpy(memdiff_before, (const void *)(uintptr_t)g_xbox_mem_offset, ram_size);
                memdiff_finish_frame = dah_frame_serial() + event->duration + 20u;
                fprintf(stderr, "[DAH-INPUT-MEMDIFF] snapshot event=%u frame=%llu report_frame=%llu\n",
                        i, (unsigned long long)dah_frame_serial(),
                        (unsigned long long)memdiff_finish_frame);
            } else {
                fprintf(stderr, "[DAH-INPUT-MEMDIFF] allocation failed\n");
                memdiff_reported = 1;
            }
        }
        state->Gamepad.wButtons |= (uint16_t)event->buttons;
        if (event->a) state->Gamepad.bAnalogButtons[XBOX_BUTTON_A] = (uint8_t)event->a;
        if (event->b) state->Gamepad.bAnalogButtons[XBOX_BUTTON_B] = (uint8_t)event->b;
        if (event->x) state->Gamepad.bAnalogButtons[XBOX_BUTTON_X] = (uint8_t)event->x;
        if (event->y) state->Gamepad.bAnalogButtons[XBOX_BUTTON_Y] = (uint8_t)event->y;
        if (event->black) state->Gamepad.bAnalogButtons[XBOX_BUTTON_BLACK] = (uint8_t)event->black;
        if (event->white) state->Gamepad.bAnalogButtons[XBOX_BUTTON_WHITE] = (uint8_t)event->white;
        if (event->lt) state->Gamepad.bAnalogButtons[XBOX_BUTTON_LTRIGGER] = (uint8_t)event->lt;
        if (event->rt) state->Gamepad.bAnalogButtons[XBOX_BUTTON_RTRIGGER] = (uint8_t)event->rt;
        if (event->lx) state->Gamepad.sThumbLX = (int16_t)event->lx;
        if (event->ly) state->Gamepad.sThumbLY = (int16_t)event->ly;
        if (event->rx) state->Gamepad.sThumbRX = (int16_t)event->rx;
        if (event->ry) state->Gamepad.sThumbRY = (int16_t)event->ry;
        if (!event->logged) {
            uint32_t control_system = MEM32(0x0025FCECu);
            uint32_t control_player = control_system >= 0x10000u &&
                                      control_system <= 0x08000000u - 0x3Cu ?
                                      MEM32(control_system + 0x38u) : 0u;
            event->logged = 1;
            fprintf(stderr, "[DAH-INPUT-SCRIPT] event=%u call=%u frame=%llu duration=%u buttons=%04X A=%u B=%u X=%u sticks=%d,%d,%d,%d extended=Y:%u,BLACK:%u,WHITE:%u,LT:%u,RT:%u relative_gameplay=%d\n",
                i, g_dah_input_state_calls, (unsigned long long)dah_frame_serial(), event->duration, event->buttons, event->a, event->b,
                event->x, event->lx, event->ly, event->rx, event->ry, event->y, event->black,
                event->white, event->lt, event->rt, event->relative_gameplay);
            if (control_player >= 0x10000u &&
                control_player <= 0x08000000u - 0x60u) {
                uint32_t focus = MEM32(control_player + 0x30u);
                uint32_t ship = MEM32(control_player + 0x34u);
                uint32_t actor = MEM32(control_player + 0x38u);
                fprintf(stderr,
                        "[DAH-CONTROL-SETTINGS] event=%u player=%08X words50=%08X,%08X,%08X,%08X\n",
                        i, control_player, MEM32(control_player + 0x50u),
                        MEM32(control_player + 0x54u),
                        MEM32(control_player + 0x58u),
                        MEM32(control_player + 0x5Cu));
                fprintf(stderr,
                        "[DAH-INPUT-STATE] event=%u player=%08X focus=%08X ship=%08X crypto=%08X focusIsShip=%u\n",
                        i, control_player, focus, ship, actor,
                        ship != 0u && focus == ship ? 1u : 0u);
                if (actor >= 0x10000u && actor <= 0x08000000u - 0x158u &&
                    ship >= 0x10000u && ship <= 0x08000000u - 0x158u) {
                    fprintf(stderr,
                            "[DAH-INPUT-POSITION] event=%u crypto=%.3f,%.3f,%.3f ship=%.3f,%.3f,%.3f delta=%.3f,%.3f,%.3f\n",
                            i, MEMF(actor + 0x14Cu), MEMF(actor + 0x150u), MEMF(actor + 0x154u),
                            MEMF(ship + 0x14Cu), MEMF(ship + 0x150u), MEMF(ship + 0x154u),
                            MEMF(ship + 0x14Cu) - MEMF(actor + 0x14Cu),
                            MEMF(ship + 0x150u) - MEMF(actor + 0x150u),
                            MEMF(ship + 0x154u) - MEMF(actor + 0x154u));
                }
            }
            if (event->relative_gameplay && getenv("DAH_INPUT_EVENT_CAPTURE"))
                dah_request_frame_capture();
        }
    }
    if (memdiff_before && !memdiff_reported && dah_frame_serial() >= memdiff_finish_frame) {
        const unsigned char *after = (const unsigned char *)(uintptr_t)g_xbox_mem_offset;
        const size_t ram_size = 0x08000000u;
        const size_t page_size = 4096u;
        size_t offset;
        unsigned changed_pages = 0, changed_bytes = 0, candidates = 0;
        unsigned signed_candidates = 0, float_candidates = 0;
        for (offset = 0x10000u; offset < ram_size; offset += page_size) {
            size_t j, end = offset + page_size;
            int page_changed = memcmp(memdiff_before + offset, after + offset, page_size) != 0;
            if (!page_changed) continue;
            ++changed_pages;
            for (j = offset; j < end; ++j)
                if (memdiff_before[j] != after[j]) ++changed_bytes;
            for (j = offset; j + 4u <= end && candidates < 256u; j += 4u) {
                uint32_t before_value, after_value;
                memcpy(&before_value, memdiff_before + j, sizeof(before_value));
                memcpy(&after_value, after + j, sizeof(after_value));
                if (before_value != after_value && before_value <= 100u && after_value <= 100u) {
                    fprintf(stderr, "[DAH-INPUT-MEMDIFF-CANDIDATE] address=%08X before=%u after=%u\n",
                            (unsigned)j, before_value, after_value);
                    ++candidates;
                }
                if (before_value != after_value && signed_candidates < 256u) {
                    int32_t before_signed = (int32_t)before_value;
                    int32_t after_signed = (int32_t)after_value;
                    if (before_signed >= -10000 && before_signed <= 10000 &&
                        after_signed >= -10000 && after_signed <= 10000 &&
                        (before_signed < 0 || after_signed < 0)) {
                        fprintf(stderr, "[DAH-INPUT-MEMDIFF-SIGNED] address=%08X before=%d after=%d\n",
                                (unsigned)j, before_signed, after_signed);
                        ++signed_candidates;
                    }
                }
                if (before_value != after_value && float_candidates < 256u) {
                    float before_float, after_float;
                    memcpy(&before_float, &before_value, sizeof(before_float));
                    memcpy(&after_float, &after_value, sizeof(after_float));
                    if (isfinite(before_float) && isfinite(after_float) &&
                        fabsf(before_float) <= 100.0f && fabsf(after_float) <= 100.0f &&
                        fabsf(before_float - after_float) >= 0.0001f) {
                        fprintf(stderr, "[DAH-INPUT-MEMDIFF-FLOAT] address=%08X before=%.6g after=%.6g\n",
                                (unsigned)j, before_float, after_float);
                        ++float_candidates;
                    }
                }
            }
        }
        fprintf(stderr, "[DAH-INPUT-MEMDIFF] complete changed_pages=%u changed_bytes=%u small_dword_candidates=%u signed_candidates=%u float_candidates=%u\n",
                changed_pages, changed_bytes, candidates, signed_candidates, float_candidates);
        free(memdiff_before);
        memdiff_before = NULL;
        memdiff_reported = 1;
    }
}
