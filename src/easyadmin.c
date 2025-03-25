#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <mmsystem.h>
#include <powrprof.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "PowrProf.lib")  // For power management

// Screen lock
void lock_screen() {
    LockWorkStation();
}

// Turn off monitor
void monitor_off() {
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM) 2);
}

// Enter standby mode
void standby() {
    SetSystemPowerState(TRUE, FALSE);
}

// Log off
void log_off() {
    ExitWindowsEx(EWX_LOGOFF, 0);
}

// Reboot
void reboot() {
    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM);
}

// Shutdown
void shutdown_pc() {
    ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, SHTDN_REASON_MAJOR_OPERATINGSYSTEM);
}

//=======[ Sound Management ]=======//
// Decrease volume
void volume_down() {
    keybd_event(VK_VOLUME_DOWN, 0, 0, 0);
    keybd_event(VK_VOLUME_DOWN, 0, KEYEVENTF_KEYUP, 0);
}

// Increase volume
void volume_up() {
    keybd_event(VK_VOLUME_UP, 0, 0, 0);
    keybd_event(VK_VOLUME_UP, 0, KEYEVENTF_KEYUP, 0);
}

// Mute volume
void mute_volume() {
    keybd_event(VK_VOLUME_MUTE, 0, 0, 0);
    keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0);
}

// Next track
void next_track() {
    keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0);
    keybd_event(VK_MEDIA_NEXT_TRACK, 0, KEYEVENTF_KEYUP, 0);
}

// Previous track
void prev_track() {
    keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0);
    keybd_event(VK_MEDIA_PREV_TRACK, 0, KEYEVENTF_KEYUP, 0);
}

// Play/Pause
void play_pause() {
    keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0);
    keybd_event(VK_MEDIA_PLAY_PAUSE, 0, KEYEVENTF_KEYUP, 0);
}

//====[ CD ROM ]====//
// Open CD-ROM
void cdrom_open(char drive) {
    char command[32];
    sprintf(command, "set %cdaudio door open", drive);
    mciSendString(command, NULL, 0, NULL);
}

// Close CD-ROM
void cdrom_close(char drive) {
    char command[32];
    sprintf(command, "set %cdaudio door closed", drive);
    mciSendString(command, NULL, 0, NULL);
}

// Kill process by name
void kill_process(const char *process) {
    char command[256];
    sprintf(command, "taskkill /IM %s /F", process);
    system(command);
}

// Kill process by PID
void kill_pid(int pid) {
    char command[64];
    sprintf(command, "taskkill /PID %d /F", pid);
    system(command);
}

// Kill all not responding processes
void kill_not_responding() {
    system("taskkill /FI \"STATUS eq NOT RESPONDING\" /F");
}

// screen brightness (0-100%)
void set_brightness(int brightness) {
    if (brightness < 0) brightness = 0;
    if (brightness > 100) brightness = 100;

    // Get monitor handle
    HANDLE hMonitor = CreateFileA("\\\\.\\LCD", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hMonitor == INVALID_HANDLE_VALUE) {
        printf("Failed to change brightness.\n");
        return;
    }

    DWORD dwBrightness = (brightness * 255) / 100;
    DeviceIoControl(hMonitor, 0x8010204C, &dwBrightness, sizeof(dwBrightness), NULL, 0, NULL, NULL);
    CloseHandle(hMonitor);
}

// Enable/disable Wi-Fi
void toggle_wifi(int enable) {
    if (enable) {
        system("netsh interface set interface \"Wi-Fi\" enable");} else {
        system("netsh interface set interface \"Wi-Fi\" disable");}}

// Display system information
void system_info() {
    system("cmd /k systeminfo");
}

// Open program
void open_program(const char *path) {
    ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [lockscreen | volumedown | volumeup | volumemute | nexttrack | prevtrack | playpause | monitoroff | standby | logoff | reboot | shutdown | kill <process> | killpid <PID> | killnotresp | cdrom <drive> open | cdrom <drive> close | brightness <0-100> | wifi <on|off> | sysinfo | open <path>]\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "lockscreen") == 0) {
        lock_screen();
    } else if (strcmp(argv[1], "volumedown") == 0) {
        volume_down();
    } else if (strcmp(argv[1], "volumeup") == 0) {
        volume_up();
    } else if (strcmp(argv[1], "volumemute") == 0) {
        mute_volume();
    } else if (strcmp(argv[1], "nexttrack") == 0) {
        next_track();
    } else if (strcmp(argv[1], "prevtrack") == 0) {
        prev_track();
    } else if (strcmp(argv[1], "playpause") == 0) {
        play_pause();
    } else if (strcmp(argv[1], "monitoroff") == 0) {
        monitor_off();
    } else if (strcmp(argv[1], "standby") == 0) {
        standby();
    } else if (strcmp(argv[1], "logoff") == 0) {
        log_off();
    } else if (strcmp(argv[1], "reboot") == 0) {
        reboot();
    } else if (strcmp(argv[1], "shutdown") == 0) {
        shutdown_pc();
    } else if (argc == 3 && strcmp(argv[1], "kill") == 0) {
        kill_process(argv[2]);
    } else if (argc == 3 && strcmp(argv[1], "killpid") == 0) {
        kill_pid(atoi(argv[2]));
    } else if (strcmp(argv[1], "killnotresp") == 0) {
        kill_not_responding();
    } else if (argc == 4 && strcmp(argv[1], "cdrom") == 0) {
        if (strcmp(argv[3], "open") == 0) {
            cdrom_open(argv[2][0]);
        } else if (strcmp(argv[3], "close") == 0) {
            cdrom_close(argv[2][0]);
        } else {
            printf("Unknown command: %s %s %s\n", argv[1], argv[2], argv[3]);
        }
    } else if (argc == 3 && strcmp(argv[1], "brightness") == 0) {
        set_brightness(atoi(argv[2]));
    } else if (argc == 3 && strcmp(argv[1], "wifi") == 0) {
        toggle_wifi(strcmp(argv[2], "on") == 0);
    } else if (strcmp(argv[1], "sysinfo") == 0) {
        system_info();
    } else if (argc == 3 && strcmp(argv[1], "open") == 0) {
        open_program(argv[2]);
    } else {
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}