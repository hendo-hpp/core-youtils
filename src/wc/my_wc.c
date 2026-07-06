#include "my_wc.h"
#include "util.h"

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#define BUFFER_SIZE 4096

static wc_totals totals = {0};

void handle_flags(const char *flags, wc_config *config) {
    while (*flags) {
        switch (*flags) {
            case 'c':
                config->print_byte_count = true;
                break;
            case 'm':
                config->print_char_count = true;
                break;
            case 'l':
                config->print_newl_count = true;
                break;
            case 'L':
                config->print_line_len = true;
                break;
            case 'w':
                config->print_word_count = true;
                break;
            default:
                log_flag_error(*flags);
                _exit(1);
        }
        flags++;
    }
}

void process_fd(int fd, const wc_config *config) {
    char buff[BUFFER_SIZE];

    int fd_newl_count = 0;
    int fd_byte_count = 0;
    int fd_char_count = 0;
    int fd_word_count = 0;
    int fd_max_line_len = 0;

    bool in_word = false;

    ssize_t num_bytes;
    while((num_bytes = read(fd, buff, BUFFER_SIZE)) > 0) {
        int curr_line_len = 0;

        for (ssize_t i = 0; i < num_bytes; i++) {
            char curr_byte = buff[i];

            if (is_whitespace(curr_byte)) {
                in_word = false;
            } else if (!in_word) {
                ++fd_word_count;
                in_word = true;
            }

            if (curr_byte == '\n') {
                ++fd_newl_count;
                if (curr_line_len > fd_max_line_len) {
                    fd_max_line_len = curr_line_len;
                }
                curr_line_len = 0;
            } else {
                ++curr_line_len;
            }

            ++fd_byte_count;
            if ((curr_byte & 0xC0) != 0x80) {
                ++fd_char_count;
            }
        }
    }

    int num_flags = 0;
    if (config->print_newl_count) {
        writef_int(fd_newl_count);
        write(STDOUT_FILENO, " ", 1);
        ++num_flags;
    }
    if (config->print_word_count) {
        writef_int(fd_word_count);
        write(STDOUT_FILENO, " ", 1);
        ++num_flags;
    }
    if (config->print_byte_count) {
        writef_int(fd_byte_count);
        write(STDOUT_FILENO, " ", 1);
        ++num_flags;
    }
    if (config->print_char_count) {
        writef_int(fd_char_count);
        write(STDOUT_FILENO, " ", 1);
        ++num_flags;
    }
    if (config->print_line_len) {
        writef_int(fd_max_line_len);
        write(STDOUT_FILENO, " ", 1);
        ++num_flags;
    }

    // default prints new lines, words, and bytes
    if (num_flags == 0) {
        writef_int(fd_newl_count);
        write(STDOUT_FILENO, " ", 1);
        writef_int(fd_word_count);
        write(STDOUT_FILENO, " ", 1);
        writef_int(fd_byte_count);
        write(STDOUT_FILENO, " ", 1);
    }

    totals.total_byte_count += fd_byte_count;
    totals.total_char_count += fd_char_count;
    totals.total_newl_count += fd_newl_count;
    totals.total_word_count += fd_word_count;
    if (fd_max_line_len > totals.total_max_line_len) {
        totals.total_max_line_len = fd_max_line_len;
    }
}

int main(int argc, char **argv) {
    wc_config conf = {0};

    int first_arg_idx = INT_MAX;
    int num_files = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            handle_flags(argv[i] + 1, &conf);
        }
        else if (i < first_arg_idx) {
            first_arg_idx = i;
        }
    }

    if (first_arg_idx == INT_MAX) {
        process_fd(STDIN_FILENO, &conf);
        write(STDOUT_FILENO, "\n", 1);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            continue;
        }

        int in_fd = open(argv[i], O_RDONLY);
        if (in_fd < 0) {
            log_file_open_error(argv[i]);
            continue;
        }

        process_fd(in_fd, &conf);
        write(STDOUT_FILENO, argv[i], lenstr(argv[i]));
        write(STDOUT_FILENO, "\n", 1);
        close(in_fd);
        ++num_files;
    }

    if (num_files > 1) {
        writef_int(totals.total_newl_count);
        write(STDOUT_FILENO, " ", 1);
        writef_int(totals.total_word_count);
        write(STDOUT_FILENO, " ", 1);
        writef_int(totals.total_byte_count);
        write(STDOUT_FILENO, " ", 1);
        write(STDOUT_FILENO, "total\n", 6);
    }

    return 0;
}