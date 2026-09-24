/* Explicit internal or hidden-script test input only. Rows:
 * start duration hex_buttons A B LX LY RX RY [X [Y BLACK WHITE LT RT]].
 * Times count logical controller polls.  A line containing "@gameplay"
 * makes subsequent row starts relative to a stable active-Crypto state and
 * interprets their start/duration values as retail main-loop frames;
 * this keeps accelerated tests deterministic across variable movie/load
 * completion. No host input devices are accessed. */
static void dah_apply_scripted_input(XBOX_INPUT_STATE *state)
{
    struct dah_input_event { unsigned start, duration, buttons, a, b, x, y, black, white, lt, rt; int lx, ly, rx, ry; int logged, relative_gameplay; };
    static struct dah_input_event events[128];
    static unsigned count;
    static int loaded;
    static int has_gameplay_relative;
    static unsigned gameplay_ready_polls;
    static uint64_t gameplay_anchor_frame;
    static FILETIME last_write;
    static DWORD last_size;
    unsigned i;
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
                while (fgets(line, sizeof(line), file)) {
                    struct dah_input_event event = {0};
                    if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;
                    if (!strncmp(line, "@gameplay", 9) &&
                        (line[9] == '\0' || line[9] == '\n' || line[9] == '\r' || line[9] == ' ' || line[9] == '\t')) {
                        relative_gameplay = 1;
                        has_gameplay_relative = 1;
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
            if (++gameplay_ready_polls >= 30u) {
                gameplay_anchor_frame = dah_frame_serial();
                fprintf(stderr, "[DAH-INPUT-SCRIPT] gameplay-anchor call=%u frame=%llu position=%.3f,%.3f,%.3f\n",
                        g_dah_input_state_calls, (unsigned long long)gameplay_anchor_frame, x, y, z);
            }
        } else {
            gameplay_ready_polls = 0;
        }
    }
    for (i = 0; i < count; ++i) {
        struct dah_input_event *event = &events[i];
        uint64_t clock_value, event_start;
        if (event->relative_gameplay && !gameplay_anchor_frame) continue;
        clock_value = event->relative_gameplay ? dah_frame_serial() : g_dah_input_state_calls;
        event_start = event->relative_gameplay ? gameplay_anchor_frame + event->start : event->start;
        if (clock_value < event_start || clock_value - event_start >= event->duration) continue;
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
            event->logged = 1;
            fprintf(stderr, "[DAH-INPUT-SCRIPT] event=%u call=%u frame=%llu duration=%u buttons=%04X A=%u B=%u X=%u sticks=%d,%d,%d,%d extended=Y:%u,BLACK:%u,WHITE:%u,LT:%u,RT:%u relative_gameplay=%d\n",
                i, g_dah_input_state_calls, (unsigned long long)dah_frame_serial(), event->duration, event->buttons, event->a, event->b,
                event->x, event->lx, event->ly, event->rx, event->ry, event->y, event->black,
                event->white, event->lt, event->rt, event->relative_gameplay);
        }
    }
}
