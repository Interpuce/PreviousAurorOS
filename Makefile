# ======================================================================
#                           AurorOS MakeFile
# ======================================================================

# ! Comments in this file are only for developers.
# ! Don't learn how to build the kernel using this file!

# Set out and source folder
TARGET_DIR = out
SRC_DIR = src

# Set bootloader and kernel source folder
SRC_BOOTLOADER = $(SRC_DIR)/boot
SRC_KERNEL = $(SRC_DIR)/kernel

# Set target dir
TARGET = $(TARGET_DIR)/os

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -nostdlib -ffreestanding -O2

# Assembly source file and object file
KERNEL_SRC = $(SRC_KERNEL)/main.c
KERNEL_OBJ = $(TARGET)/kernel.o

# The final kernel binary
KERNEL_BIN = $(TARGET)/kernel.bin

# OS-specific commands
ifeq ($(OS),Windows_NT)
    MKDIR_P = if not exist $(subst /,\,$(TARGET)) mkdir $(subst /,\,$(TARGET))
    RM = rmdir /S /Q $(subst /,\,$(TARGET_DIR))
else
    MKDIR_P = mkdir -p $(TARGET)
    RM = rm -rf $(TARGET_DIR)
endif

# Default rule to display options
all:
	@echo Usage:
	@echo   make build   - Build the OS
	@echo   make clean   - Clean the build output

# Rule to build the kernel
build: $(KERNEL_BIN)

$(TARGET):
	$(MKDIR_P)

$(KERNEL_OBJ): $(KERNEL_SRC) | $(TARGET)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BIN): $(KERNEL_OBJ)
	$(CC) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib $^

# Rule to clean the build output
clean:
	$(RM)

.PHONY: all build clean