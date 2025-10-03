#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>

#define DEFAULT_INTERVAL 5
#define DEFAULT_LOGFILE "/tmp/assignment_sensor.log"
#define FALLBACK_LOGFILE "/var/tmp/assignment_sensor.log"
#define DEFAULT_DEVICE "/dev/urandom"

static volatile int keep_running = 1;

void handle_sigterm(int sig) {
    (void)sig; // Suppress unused parameter warning
    keep_running = 0;
}

void format_time_iso8601(char *buffer, size_t size) {
    struct timespec ts;
    struct tm tm;

    clock_gettime(CLOCK_REALTIME, &ts);
    gmtime_r(&ts.tv_sec, &tm);
    snprintf(buffer, size, "%04d-%02d-%02dT%02d:%02d:%02d.%03ldZ",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec, ts.tv_nsec / 1000000);
}

int main(int argc, char *argv[]) {
    int interval = DEFAULT_INTERVAL;
    const char *logfile = DEFAULT_LOGFILE;
    const char *device = DEFAULT_DEVICE;

    // Parse CLI arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--interval") == 0 && i + 1 < argc) {
            interval = atoi(argv[++i]);
        } else if (strcmp(argv[i], "--logfile") == 0 && i + 1 < argc) {
            logfile = argv[++i];
        } else if (strcmp(argv[i], "--device") == 0 && i + 1 < argc) {
            device = argv[++i];
        } else {
            fprintf(stderr, "Usage: %s [--interval N] [--logfile FILE] [--device FILE]\n", argv[0]);
            return EXIT_FAILURE;
        }
    }

    // Open log file
    FILE *log_fp = fopen(logfile, "a");
    if (!log_fp) {
        perror("Failed to open log file, trying fallback");
        logfile = FALLBACK_LOGFILE;
        log_fp = fopen(logfile, "a");
        if (!log_fp) {
            perror("Failed to open fallback log file");
            return EXIT_FAILURE;
        }
    }

    // Set line buffering for the log file
    setvbuf(log_fp, NULL, _IOLBF, 0);

    // Open device file
    int device_fd = open(device, O_RDONLY);
    if (device_fd < 0) {
        perror("Failed to open device file");
        fclose(log_fp);
        return EXIT_FAILURE;
    }

    // Handle SIGTERM
    struct sigaction sa;
    sa.sa_handler = handle_sigterm;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGTERM, &sa, NULL);

    // Main loop
    while (keep_running) {
        uint32_t random_value;
        ssize_t bytes_read = read(device_fd, &random_value, sizeof(random_value));
        if (bytes_read != sizeof(random_value)) {
            perror("Failed to read from device");
            break;
        }

        char timestamp[32];
        format_time_iso8601(timestamp, sizeof(timestamp));

        fprintf(log_fp, "%s | 0x%08X\n", timestamp, random_value);

        sleep(interval);
    }

    // Cleanup
    close(device_fd);
    fclose(log_fp);

    return EXIT_SUCCESS;
}
