#include "util.h"

#include <limits.h>
#include <string.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif // PATH_MAX

void log_flag_error(const char flag) {
    char buffer[32];
    int buffer_idx = 0;

    const char *msg = "invalid option: -";
    while (*msg) {
        buffer[buffer_idx++] = *msg++;
    }

    buffer[buffer_idx++] = flag;
    buffer[buffer_idx++] = '\n';

    write(STDERR_FILENO, buffer, buffer_idx);
}

void log_file_open_error(const char *file_name) {
    char buffer[PATH_MAX + 32];
    int buffer_idx = 0;

    const char *msg = "could not find file: ";

    while (*msg) {
        buffer[buffer_idx++] = *msg++;
    }

    while (*file_name) {
        buffer[buffer_idx++] = *file_name++;
    }

    buffer[buffer_idx++] = '\n';

    write(STDERR_FILENO, buffer, buffer_idx);
}