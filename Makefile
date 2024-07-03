# ========================================================
#                      AurorOS Makefile
# ========================================================

# THIS MAKEFILE WORKS ON LINUX!
# Don't try to run this Makefile on Windows or other OS'es.

# Don't learn how to build the AurorOS using this file!
# Use Makefile to get the latest compilation mode!

# Prevent Windows users from running Makefile
ifeq ($(OS),Windows_NT)
$(error This Makefile is supported only on Linux; please use WSL for Windows)
endif

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -nostdinc -ffreestanding -fno-builtin -Iinclude
LDFLAGS = -ffreestanding -nostdlib

# Source directory
SRC_DIR = src

# Source files
KERNEL_SRC = ${SRC_DIR}/kernel/main.c
DRIVERS_SRC = ${SRC_DIR}/drivers/console/init.c ${SRC_DIR}/drivers/vga/console.c ${SRC_DIR}/drivers/fs/fat32/fat32.c

# Object files
KERNEL_OBJ = $(KERNEL_SRC:%.c=$(OUT_DIR)/%.o)
DRIVERS_OBJ = $(DRIVERS_SRC:%.c=$(OUT_DIR)/%.o)

# Output directory
OUT_DIR = out

# Command line targets
.PHONY: all help kernel clean

# Default target
all: help

# Help target
help:
	@echo "Available commands:"
	@echo "  make help    - Show this help message"
	@echo "  make kernel  - Build the kernel binary"
	@echo "  make clean   - Clean the output directory"

# Rule to compile kernel
kernel: $(OUT_DIR)/kernel.bin

# Rule to compile kernel
$(OUT_DIR)/kernel.bin: $(KERNEL_OBJ) $(DRIVERS_OBJ)
	$(CC) $(LDFLAGS) $(KERNEL_OBJ) $(DRIVERS_OBJ) -o $@

# Rule to compile C source files into object files
$(OUT_DIR)/%.o: %.c | $(OUT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create output directory if it doesn't exist
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Clean target
clean:
	rm -rf $(OUT_DIR)