# ======================================================================
#                           AurorOS MakeFile
# ======================================================================

# Set target and src
TARGET = out/os
SRC_DIR = src/boot
SRC_C = $(SRC_DIR)/bootloader.c
SRC_ASM = $(SRC_DIR)/bootstart.asm

# Set other variables
ARCH = $(shell uname -m | sed 's/x86_64/x86_64/')
EFI_INC = /usr/include/efi
EFI_LIB = /usr/lib
EFI_CC = gcc
EFI_LD = ld
NASM = nasm
CFLAGS = -I$(EFI_INC) -I$(EFI_INC)/$(ARCH) -fno-stack-protector -fpic -fshort-wchar -mno-red-zone -fno-stack-check -fno-lto -fno-common
LDFLAGS = -nostdlib -znocombreloc -T $(EFI_INC)/elf_$(ARCH)_efi.lds
ASMFLAGS = -f elf64

# ===== START OF FILE =====

all: $(TARGET).efi

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(TARGET).efi: $(TARGET).so | $(TARGET_DIR)
	objcopy -j .text -j .sdata -j .data -j .dynamic -j .dynsym \
	    -j .rel -j .rela -j .reloc --target=efi-app-$(ARCH) $^ $@

$(TARGET).so: $(SRC_C) $(SRC_ASM:.asm=.o)
	$(EFI_CC) $(CFLAGS) -o $@ -shared $^ $(LDFLAGS)

%.o: $(SRC_DIR)/%.asm
	$(NASM) $(ASMFLAGS) -o $@ $<

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET_DIR)/*.so $(TARGET_DIR)/*.efi