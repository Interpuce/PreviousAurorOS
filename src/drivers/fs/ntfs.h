// ======================================================================
//                            AurorOS Driver
// ======================================================================

// => The NTFS filesystem driver.
//       This file is basically a inplementation of NTFS filesystem
//       and provides API calls to read the files, etc.

#include "lib/ntfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ntfs_read_sector(const char *device, uint64_t sector, uint8_t *buffer, size_t size);

typedef struct {
    ntfs_boot_sector_t boot_sector;
} ntfs_fs_t;

static ntfs_fs_t *ntfs_fs = NULL;

int ntfs_mount(const char *device) {
    ntfs_fs = (ntfs_fs_t *)malloc(sizeof(ntfs_fs_t));
    if (!ntfs_fs) {
        return -1;
    }

    if (ntfs_read_sector(device, 0, (uint8_t *)&ntfs_fs->boot_sector, sizeof(ntfs_boot_sector_t)) != 0) {
        free(ntfs_fs);
        ntfs_fs = NULL;
        return -1;
    }

    if (ntfs_fs->boot_sector.end_of_sector_marker != 0xAA55) {
        free(ntfs_fs);
        ntfs_fs = NULL;
        return -1;
    }

    return 0;
}

int ntfs_unmount(void) {
    if (ntfs_fs) {
        free(ntfs_fs);
        ntfs_fs = NULL;
        return 0;
    }
    return -1;
}

int ntfs_read_file(const char *path, void *buffer, size_t size) {
    if (!ntfs_fs) {
        return -1;
    }

    return 0;
}

int ntfs_read_sector(const char *device, uint64_t sector, uint8_t *buffer, size_t size) {
    FILE *f = fopen(device, "rb");
    if (!f) {
        return -1;
    }

    if (fseek(f, sector * 512, SEEK_SET) != 0) {
        fclose(f);
        return -1;
    }

    if (fread(buffer, 1, size, f) != size) {
        fclose(f);
        return -1;
    }

    fclose(f);
    return 0;
}