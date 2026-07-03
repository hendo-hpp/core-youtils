

At first I thought I would need a distinct function for when the user
specifies to read standard input (i.e. no arguments). Since
stdin has a file descriptor (specifically 0) it could be handled
as if we were opening/processing any other file

using pointer arithmetic such as
```c
while (*str) { buff[idx++] = *str++ }
```
was a clean way to iterate over the string without having
to double index the string for the end check `str[i] != '\0'` and setting
the value

tradeoff of using #define buffer_size 4096 vs sysconf()