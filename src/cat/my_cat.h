#ifndef MY_CAT_H__
#define MY_CAT_H__

#include <stdbool.h>

typedef struct {
    bool show_all;               // -A
    bool number_non_blank;       // -b
    bool show_ends_non_printing; // -e
    bool show_ends;              // -E
    bool number_lines;           // -n
    bool squeeze_blank;          // -s
    bool show_tabs_non_printing; // -t
    bool show_tabs;              // -T
    bool show_non_printing;      // -v
} cat_config;

void handle_flags(const char *flag, cat_config *config);
void process_fd(int fd, const cat_config *config);

#endif // MY_CAT_H__