#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mmsystem.h>
#include <powrprof.h>
#include <initguid.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

// Pragma comments for required libraries
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "PowrProf.lib")
#pragma comment(lib, "mmdevapi.lib")

// Function prototypes for system management
void system_lock_screen(void);
void system_monitor_off(void);
void system_standby(void);
void system_log_off(void);
void system_reboot(void);
void system_shutdown(void);

// Function prototypes for sound management
void sound_volume_down(void);
void sound_volume_up(void);
void sound_set_volume(int level);
void sound_mute(void);
void sound_next_track(void);
void sound_prev_track(void);
void sound_play_pause(void);

// Function prototypes for system utilities
void cdrom_control(char drive, int open);
void process_kill_by_name(const char *process);
void process_kill_by_pid(int pid);
void process_kill_not_responding(void);
void display_system_info(void);
void open_program(const char *path);
void toggle_wifi(int enable);
void set_screen_brightness(int brightness);

// Implementations of system management functions
void system_lock_screen(void) {LockWorkStation();}
void system_monitor_off(void) {SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, (LPARAM)2);}
void system_standby(void) {SetSystemPowerState(TRUE, FALSE);}
void system_log_off(void) {ExitWindowsEx(EWX_LOGOFF, 0);}
void system_reboot(void) {ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);}
void system_shutdown(void) {ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);}

// Implementations of sound management functions
void sound_volume_down(void) {keybd_event(VK_VOLUME_DOWN, 0, 0, 0); keybd_event(VK_VOLUME_DOWN, 0, KEYEVENTF_KEYUP, 0);}
void sound_volume_up(void) {keybd_event(VK_VOLUME_UP, 0, 0, 0);keybd_event(VK_VOLUME_UP, 0, KEYEVENTF_KEYUP, 0);}
void sound_mute(void) {keybd_event(VK_VOLUME_MUTE, 0, 0, 0); keybd_event(VK_VOLUME_MUTE, 0, KEYEVENTF_KEYUP, 0); }
void sound_next_track(void) {keybd_event(VK_MEDIA_NEXT_TRACK, 0, 0, 0); keybd_event(VK_MEDIA_NEXT_TRACK, 0, KEYEVENTF_KEYUP, 0);}
void sound_prev_track(void) {keybd_event(VK_MEDIA_PREV_TRACK, 0, 0, 0); keybd_event(VK_MEDIA_PREV_TRACK, 0, KEYEVENTF_KEYUP, 0);}
void sound_play_pause(void) {keybd_event(VK_MEDIA_PLAY_PAUSE, 0, 0, 0); keybd_event(VK_MEDIA_PLAY_PAUSE, 0, KEYEVENTF_KEYUP, 0);}

void sound_set_volume(int level) {
    HRESULT hr;
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    IMMDevice *defaultDevice = NULL;
    IAudioEndpointVolume *endpointVolume = NULL;

    level = (level < 0) ? 0 : (level > 100) ? 100 : level;
    float fLevel = level / 100.0f;
    
    // COM
    hr = CoInitialize(NULL);
    if (FAILED(hr)) {
        fprintf(stderr, "Failed to initialize COM\n");
        return;
    }

    // Create device
    hr = CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, 
                          &IID_IMMDeviceEnumerator, (void**)&deviceEnumerator);
    if (FAILED(hr)) {
        fprintf(stderr, "Failed to create device enumerator\n");
        CoUninitialize();
        return;
    }
    
    hr = deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, 
                                                           eRender, 
                                                           eConsole, 
                                                           &defaultDevice);
    if (FAILED(hr)) {
        fprintf(stderr, "Failed to get default audio endpoint\n");
        deviceEnumerator->lpVtbl->Release(deviceEnumerator);
        CoUninitialize();
        return;
    }
    
    // Activate volume control
    hr = defaultDevice->lpVtbl->Activate(defaultDevice, 
                                         &IID_IAudioEndpointVolume, 
                                         CLSCTX_ALL, 
                                         NULL, 
                                         (void**)&endpointVolume);
    if (FAILED(hr)) {
        fprintf(stderr, "Failed to get volume control\n");
        defaultDevice->lpVtbl->Release(defaultDevice);
        deviceEnumerator->lpVtbl->Release(deviceEnumerator);
        CoUninitialize();
        return;
    }
    
    // Set
    hr = endpointVolume->lpVtbl->SetMasterVolumeLevelScalar(endpointVolume, fLevel, NULL);
    if (SUCCEEDED(hr)) {
        printf("Volume set to %d%%\n", level);
    } else {
        fprintf(stderr, "Failed to set volume\n");
    }
    
    // Cleanup
    endpointVolume->lpVtbl->Release(endpointVolume);
    defaultDevice->lpVtbl->Release(defaultDevice);
    deviceEnumerator->lpVtbl->Release(deviceEnumerator);
    CoUninitialize();
}

// Implementations of system utilities
void cdrom_control(char drive, int open) {
    char command[32];
    snprintf(command, sizeof(command), "set %cdaudio door %s", 
             drive, open ? "open" : "closed");
    mciSendString(command, NULL, 0, NULL);
}

void process_kill_by_name(const char *process) {
    char command[256];
    snprintf(command, sizeof(command), "taskkill /IM %s /F", process);
    system(command);
}

void process_kill_by_pid(int pid) {
    char command[64];
    snprintf(command, sizeof(command), "taskkill /PID %d /F", pid);
    system(command);
}

void process_kill_not_responding(void) {system("taskkill /FI \"STATUS eq NOT RESPONDING\" /F");}
void display_system_info(void) {system("cmd /k systeminfo");}
void open_program(const char *path) {ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWNORMAL);}

void toggle_wifi(int enable) {
    system(enable 
        ? "netsh interface set interface \"Wi-Fi\" enable" 
        : "netsh interface set interface \"Wi-Fi\" disable");
}

void set_screen_brightness(int brightness) {
    brightness = (brightness < 0) ? 0 : (brightness > 100) ? 100 : brightness;

    HANDLE hMonitor = CreateFileA("\\\\.\\LCD", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hMonitor == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Failed to change brightness.\n");
        return;
    }

    DWORD dwBrightness = (brightness * 255) / 100;
    DeviceIoControl(hMonitor, 0x8010204C, &dwBrightness, sizeof(dwBrightness), NULL, 0, NULL, NULL);
    CloseHandle(hMonitor);
}

// Print usage instructions
void print_usage(const char *program_name) {
    printf("Usage: %s <command> [args]\n\n", program_name);
    printf("System Commands:\n");
    printf("  lockscreen                  - Lock the screen\n");
    printf("  monitoroff                  - Turn off monitor\n");
    printf("  standby                     - Put system in standby mode\n");
    printf("  logoff                      - Log off current user\n");
    printf("  reboot                      - Reboot the system\n");
    printf("  shutdown                    - Shut down the system\n\n");
    
    printf("Sound Commands:\n");
    printf("  volumedown                  - Decrease volume\n");
    printf("  volumeup                    - Increase volume\n");
    printf("  volumemute                  - Mute/unmute volume\n");
    printf("  setvolume <0-100>           - Set volume to specific level\n");
    printf("  nexttrack                   - Next media track\n");
    printf("  prevtrack                   - Previous media track\n");
    printf("  playpause                   - Play/Pause media\n\n");
    
    printf("Process Commands:\n");
    printf("  kill <process>              - Kill process by name\n");
    printf("  killpid <PID>               - Kill process by PID\n");
    printf("  killnotresp                 - Kill not responding processes\n\n");
    
    printf("Other Commands:\n");
    printf("  cdrom <drive> <open|close>  - Control CD-ROM tray\n");
    printf("  brightness <0-100>          - Set screen brightness\n");
    printf("  wifi <on|off>               - Toggle Wi-Fi\n");
    printf("  sysinfo                     - Display system information\n");
    printf("  open <path>                 - Open a program\n");
}

int main(int argc, char *argv[]) {
	//if (argc < 2) return 1;
    if (argc < 2) {print_usage(argv[0]); return 1;}

    // System Management Commands
    if (strcmp(argv[1], "lockscreen") == 0) system_lock_screen();
    else if (strcmp(argv[1], "monitoroff") == 0) system_monitor_off();
    else if (strcmp(argv[1], "standby") == 0) system_standby();
    else if (strcmp(argv[1], "logoff") == 0) system_log_off();
    else if (strcmp(argv[1], "reboot") == 0) system_reboot();
    else if (strcmp(argv[1], "shutdown") == 0) system_shutdown();

    // Sound Management Commands
    else if (strcmp(argv[1], "volumedown") == 0) sound_volume_down();
    else if (strcmp(argv[1], "volumeup") == 0) sound_volume_up();
    else if (strcmp(argv[1], "volumemute") == 0) sound_mute();
    else if (strcmp(argv[1], "setvolume") == 0) {
        if (argc != 3) {
            fprintf(stderr, "Usage: %s setvolume <0-100>\n", argv[0]);
            return 1;
        }
        sound_set_volume(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "nexttrack") == 0) sound_next_track();
    else if (strcmp(argv[1], "prevtrack") == 0) sound_prev_track();
    else if (strcmp(argv[1], "playpause") == 0) sound_play_pause();

    // Process Management Commands
    else if (argc == 3 && strcmp(argv[1], "kill") == 0) process_kill_by_name(argv[2]);
    else if (argc == 3 && strcmp(argv[1], "killpid") == 0) process_kill_by_pid(atoi(argv[2]));
    else if (strcmp(argv[1], "killnotresp") == 0) process_kill_not_responding();

    // CD-ROM Commands
    else if (argc == 4 && strcmp(argv[1], "cdrom") == 0) {cdrom_control(argv[2][0], strcmp(argv[3], "open") == 0);}

    // Other Utility Commands
    else if (argc == 3 && strcmp(argv[1], "brightness") == 0) set_screen_brightness(atoi(argv[2]));
    else if (argc == 3 && strcmp(argv[1], "wifi") == 0) toggle_wifi(strcmp(argv[2], "on") == 0);
    else if (strcmp(argv[1], "sysinfo") == 0) display_system_info();
    else if (argc == 3 && strcmp(argv[1], "open") == 0) open_program(argv[2]);

    // Unknown Command
    else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
