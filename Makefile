# ========================================================
#                      AurorOS Makefile
# ========================================================

.PHONY: all help kernel build clean

all:
	@echo ======================================================
	@echo                    AurorOS Makefile
	@echo ======================================================
	@echo Write "make help" to get help.

help:
	@echo Available commands:
	@echo   make help    - Show this help message
	@echo   make kernel  - Build the kernel binary
	@echo   make build   - Build the ISO image
	@echo   make clean   - Clean the output directory

kernel: out/kernel.bin

out/kernel.bin: src/kernel/main.c
	@echo Building kernel...
	@md out
	gcc -o out/kernel.bin src/kernel/main.c

clean:
	@echo Cleaning output directory...
	@rd /s /q out