#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

static void max_volume(void) {
    for (int i = 0; i < 60; i++) {
        keybd_event(VK_VOLUME_UP, 0, 0, 0);
        keybd_event(VK_VOLUME_UP, 0, KEYEVENTF_KEYUP, 0);
    }
}

static void force_speakers(void) {
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    char *slash = strrchr(path, '\\');
    if (slash) *(slash + 1) = 0;
    strcat(path, "nircmd.exe");
    if (GetFileAttributesA(path) != INVALID_FILE_ATTRIBUTES) {
        ShellExecuteA(NULL, "open", path,
            "setdefaultsounddevice Speakers", NULL, SW_HIDE);
        Sleep(1500);
    }
}

int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR c, int s) {
    force_speakers();
    max_volume();
    ShellExecuteA(NULL, "open",
        "https://youtu.be/ppreN8ZaG4Y", NULL, NULL, SW_SHOWNORMAL);
    Sleep(60000);
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_F4, 0, 0, 0);
    keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    return 0;
}
