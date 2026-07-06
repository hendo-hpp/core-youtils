#ifndef UTIL_H__
#define UTIL_H__

#include <stdbool.h>
#include <unistd.h>

size_t lenstr(const char *str);

bool is_whitespace(char c);

void log_dir_open_error(const char *dir_name);
void log_file_open_error(const char *file_name);
void log_flag_error(const char flag);

void writef_int(int val);

#endif // UTIL_H__