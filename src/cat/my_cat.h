#ifndef YOUTIL_MY_CAT_H__
#define YOUTIL_MY_CAT_H__

#include <stdbool.h>

typedef struct {
    bool show_all;
    bool number_non_blank;
    bool show_ends_non_printing;
    bool show_ends;
    bool number_lines;
    bool squeeze_blank;
    bool show_tabs_non_printing;
    bool show_tabs;
    bool show_non_printing;
} MyCatConfig;

void handle_flags(const char *flag, MyCatConfig *config);
void process_fd(int fd, const MyCatConfig *config);

#endif // YOUTIL_MY_CAT_H__