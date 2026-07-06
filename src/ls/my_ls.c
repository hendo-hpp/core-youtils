#include "my_ls.h"

#include "util.h"

#include <dirent.h>
#include <limits.h>
#include <stdbool.h>

void handle_flags(const char *flags, ls_config *config) {
    while (*flags) {
        switch (*flags) {
        case 'a':
            config->print_all = true;
            break;
        case 'i':
            config->print_index = true;
            break;
        case 'l':
            config->format_long = true;
            break;
        case 'c':
            config->sort_change_time = true;
            break;
        case 't':
            config->sort_time = true;
            break;
        case 'C':
            config->list_columns = true;
            break;
        case 'm':
            config->format_commas = true;
            break;
        case 'n':
            config->print_literal = true;
            break;
        case 'r':
            config->print_recursive = true;
            break;
        case 's':
            config->print_size = true;
            break;
        default:
            log_flag_error(*flags);
            _exit(1);
        }
        flags++;
    }
}

void process_directory(const char *path, ls_config *config) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        log_dir_open_error(path);
        return;
    }

    struct dirent *dir_entry;
    while ((dir_entry = readdir(dir)) != NULL) {
        if (dir_entry->d_name[0] == '.' && !config->print_all) {
            continue;
        }

        write(STDOUT_FILENO, dir_entry->d_name, lenstr(dir_entry->d_name));
        write(STDOUT_FILENO, "\n", 1);
    }

    closedir(dir);
}

int main(int argc, char **argv) {
    ls_config conf = {0};
    int first_arg_idx = INT_MAX;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            handle_flags(argv[i] + 1, &conf);
        } else if (i < first_arg_idx) {
            first_arg_idx = i;
        }
    }

    if (first_arg_idx == INT_MAX) {
        process_directory(".", &conf);
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            continue;
        }
        process_directory(argv[i], &conf);
    }

    return 0;
}