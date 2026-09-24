/* Host developer console. Included once by main.c; game commands are consumed
 * by the original game's input thread, never by this Windows UI thread. */
#include <stdarg.h>

#define DAH_CONSOLE_LINE 192
#define DAH_CONSOLE_OUTPUT 96
#define DAH_CONSOLE_HISTORY 32
#define DAH_CONSOLE_QUEUE 8
static HWND g_dah_console_window;
static HFONT g_dah_console_font;
static SRWLOCK g_dah_console_lock = SRWLOCK_INIT;
static volatile LONG g_dah_console_open;
static volatile LONG g_dah_console_escape_latch;
static char g_dah_console_output[DAH_CONSOLE_OUTPUT][DAH_CONSOLE_LINE];
static unsigned g_dah_console_output_count;
static char g_dah_console_history[DAH_CONSOLE_HISTORY][DAH_CONSOLE_LINE];
static unsigned g_dah_console_history_count;
static unsigned g_dah_console_history_back;
static char g_dah_console_input[DAH_CONSOLE_LINE];
static unsigned g_dah_console_cursor;
static char g_dah_console_queue[DAH_CONSOLE_QUEUE][DAH_CONSOLE_LINE];
static unsigned g_dah_console_queue_read, g_dah_console_queue_write;

int dah_console_is_open(void)
{
    return InterlockedCompareExchange(&g_dah_console_open, 0, 0) != 0;
}

/* Closing the console must not send the held Esc key to the game's BACK
 * binding. The game calls this only while focused and outside internal mode. */
int dah_console_key_blocked(int virtual_key)
{
    if (virtual_key == VK_ESCAPE &&
        InterlockedCompareExchange(&g_dah_console_escape_latch,0,0)) {
        if (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
            InterlockedExchange(&g_dah_console_escape_latch,0);
        return 1;
    }
    return 0;
}

int dah_host_has_input_focus(void)
{
    HWND foreground = GetForegroundWindow();
    return foreground && (foreground == g_game_window ||
        IsChild(g_game_window, foreground));
}

void dah_console_write(const char *format, ...)
{
    char line[DAH_CONSOLE_LINE];
    va_list args;
    va_start(args, format);
    vsnprintf(line, sizeof(line), format, args);
    va_end(args);
    line[sizeof(line)-1] = 0;
    AcquireSRWLockExclusive(&g_dah_console_lock);
    strcpy(g_dah_console_output[g_dah_console_output_count++ % DAH_CONSOLE_OUTPUT], line);
    ReleaseSRWLockExclusive(&g_dah_console_lock);
    fprintf(stderr, "[DAH-CONSOLE] %s\n", line);
    fflush(stderr);
    if (g_dah_console_window) InvalidateRect(g_dah_console_window, NULL, FALSE);
}

int dah_console_take_command(char *line, size_t capacity)
{
    int ready = 0;
    AcquireSRWLockExclusive(&g_dah_console_lock);
    if (g_dah_console_queue_read != g_dah_console_queue_write) {
        const char *source = g_dah_console_queue[g_dah_console_queue_read % DAH_CONSOLE_QUEUE];
        if (capacity > strlen(source)) {
            strcpy(line, source);
            ++g_dah_console_queue_read;
            ready = 1;
        }
    }
    ReleaseSRWLockExclusive(&g_dah_console_lock);
    return ready;
}

static void dah_console_help(void)
{
    dah_console_write("Commands: help, clear, status, capture, capture_console");
    dah_console_write("Game commands: load_level <map>, spawn <npc>, give_weapon <name>, giveall_weapons");
    dah_console_write("Maps: farm rockwell santa area42 union capitol cptlboss");
    dah_console_write("Weapons: cortex brainextractor zapomatic analprobe mattermove abducto");
    dah_console_write("  holobob holobobhelper hypnoray deathray destructoray iondetonator");
    dah_console_write("  sonicboom quantum brainray");
    dah_console_write("NPCs: npc_cow npc_farmer npc_cop npc_soldier npc_scientist npc_gman");
    dah_console_write("NPC availability depends on the current map's original assets.");
    dah_console_write("Enter submits; Up/Down history; Tab completes; ` or Esc closes.");
}

static int dah_console_save_capture(void);

static void dah_console_submit(void)
{
    char *line = g_dah_console_input;
    size_t length;
    int full;
    while (*line == ' ') ++line;
    length = strlen(line);
    while (length && line[length-1] == ' ') line[--length] = 0;
    if (!length) return;
    strcpy(g_dah_console_history[g_dah_console_history_count++ % DAH_CONSOLE_HISTORY], line);
    g_dah_console_history_back = 0;
    dah_console_write("> %s", line);
    if (!_stricmp(line, "help")) dah_console_help();
    else if (!_stricmp(line, "capture_console")) {
        if (dah_console_save_capture())
            dah_console_write("Console saved to dah_console_%lu.bmp in the game folder.", GetCurrentProcessId());
        else dah_console_write("Could not save the console image in the game folder.");
    }
    else if (!_stricmp(line, "clear")) {
        AcquireSRWLockExclusive(&g_dah_console_lock);
        g_dah_console_output_count = 0;
        ReleaseSRWLockExclusive(&g_dah_console_lock);
    } else {
        AcquireSRWLockExclusive(&g_dah_console_lock);
        full = g_dah_console_queue_write - g_dah_console_queue_read >= DAH_CONSOLE_QUEUE;
        if (!full) strcpy(g_dah_console_queue[g_dah_console_queue_write++ % DAH_CONSOLE_QUEUE], line);
        ReleaseSRWLockExclusive(&g_dah_console_lock);
        if (full) dah_console_write("Command queue full; wait for the game to finish its current operation.");
    }
    g_dah_console_input[0] = 0;
    g_dah_console_cursor = 0;
    InvalidateRect(g_dah_console_window, NULL, FALSE);
}

static void dah_console_complete(void)
{
    static const char *const commands[] = {
        "help", "clear", "status", "capture", "capture_console", "load_level farm", "load_level rockwell",
        "load_level santa", "load_level area42", "load_level union",
        "load_level capitol", "load_level cptlboss", "spawn npc_cow",
        "spawn npc_farmer", "spawn npc_cop", "spawn npc_soldier",
        "spawn npc_scientist", "spawn npc_gman", "giveall_weapons",
        "give_weapon cortex", "give_weapon brainextractor", "give_weapon zapomatic",
        "give_weapon analprobe", "give_weapon mattermove", "give_weapon abducto",
        "give_weapon holobob", "give_weapon holobobhelper", "give_weapon hypnoray",
        "give_weapon deathray", "give_weapon destructoray", "give_weapon iondetonator",
        "give_weapon sonicboom", "give_weapon quantum", "give_weapon brainray"
    };
    unsigned i, matches = 0;
    const char *match = NULL;
    size_t n = strlen(g_dah_console_input);
    for (i = 0; i < sizeof(commands)/sizeof(commands[0]); ++i)
        if (!_strnicmp(commands[i], g_dah_console_input, n)) { ++matches; match = commands[i]; }
    if (matches == 1) {
        strcpy(g_dah_console_input, match);
        g_dah_console_cursor = (unsigned)strlen(match);
    } else if (matches) {
        for (i = 0; i < sizeof(commands)/sizeof(commands[0]); ++i)
            if (!_strnicmp(commands[i], g_dah_console_input, n)) dah_console_write("  %s", commands[i]);
    }
}

static void dah_console_resize(void)
{
    RECT rect;
    if (!g_dah_console_window || !GetClientRect(g_game_window, &rect)) return;
    SetWindowPos(g_dah_console_window, HWND_TOP, 0, 0, rect.right,
        rect.bottom < 240 ? rect.bottom : (rect.bottom * 3 / 5), SWP_NOACTIVATE);
}

static void dah_console_toggle(int show)
{
    if (!g_dah_console_window) return;
    InterlockedExchange(&g_dah_console_open, show ? 1 : 0);
    dah_console_resize();
    ShowWindow(g_dah_console_window, show ? SW_SHOWNOACTIVATE : SW_HIDE);
    if (dah_host_has_input_focus()) SetFocus(show ? g_dah_console_window : g_game_window);
    fprintf(stderr, "[DAH-CONSOLE] %s\n", show ? "opened" : "closed");
    fflush(stderr);
}

static LRESULT CALLBACK dah_console_proc(HWND hwnd, UINT message, WPARAM wp, LPARAM lp)
{
    unsigned length = (unsigned)strlen(g_dah_console_input);
    if (message == WM_KEYDOWN) {
        if (wp == VK_OEM_3 || wp == VK_ESCAPE) {
            if (!(lp & (1L<<30))) {
                if (wp == VK_ESCAPE) InterlockedExchange(&g_dah_console_escape_latch,1);
                dah_console_toggle(0);
            }
            return 0;
        }
        if (wp == VK_UP || wp == VK_DOWN) {
            unsigned maximum = g_dah_console_history_count < DAH_CONSOLE_HISTORY ?
                g_dah_console_history_count : DAH_CONSOLE_HISTORY;
            if (wp == VK_UP && g_dah_console_history_back < maximum) ++g_dah_console_history_back;
            if (wp == VK_DOWN && g_dah_console_history_back) --g_dah_console_history_back;
            if (g_dah_console_history_back)
                strcpy(g_dah_console_input, g_dah_console_history[(g_dah_console_history_count - g_dah_console_history_back) % DAH_CONSOLE_HISTORY]);
            else g_dah_console_input[0] = 0;
            g_dah_console_cursor = (unsigned)strlen(g_dah_console_input);
        } else if (wp == VK_LEFT && g_dah_console_cursor) --g_dah_console_cursor;
        else if (wp == VK_RIGHT && g_dah_console_cursor < length) ++g_dah_console_cursor;
        else if (wp == VK_HOME) g_dah_console_cursor = 0;
        else if (wp == VK_END) g_dah_console_cursor = length;
        else if (wp == VK_DELETE && g_dah_console_cursor < length)
            memmove(g_dah_console_input+g_dah_console_cursor, g_dah_console_input+g_dah_console_cursor+1, length-g_dah_console_cursor);
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }
    if (message == WM_CHAR) {
        if (wp == '`' || wp == '~' || wp == 27) return 0;
        if (wp == '\r') dah_console_submit();
        else if (wp == '\t') dah_console_complete();
        else if (wp == '\b' && g_dah_console_cursor) {
            memmove(g_dah_console_input+g_dah_console_cursor-1, g_dah_console_input+g_dah_console_cursor, length-g_dah_console_cursor+1);
            --g_dah_console_cursor;
        } else if (wp >= 32 && wp < 127 && length+1 < DAH_CONSOLE_LINE) {
            memmove(g_dah_console_input+g_dah_console_cursor+1, g_dah_console_input+g_dah_console_cursor, length-g_dah_console_cursor+1);
            g_dah_console_input[g_dah_console_cursor++] = (char)wp;
        }
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;
    }
    if (message == WM_PAINT || message == WM_PRINTCLIENT) {
        PAINTSTRUCT paint;
        RECT rect, row;
        HDC dc = message == WM_PRINTCLIENT ? (HDC)wp : BeginPaint(hwnd, &paint);
        HBRUSH background = CreateSolidBrush(RGB(9, 17, 28));
        unsigned count, first, i;
        int available;
        SIZE cursor;
        GetClientRect(hwnd, &rect);
        FillRect(dc, &rect, background);
        DeleteObject(background);
        SelectObject(dc, g_dah_console_font);
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, RGB(88, 230, 209));
        { const char *title = "DAH! DEVELOPER CONSOLE    ` / Esc: close    help: commands";
          TextOutA(dc, 10, 8, title, (int)strlen(title)); }
        SetTextColor(dc, RGB(219, 228, 237));
        available = (rect.bottom - 68) / 18;
        if (available < 0) available = 0;
        AcquireSRWLockShared(&g_dah_console_lock);
        count = g_dah_console_output_count;
        first = count > (unsigned)available ? count - available : 0;
        if (count-first > DAH_CONSOLE_OUTPUT) first = count - DAH_CONSOLE_OUTPUT;
        for (i = first; i < count; ++i) {
            const char *line = g_dah_console_output[i % DAH_CONSOLE_OUTPUT];
            SetRect(&row, 10, 32+(int)(i-first)*18, rect.right-8, 50+(int)(i-first)*18);
            DrawTextA(dc, line, -1, &row, DT_SINGLELINE | DT_NOPREFIX | DT_END_ELLIPSIS);
        }
        ReleaseSRWLockShared(&g_dah_console_lock);
        SetTextColor(dc, RGB(120, 255, 157));
        TextOutA(dc, 10, rect.bottom-28, "> ", 2);
        TextOutA(dc, 26, rect.bottom-28, g_dah_console_input, (int)length);
        GetTextExtentPoint32A(dc, g_dah_console_input, g_dah_console_cursor, &cursor);
        TextOutA(dc, 26+cursor.cx, rect.bottom-28, "_", 1);
        if (message == WM_PAINT) EndPaint(hwnd, &paint);
        return 0;
    }
    if (message == WM_ERASEBKGND) return 1;
    return DefWindowProcA(hwnd, message, wp, lp);
}

/* Render this HWND inside its owning process. A hidden child cannot be
 * reliably painted into another process's HDC via PrintWindow. */
static int dah_console_save_capture(void)
{
    RECT rect;
    BITMAPINFO info = {0};
    BITMAPFILEHEADER header = {0};
    HDC source, memory;
    HBITMAP bitmap;
    HGDIOBJ previous;
    void *pixels;
    FILE *file;
    char filename[80];
    size_t bytes;
    int ok = 0;
    if (!g_dah_console_window || !GetClientRect(g_dah_console_window,&rect) ||
        rect.right <= 0 || rect.bottom <= 0 || rect.right > 8192 || rect.bottom > 4096) return 0;
    bytes=(size_t)rect.right*rect.bottom*4u;
    if (bytes > 64u*1024u*1024u) return 0;
    info.bmiHeader.biSize=sizeof(info.bmiHeader);
    info.bmiHeader.biWidth=rect.right;
    info.bmiHeader.biHeight=-rect.bottom;
    info.bmiHeader.biPlanes=1;
    info.bmiHeader.biBitCount=32;
    info.bmiHeader.biCompression=BI_RGB;
    source=GetDC(g_dah_console_window);
    if (!source) return 0;
    memory=CreateCompatibleDC(source);
    if (!memory) { ReleaseDC(g_dah_console_window,source); return 0; }
    bitmap=CreateDIBSection(source,&info,DIB_RGB_COLORS,&pixels,NULL,0);
    if (!bitmap) { DeleteDC(memory); ReleaseDC(g_dah_console_window,source); return 0; }
    previous=SelectObject(memory,bitmap);
    SendMessageA(g_dah_console_window,WM_PRINTCLIENT,(WPARAM)memory,PRF_CLIENT);
    GdiFlush();
    snprintf(filename,sizeof(filename),"dah_console_%lu.bmp",GetCurrentProcessId());
    file=fopen(filename,"wb");
    if (file) {
        header.bfType=0x4D42;
        header.bfOffBits=sizeof(header)+sizeof(info.bmiHeader);
        header.bfSize=(DWORD)(header.bfOffBits+bytes);
        ok=fwrite(&header,sizeof(header),1,file)==1 &&
            fwrite(&info.bmiHeader,sizeof(info.bmiHeader),1,file)==1 &&
            fwrite(pixels,bytes,1,file)==1;
        if (fclose(file)!=0) ok=0;
    }
    SelectObject(memory,previous);
    DeleteObject(bitmap);
    DeleteDC(memory);
    ReleaseDC(g_dah_console_window,source);
    return ok;
}

static int dah_console_create(HINSTANCE instance)
{
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = dah_console_proc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = "DestroyAllHumansDeveloperConsole";
    if (!RegisterClassA(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) return 0;
    g_dah_console_font = CreateFontA(-16, 0, 0, 0, FW_NORMAL, FALSE, FALSE,
        FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, FIXED_PITCH | FF_MODERN, "Consolas");
    if (!g_dah_console_font) g_dah_console_font = (HFONT)GetStockObject(ANSI_FIXED_FONT);
    g_dah_console_window = CreateWindowExA(0, wc.lpszClassName, "Developer console",
        WS_CHILD | WS_CLIPSIBLINGS, 0, 0, 640, 288, g_game_window, NULL, instance, NULL);
    if (!g_dah_console_window) return 0;
    dah_console_help();
    return 1;
}
