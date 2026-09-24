/* Explicit internal or hidden-script test input only. Rows:
 * start duration hex_buttons A B LX LY RX RY [X [Y BLACK WHITE LT RT]].
 * Times count logical controller polls. No host input devices are accessed. */
static void dah_apply_scripted_input(XBOX_INPUT_STATE *state)
{
    struct dah_input_event { unsigned start, duration, buttons, a, b, x, y, black, white, lt, rt; int lx, ly, rx, ry; int logged; };
    static struct dah_input_event events[128];
    static unsigned count;
    static int loaded;
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
        }
    }
    if (!loaded) {
        const char *path = getenv("DAH_INPUT_SCRIPT");
        loaded = 1;
        if (path && *path) {
            FILE *file = fopen(path, "r");
            if (file) {
                char line[256];
                while (fgets(line, sizeof(line), file)) {
                    struct dah_input_event event = {0};
                    if (line[0] == '#' || line[0] == '\n' || line[0] == '\r') continue;
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
                    events[count++] = event;
                }
                fclose(file);
                fprintf(stderr, "[DAH-INPUT-SCRIPT] loaded %u events\n", count);
            } else fprintf(stderr, "[DAH-INPUT-SCRIPT] cannot read schedule\n");
        }
    }
    for (i = 0; i < count; ++i) {
        struct dah_input_event *event = &events[i];
        if (g_dah_input_state_calls < event->start || g_dah_input_state_calls - event->start >= event->duration) continue;
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
            fprintf(stderr, "[DAH-INPUT-SCRIPT] event=%u call=%u duration=%u buttons=%04X A=%u B=%u X=%u sticks=%d,%d,%d,%d extended=Y:%u,BLACK:%u,WHITE:%u,LT:%u,RT:%u\n",
                i, g_dah_input_state_calls, event->duration, event->buttons, event->a, event->b,
                event->x, event->lx, event->ly, event->rx, event->ry, event->y, event->black,
                event->white, event->lt, event->rt);
        }
    }
}
