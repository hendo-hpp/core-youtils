

At first I thought I would need a distinct function for when the user
specifies to read standard input (i.e. no arguments). Since
stdin has a file descriptor (specifically 0) it could be handled
as if we were opening/processing any other file