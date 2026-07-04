#ifndef MY_WC_H__
#define MY_WC_H__

#include <stdbool.h>

typedef struct {
    bool print_byte_count; // -c
    bool print_char_count; // -m
    bool print_newl_count; // -l
    bool print_line_len;   // -L
    bool print_word_count; // -w
} wc_config;

typedef struct {
    int total_byte_count;
    int total_char_count;
    int total_newl_count;
    int total_max_line_len;
    int total_word_count;
} wc_totals;

void handle_flags(const char *flags, wc_config *config);
void process_fd(int fd, const wc_config *config);

#endif // MY_WC_H__