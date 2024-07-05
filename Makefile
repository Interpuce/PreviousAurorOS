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

# Compiler and compilator flags
CC = gcc
CFLAGS = -Wall -Wextra -O2 -nostdinc -ffreestanding -fno-builtin -Iinclude -m32
LDFLAGS = -ffreestanding -nostdlib

# Source files
SRC_DIR = src

# C files
C_SRCS = $(shell find $(SRC_DIR) -name *.c)
C_OBJS = $(patsubst src/%.c,out/obj/%.c.o,$(C_SRCS))
ASM_SRCS = $(shell find $(SRC_DIR) -name *.asm)
ASM_OBJS = $(patsubst src/%.asm,out/obj/%.asm.o,$(ASM_SRCS))

# Rules
.PHONY: all
all: kernel

# Rules to compilation
.PHONY: all kernel dirs 
kernel: dirs $(C_OBJS) $(ASM_OBJS) kernelImg

kernelImg:
	$(CC) $(LDFLAGS) $(C_OBJS) $(ASM_OBJS) -o kernelImg
	@echo "kernel: ./kernelImg is ready!"

out/obj/%.c.o: $(SRC_DIR)/%.c
	@mkdir -p $(shell dirname '$@')
	$(CC) $(CFLAGS) -c $< -o $@

out/obj/%.asm.o: $(SRC_DIR)/%.asm
	@nasm -f elf32 -c $< -o $@

dirs:
	@mkdir -p out out/obj

clean:
	@rm -rf $(OUT_DIR)