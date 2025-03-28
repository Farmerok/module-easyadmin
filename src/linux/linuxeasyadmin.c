#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <X11/extensions/XTest.h>

// System control functions
void system_lock_screen() { system("xdg-screensaver lock"); }
void system_monitor_off() { system("xset dpms force off"); }
void system_standby() { system("systemctl suspend"); }
void system_log_off() { system("pkill -KILL -u $(whoami)"); }
void system_reboot() { system("reboot"); }
void system_shutdown() { system("poweroff"); }

// Sound control using pactl (PipeWire/PulseAudio)
void sound_volume_down() { system("pactl set-sink-volume @DEFAULT_SINK@ -5%"); }
void sound_volume_up() { system("pactl set-sink-volume @DEFAULT_SINK@ +5%"); }
void sound_play_pause() { system("playerctl play-pause"); }
void sound_next_track() { system("playerctl next"); }
void sound_prev_track() { system("playerctl previous"); }
void sound_stop() { system("playerctl stop"); }
void sound_mute() { system("pactl set-sink-mute @DEFAULT_SINK@ toggle"); }
void sound_set_volume(int level) {
    char cmd[50];
    snprintf(cmd, sizeof(cmd), "pactl set-sink-volume @DEFAULT_SINK@ %d%%", level);
    system(cmd);
}

// Managment process
void process_kill_by_name(const char *process) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "pkill %s", process);
    system(cmd);
}
void process_kill_by_pid(int pid) {
    kill(pid, SIGKILL);
}
void display_system_info() { system("uname -a && lsb_release -a"); }
void open_program(const char *path) {
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "%s &", path);
    system(cmd);
}
void toggle_wifi(int enable) {
    system(enable ? "nmcli radio wifi on" : "nmcli radio wifi off");
}
void set_screen_brightness(int brightness) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "xrandr --output eDP-0 --brightness %.2f", brightness / 100.0);
    system(cmd);
}

void print_usage(const char *program_name) {
    printf("Usage: %s <command> [args]\n", program_name);
    printf("Commands:\n");
    printf("  lockscreen\n  monitoroff\n  standby\n  logoff\n  reboot\n  shutdown\n");
    printf("  volumedown\n  volumeup\n  mute\n  setvolume <0-100>\n");
    printf("  playpause\n  next\n  prev\n  stop\n");
    printf("  kill <process>\n  killpid <PID>\n  sysinfo\n  open <path>\n  wifi <on|off>\n  brightness <0-100>\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) { print_usage(argv[0]); return 1; }
    if (strcmp(argv[1], "lockscreen") == 0) system_lock_screen();
    else if (strcmp(argv[1], "monitoroff") == 0) system_monitor_off();
    else if (strcmp(argv[1], "standby") == 0) system_standby();
    else if (strcmp(argv[1], "logoff") == 0) system_log_off();
    else if (strcmp(argv[1], "reboot") == 0) system_reboot();
    else if (strcmp(argv[1], "shutdown") == 0) system_shutdown();
    else if (strcmp(argv[1], "volumedown") == 0) sound_volume_down();
    else if (strcmp(argv[1], "volumeup") == 0) sound_volume_up();
    else if (strcmp(argv[1], "playpause") == 0) sound_play_pause();
    else if (strcmp(argv[1], "next") == 0) sound_next_track();
    else if (strcmp(argv[1], "prev") == 0) sound_prev_track();
    else if (strcmp(argv[1], "stop") == 0) sound_stop();
    else if (strcmp(argv[1], "mute") == 0) sound_mute();
    else if (strcmp(argv[1], "setvolume") == 0 && argc == 3) sound_set_volume(atoi(argv[2]));
    else if (strcmp(argv[1], "kill") == 0 && argc == 3) process_kill_by_name(argv[2]);
    else if (strcmp(argv[1], "killpid") == 0 && argc == 3) process_kill_by_pid(atoi(argv[2]));
    else if (strcmp(argv[1], "sysinfo") == 0) display_system_info();
    else if (strcmp(argv[1], "open") == 0 && argc == 3) open_program(argv[2]);
    else if (strcmp(argv[1], "wifi") == 0 && argc == 3) toggle_wifi(strcmp(argv[2], "on") == 0);
    else if (strcmp(argv[1], "brightness") == 0 && argc == 3) set_screen_brightness(atoi(argv[2]));
    else { fprintf(stderr, "Unknown command: %s\n", argv[1]); print_usage(argv[0]); return 1; }
    return 0;
}
