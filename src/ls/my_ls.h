#ifndef MY_LS_H__
#define MY_LS_H__

#include <stdbool.h>

typedef struct {
    bool print_all;        // -a
    bool print_index;      // -i
    bool format_long;      // -l
    bool sort_change_time; // -c
    bool sort_time;        // -t
    bool list_columns;     // -C
    bool format_commas;    // -m
    bool print_literal;    // -n
    bool print_recursive;  // -R
    bool print_size;       // -s
} ls_config;

void handle_flags(const char *flags, ls_config *config);
void process_directory(const char *path, ls_config *config);

#endif // MY_LS_H__