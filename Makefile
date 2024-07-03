# ========================================================
#                      AurorOS Makefile
# ========================================================

# THIS MAKEFILE WORKS ON LINUX!
# Don't try to run this Makefile on Windows or other OS'es.

# Don't learn how to build the AurorOS using this file!
# Use Makefile to get the latest compilation mode!

# Prevent Windows users from running Makefile
ifeq ($(OS),Windows_NT)
$(error This Makefile is supported only on Linux, for deploying this on Windows please use WSL)
endif

# Define compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -nostdinc -ffreestanding -fno-builtin -Iinclude
LDFLAGS = -ffreestanding -nostdlib

# Define source files
KERNEL_SRC = kernel/main.c
DRIVERS_SRC = drivers/console/init.c drivers/vga/console.c drivers/fs/fat32/fat32.c

# Define object files
KERNEL_OBJ = $(patsubst %.c, $(OUT_DIR)/%.o, $(KERNEL_SRC))
DRIVERS_OBJ = $(patsubst %.c, $(OUT_DIR)/%.o, $(DRIVERS_SRC))

# Define output directory
OUT_DIR = out

.PHONY: all help kernel clean

# Define rule for normal `make`
all: help

# Define rule for `make help`
help:
	@echo "Available commands:"
	@echo "  make help    - Show this help message"
	@echo "  make kernel  - Build the kernel binary"
	@echo "  make clean   - Clean the output directory"

# Define rules for compiling kernel
kernel: $(OUT_DIR)/kernel.bin

$(OUT_DIR)/kernel.bin: $(KERNEL_OBJ) $(DRIVERS_OBJ)
	@echo "Linking kernel..."
	@mkdir -p $(OUT_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(OUT_DIR)/%.o: %.c
	@echo "Compiling $<..."
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Define rule for cleaning.
clean:
	@echo "Cleaning output directory..."
	@rm -rf $(OUT_DIR)
	@find . -name "*.o" -type f -delete