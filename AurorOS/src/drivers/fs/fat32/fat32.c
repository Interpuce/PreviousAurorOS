// ----------------------------- AurorOS -----------------------------
//                       Created by Interpuce Team
// -------------------------------------------------------------------

// This is a FAT32 filesystem driver.

// NOTE: This driver needs more things, but for making simple OS
//       and for now let implement the most important things.

// Include function prototypes
#include <kerdef.h>

// Include FAT32 structures
#include "fat32.h"

// Include the C basics (rewrite in includes/)
#include <stdint.h>
#include <string.h>

// Prototypes of internal functions

static uint32_t fat32_get_fat_entry(uint32_t cluster);
static void fat32_read_sector(uint32_t sector, void* buffer);
static void fat32_write_sector(uint32_t sector, const void* buffer);

// Global boot sector variable
struct FAT32BootSector fat32_boot_sector;

// Function to read the boot sector
void fat32_read_boot_sector(uint32_t start_sector) {
    fat32_read_sector(start_sector, &fat32_boot_sector);
}

// Function to read a sector from the disk
static void fat32_read_sector(uint32_t sector, void* buffer) {
}

// Function to write a sector to the disk
static void fat32_write_sector(uint32_t sector, const void* buffer) {
}

// Function to get the FAT entry for a given cluster
static uint32_t fat32_get_fat_entry(uint32_t cluster) {
    uint32_t fat_offset = cluster * 4;
    uint32_t fat_sector = fat32_boot_sector.reservedSectors + (fat_offset / fat32_boot_sector.bytesPerSector);
    uint32_t entry_offset = fat_offset % fat32_boot_sector.bytesPerSector;

    uint8_t sector_buffer[fat32_boot_sector.bytesPerSector];
    fat32_read_sector(fat_sector, sector_buffer);

    return *((uint32_t*)&sector_buffer[entry_offset]) & 0x0FFFFFFF;
}

// Function to read a file or directory entry from a cluster
void fat32_read_directory_entry(uint32_t cluster, struct DirectoryEntry* entry) {
    uint32_t sector = fat32_boot_sector.reservedSectors + (cluster - 2) * fat32_boot_sector.sectorsPerCluster;
    fat32_read_sector(sector, entry);
}

// Function to initialize the FAT32 filesystem
void fat32_init(uint32_t start_sector) {
    fat32_read_boot_sector(start_sector);
}