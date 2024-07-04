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
KERNEL_SRC = $(wildcard $(SRC_DIR)/kernel/*.c)
DRIVERS_SRC = $(wildcard $(SRC_DIR)/drivers/**/*.c)

# Object files
KERNEL_OBJ = $(KERNEL_SRC:$(SRC_DIR)/%.c=out/kernel/%.o)
DRIVERS_OBJ = $(DRIVERS_SRC:$(SRC_DIR)/%.c=out/drivers/%.o)

# Output directory
OUT_DIR = out

# Command line targets
.PHONY: all kernel clean

# Default target
all: kernel

# Rule to compile kernel
kernel: $(OUT_DIR)/kernel.bin

$(OUT_DIR)/kernel.bin: $(KERNEL_OBJ) $(DRIVERS_OBJ) | $(OUT_DIR)
    $(CC) $(LDFLAGS) $^ -o $@

# Rule to compile C source files into object files
out/kernel/%.o: $(SRC_DIR)/kernel/%.c | out/kernel
    $(CC) $(CFLAGS) -c $< -o $@

out/drivers/%.o: $(SRC_DIR)/drivers/%.c | out/drivers
    $(CC) $(CFLAGS) -c $< -o $@

# Create output directories if they don't exist
$(OUT_DIR) out/kernel out/drivers:
    mkdir -p $@

# Clean target
clean:
    rm -rf $(OUT_DIR)