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

# Directories
SRC_DIR = src
OUT_DIR = out
OBJ_DIR = $(OUT_DIR)/obj

# Source files
KERNEL_SRC = $(wildcard $(SRC_DIR)/kernel/*.c)
DRIVERS_SRC = $(wildcard $(SRC_DIR)/drivers/**/*.c)

# Object files
KERNEL_OBJ = $(patsubst $(SRC_DIR)/kernel/%.c, $(OBJ_DIR)/kernel/%.o, $(KERNEL_SRC))
DRIVERS_OBJ = $(patsubst $(SRC_DIR)/drivers/%.c, $(OBJ_DIR)/drivers/%.o, $(DRIVERS_SRC))

# All object files
OBJ = $(KERNEL_OBJ) $(DRIVERS_OBJ)

# Command line targets
.PHONY: all help kernel clean

# Default target
all: kernel

# Help target
help:
	@echo "Available commands:"
	@echo "  make help    - Show this help message"
	@echo "  make kernel  - Build the kernel binary"
	@echo "  make clean   - Clean the output directory"

# Rule to compile kernel
kernel: $(OUT_DIR)/kernel.bin

$(OUT_DIR)/kernel.bin: $(OBJ) | $(OUT_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Rule to compile C source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create output directory if it doesn't exist
$(OUT_DIR):
	@mkdir -p $(OUT_DIR)

# Clean target
clean:
	rm -rf $(OUT_DIR)