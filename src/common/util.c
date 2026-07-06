#include "util.h"

#include <linux/limits.h>
#include <string.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define MAX_INT_LEN 20

#ifndef NAME_MAX 
#define NAME_MAX 255
#endif

size_t lenstr(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = 0;
    while (*str++ != '\0') {
        ++len;
    }
    return len;
}

bool is_whitespace(char c) {
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' ||
            c == '\f');
}

void log_dir_open_error(const char *dir_name) {
    char buff[NAME_MAX + 32];
    int buff_idx = 0;

    const char *msg = "could not open directory: ";

    while (*msg) {
        buff[buff_idx++] = *msg++;
    }

    while (*dir_name) {
        buff[buff_idx++] = *dir_name++;
    }

    buff[buff_idx++] = '\n';

    write(STDOUT_FILENO, buff, buff_idx);
}

void log_file_open_error(const char *file_name) {
    char buff[PATH_MAX + 32];
    int buff_idx = 0;

    const char *msg = "could not find file: ";

    while (*msg) {
        buff[buff_idx++] = *msg++;
    }

    while (*file_name) {
        buff[buff_idx++] = *file_name++;
    }

    buff[buff_idx++] = '\n';

    write(STDERR_FILENO, buff, buff_idx);
}

void log_flag_error(const char flag) {
    char buff[32];
    int buff_idx = 0;

    const char *msg = "invalid option: -";
    while (*msg) {
        buff[buff_idx++] = *msg++;
    }

    buff[buff_idx++] = flag;
    buff[buff_idx++] = '\n';

    write(STDERR_FILENO, buff, buff_idx);
}

void writef_int(int val) {
    if (val == 0) {
        write(STDOUT_FILENO, "0", 1);
        return;
    }

    char buff[MAX_INT_LEN];
    int i = 0;

    while (val > 0) {
        buff[i++] = (val % 10) + '0';
        val /= 10;
    }

    while (--i >= 0) {
        write(STDOUT_FILENO, &buff[i], 1);
    }
}