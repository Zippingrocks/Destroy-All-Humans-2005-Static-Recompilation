#include <windows.h>
#include <xinput.h>
#include <stdio.h>

int main(void)
{
    unsigned connected = 0;
    for (DWORD port = 0; port < XUSER_MAX_COUNT; ++port) {
        XINPUT_STATE state = {0};
        DWORD result = XInputGetState(port, &state);
        printf("port=%lu result=%lu connected=%u packet=%lu sticks=%d,%d,%d,%d\n",
               (unsigned long)port, (unsigned long)result,
               result == ERROR_SUCCESS ? 1u : 0u,
               (unsigned long)state.dwPacketNumber,
               (int)state.Gamepad.sThumbLX, (int)state.Gamepad.sThumbLY,
               (int)state.Gamepad.sThumbRX, (int)state.Gamepad.sThumbRY);
        if (result == ERROR_SUCCESS) ++connected;
    }
    printf("connected_ports=%u\n", connected);
    return connected ? 0 : 2;
}
