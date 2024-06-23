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
	@mkdir -p out
	gcc -o out/kernel.bin src/kernel/main.c

build: check-kernel
	@echo Creating ISO structure...
	@mkdir -p out/iso/AurorOS
	@mkdir -p out/iso/Apps
	@cp out/kernel.bin out/iso/AurorOS/kernel.aur
	@echo Generating ISO...
	mkisofs -o out/AurorOS.iso -V "AurorOS" -R -J out/iso

check-kernel:
	@if [ ! -f out/kernel.bin ]; then \
		echo "Kernel binary not found. Please run 'make kernel' first."; \
		exit 1; \
	fi

clean:
	@echo Cleaning output directory...
	@rm -rf out