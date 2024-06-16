# ======================================================================
#                           AurorOS MakeFile
# ======================================================================

# ! Comments in this file are only for developers.
# ! Don't learn how to build the kernel using this file!

# Set out and source folder
TARGET_DIR = out/
SRC_DIR = src/

# Set bootloader and kernel source folder
SRC_BOOTLOADER = ${OUT_DIR}/boot
SRC_KERNEL = ${OUT_DIR}/kernel

# Set target dir
TARGET = ${TARGET_DIR}