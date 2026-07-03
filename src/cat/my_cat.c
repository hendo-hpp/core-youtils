#include "my_cat.h"

#include "util.h"

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

void handle_flags(const char *flags, MyCatConfig *config) {
    for (int i = 0; flags[i] != '\0'; i++) {
        switch (flags[i]) {
        case 'A':
            config->show_all = true;
            break;
        case 'b':
            config->number_non_blank = true;
            break;
        case 'e':
            config->show_ends_non_printing = true;
            break;
        case 'E':
            config->show_ends = true;
            break;
        case 'n':
            config->number_lines = true;
            break;
        case 's':
            config->squeeze_blank = true;
            break;
        case 't':
            config->show_tabs_non_printing = true;
            break;
        case 'T':
            config->show_tabs = true;
            break;
        case 'v':
            config->show_non_printing = true;
            break;
        default:
            log_flag_error(flags[i]);
            _exit(1);
        }
    }
}

void process_fd(int fd, const MyCatConfig *config) {
    char buffer[BUFFER_SIZE];

    int line_number = 1;
    bool prev_newline = true;

    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        for (ssize_t i = 0; i < bytes_read ; i++) {
            char char_to_write = buffer[i];

            if (config->squeeze_blank) {

            }

            if (config->number_lines) {

            }
            

            write(STDOUT_FILENO, &char_to_write, 1);
        }
    }

    write(STDOUT_FILENO, "\n", 1);
}

int main(int argc, char **argv) {
    MyCatConfig config = {0};

    if (argc == 1) {
        process_fd(STDIN_FILENO, &config);
        return 0;
    }

    // prescan for all flags specified by user
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            handle_flags(argv[i] + 1, &config);
        }
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            continue;
        }

        int input_fd = open(argv[i], O_RDONLY);
        if (input_fd < 0) {
            log_file_open_error(argv[i]);
            continue;
        }

        process_fd(input_fd, &config);
        close(input_fd);
    }

    return 0;
}