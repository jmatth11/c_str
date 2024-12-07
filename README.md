# C Str

This is just a small library mainly for me to use with my C projects to handle strings in a more uniform way.

nothing special.


The `main.c` file contains unit tests for the functionality. When running this file, no response means everything passed, otherwise an assert will fail.

The `Makefile` supports 4 functions:
- No arguments: builds everything and generates a `c_str` executable (just for unit testing)
- `debug`: builds everything with debug flags and generates a `c_str` executable (just for unit testing)
- `archive`: builds everything for library usage. (builds .a and .so files)
- `clean`: cleans executable, object files, and library files.

