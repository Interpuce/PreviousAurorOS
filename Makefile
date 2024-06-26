# ========================================================
#                      AurorOS Makefile
# ========================================================

# Define flags for GCC
CFLAGS = -Wall -Wextra -O2 -nostdinc -ffreestanding -fno-builtin -Iinclude

.PHONY: all help kernel build clean

# Define rule for normal `make`
all:
	@echo "======================================================"
	@echo "                   AurorOS Makefile"
	@echo "======================================================"
	@echo 'Write "make help" to get help.'

# Define rule for `make help`
help:
	@echo "Available commands:"
	@echo "  make help    - Show this help message"
	@echo "  make kernel  - Build the kernel binary"
	@echo "  make clean   - Clean the output directory"

# Define rules for compiling kernel
kernel:
	@echo Building kernel...
	@mkdir -p out
	gcc ${CFLAGS} -o out/kernel.bin src/kernel/main.c src/drivers/console.c

# Define rule for cleaning.
clean:
	@echo Cleaning output directory...
	@rm -rf out