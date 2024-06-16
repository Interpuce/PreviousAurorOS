// ======================================================================
//                            AurorOS Driver
// ======================================================================
//
// => The NTFS filesystem driver.
//       This file is basically an implementation of NTFS filesystem
//       and provides API calls to read the files, etc.

#include "lib/ntfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of NTFS devices
#define MAX_NTFS_DEVICES 16

static ntfs_device_t ntfs_devices[MAX_NTFS_DEVICES];
static int ntfs_device_count = 0;

// Function to find a device by its path
static ntfs_device_t* find_device(const char *device) {
    for (int i = 0; i < ntfs_device_count; i++) {
        if (strcmp(ntfs_devices[i].device_path, device) == 0) {
            return &ntfs_devices[i];
        }
    }
    return NULL;
}

// Function to mount the NTFS filesystem
int ntfs_mount(const char *device) {
    if (ntfs_device_count >= MAX_NTFS_DEVICES) {
        return -1; // Maximum number of devices reached
    }

    ntfs_device_t *new_device = &ntfs_devices[ntfs_device_count];
    new_device->device_path = strdup(device);
    if (!new_device->device_path) {
        return -1; // Memory allocation failure
    }

    // Read the boot sector from the device
    if (ntfs_read_sector(device, 0, (uint8_t *)&new_device->boot_sector, sizeof(ntfs_boot_sector_t)) != 0) {
        free(new_device->device_path);
        return -1; // Error reading boot sector
    }

    // Check the validity of the NTFS boot sector
    if (new_device->boot_sector.end_of_sector_marker != 0xAA55) {
        free(new_device->device_path);
        return -1; // Invalid boot sector
    }

    new_device->mft_start = new_device->boot_sector.mft_cluster * new_device->boot_sector.sectors_per_cluster;
    ntfs_device_count++;
    return 0; // Mounting successful
}

// Function to unmount the NTFS filesystem
int ntfs_unmount(const char *device) {
    ntfs_device_t *device_to_remove = find_device(device);
    if (!device_to_remove) {
        return -1; // Device not found
    }

    free(device_to_remove->device_path);
    *device_to_remove = ntfs_devices[--ntfs_device_count];
    return 0; // Unmounting successful
}

// Function to read an MFT entry
int ntfs_read_mft_entry(const char *device, uint64_t entry_number, ntfs_mft_entry_t *mft_entry) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // Device not mounted
    }

    uint64_t sector = ntfs_fs->mft_start + (entry_number * sizeof(ntfs_mft_entry_t)) / 512;

    if (ntfs_read_sector(device, sector, (uint8_t *)mft_entry, sizeof(ntfs_mft_entry_t)) != 0) {
        return -1; // Error reading MFT entry
    }

    if (mft_entry->signature != 0x454C4946) { // Check for "FILE" signature
        return -1; // Invalid MFT entry
    }

    return 0; // MFT entry read successfully
}

// Function to find an attribute within an MFT entry
int ntfs_find_attribute(ntfs_mft_entry_t *mft_entry, uint32_t type, ntfs_attribute_t **attr) {
    uint8_t *ptr = (uint8_t *)mft_entry + mft_entry->offset_to_first_attribute;
    while (ptr < (uint8_t *)mft_entry + mft_entry->used_size) {
        ntfs_attribute_t *attribute = (ntfs_attribute_t *)ptr;
        if (attribute->type == type) {
            *attr = attribute;
            return 0;
        }
        ptr += attribute->length;
    }
    return -1; // Attribute not found
}

// Function to read a file from the NTFS filesystem
int ntfs_read_file(const char *device, const char *path, void *buffer, size_t size) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    // Locate the file in the MFT (simplified for root directory entry 0)
    ntfs_mft_entry_t mft_entry;
    if (ntfs_read_mft_entry(device, 0, &mft_entry) != 0) {
        return -1; // Error reading MFT entry
    }

    // Find the $DATA attribute
    ntfs_attribute_t *data_attr;
    if (ntfs_find_attribute(&mft_entry, 0x80, &data_attr) != 0) {
        return -1; // Data attribute not found
    }

    uint8_t *data = (uint8_t *)data_attr + data_attr->name_offset;
    if (data_attr->non_resident) {
        return -1; // Non-resident attributes not handled in this example
    }

    if (data_attr->length > size) {
        return -1; // Buffer size is too small
    }

    memcpy(buffer, data, data_attr->length);
    return data_attr->length; // Return the number of bytes read
}

// Function to write a file to the NTFS filesystem
int ntfs_write_file(const char *device, const char *path, const void *buffer, size_t size) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    // Locate the file in the MFT (simplified for root directory entry 0)
    ntfs_mft_entry_t mft_entry;
    if (ntfs_read_mft_entry(device, 0, &mft_entry) != 0) {
        return -1; // Error reading MFT entry
    }

    // Find the $DATA attribute
    ntfs_attribute_t *data_attr;
    if (ntfs_find_attribute(&mft_entry, 0x80, &data_attr) != 0) {
        return -1; // Data attribute not found
    }

    uint8_t *data = (uint8_t *)data_attr + data_attr->name_offset;
    if (data_attr->non_resident) {
        return -1; // Non-resident attributes not handled in this example
    }

    if (size > data_attr->length) {
        return -1; // Buffer size is too large
    }

    memcpy(data, buffer, size);

    uint64_t sector = ntfs_fs->mft_start + (0 * sizeof(ntfs_mft_entry_t)) / 512;
    if (ntfs_write_sector(device, sector, (uint8_t *)&mft_entry, sizeof(ntfs_mft_entry_t)) != 0) {
        return -1; // Error writing MFT entry
    }

    return 0; // File written successfully
}

// Function to locate the first free MFT entry
int find_free_mft_entry(const char *device, uint64_t *entry_number) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    ntfs_mft_entry_t mft_entry;
    uint64_t i = 0;

    while (ntfs_read_mft_entry(device, i, &mft_entry) == 0) {
        if (mft_entry.signature != 0x454C4946) { // Check for "FILE" signature
            *entry_number = i;
            return 0; // Free entry found
        }
        i++;
    }
    return -1; // No free entry found
}

// Function to create a new file
int ntfs_create_file(const char *device, const char *filename) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    uint64_t free_entry;
    if (find_free_mft_entry(device, &free_entry) != 0) {
        return -1; // No free MFT entry found
    }

    ntfs_mft_entry_t mft_entry = {0};
    mft_entry.signature = 0x454C4946; // "FILE" signature
    mft_entry.offset_to_first_attribute = sizeof(ntfs_mft_entry_t);
    mft_entry.used_size = sizeof(ntfs_mft_entry_t) + sizeof(ntfs_attribute_t);
    mft_entry.allocated_size = sizeof(ntfs_mft_entry_t) + sizeof(ntfs_attribute_t);

    ntfs_attribute_t data_attr = {0};
    data_attr.type = 0x80; // $DATA attribute
    data_attr.length = sizeof(ntfs_attribute_t);
    data_attr.non_resident = 0;

    uint8_t buffer[512] = {0};
    memcpy(buffer, &mft_entry, sizeof(ntfs_mft_entry_t));
    memcpy(buffer + sizeof(ntfs_mft_entry_t), &data_attr, sizeof(ntfs_attribute_t));

    uint64_t sector = ntfs_fs->mft_start + (free_entry * sizeof(ntfs_mft_entry_t)) / 512;

    if (ntfs_write_sector(device, sector, buffer, sizeof(buffer)) != 0) {
        return -1; // Error writing MFT entry
    }

    return 0; // File created successfully
}

// Function to delete a file
int ntfs_delete_file(const char *device, uint64_t entry_number) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    ntfs_mft_entry_t mft_entry = {0};

    uint64_t sector = ntfs_fs->mft_start + (entry_number * sizeof(ntfs_mft_entry_t)) / 512;

    if (ntfs_read_sector(device, sector, (uint8_t *)&mft_entry, sizeof(ntfs_mft_entry_t)) != 0) {
        return -1; // Error reading MFT entry
    }

    mft_entry.signature = 0x0; // Mark as free

    if (ntfs_write_sector(device, sector, (uint8_t *)&mft_entry, sizeof(ntfs_mft_entry_t)) != 0) {
        return -1; // Error writing MFT entry
    }

    return 0; // File deleted successfully
}

// Function to read a directory
int ntfs_read_directory(const char *device, const char *path, void *buffer, size_t size) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    // Locate the directory in the MFT (simplified for root directory entry 0)
    ntfs_mft_entry_t mft_entry;
    if (ntfs_read_mft_entry(device, 0, &mft_entry) != 0) {
        return -1; // Error reading MFT entry
    }

    // Find the $INDEX_ROOT attribute
    ntfs_attribute_t *index_root_attr;
    if (ntfs_find_attribute(&mft_entry, 0x90, &index_root_attr) != 0) {
        return -1; // Index root attribute not found
    }

    uint8_t *data = (uint8_t *)index_root_attr + index_root_attr->name_offset;
    if (index_root_attr->non_resident) {
        return -1; // Non-resident attributes not handled in this example
    }

    if (index_root_attr->length > size) {
        return -1; // Buffer size is too small
    }

    memcpy(buffer, data, index_root_attr->length);
    return index_root_attr->length; // Return the number of bytes read
}

// Function to read the metadata of a file
int ntfs_read_metadata(const char *device, const char *path, ntfs_mft_entry_t *metadata) {
    ntfs_device_t *ntfs_fs = find_device(device);
    if (!ntfs_fs) {
        return -1; // NTFS is not mounted
    }

    // Locate the file in the MFT (simplified for root directory entry 0)
    if (ntfs_read_mft_entry(device, 0, metadata) != 0) {
        return -1; // Error reading MFT entry
    }

    return 0; // Metadata read successfully
}

// Function to read a sector from the disk
int ntfs_read_sector(const char *device, uint64_t sector, uint8_t *buffer, size_t size) {
    FILE *f = fopen(device, "rb");
    if (!f) {
        return -1; // Error opening device
    }

    if (fseek(f, sector * 512, SEEK_SET) != 0) {
        fclose(f);
        return -1; // Error seeking to sector
    }

    if (fread(buffer, 1, size, f) != size) {
        fclose(f);
        return -1; // Error reading sector
    }

    fclose(f);
    return 0; // Sector read successfully
}

// Function to write a sector to the disk
int ntfs_write_sector(const char *device, uint64_t sector, const uint8_t *buffer, size_t size) {
    FILE *f = fopen(device, "rb+");
    if (!f) {
        return -1; // Error opening device
    }

    if (fseek(f, sector * 512, SEEK_SET) != 0) {
        fclose(f);
        return -1; // Error seeking to sector
    }

    if (fwrite(buffer, 1, size, f) != size) {
        fclose(f);
        return -1; // Error writing sector
    }

    fclose(f);
    return 0; // Sector written successfully
}