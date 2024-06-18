# The AurorOS kernel

This is simplified document about AurorOS kernel.

**Files:**

- [main.c](#mainc)
- [functions.h](#functionsh)

## main.c

This file is a main kernel file contains boot procedure and GUI initialization. It is used to boot the OS and make main system loop.

## functions.h

The kernel core contains functions like `print_version_line()`. Its API calls are used by different applications and the [main.c](#mainc) file.