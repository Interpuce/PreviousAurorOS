#ifndef NTFS_H
#define NTFS_H

#include <stdint.h>
#include <stddef.h>

// NTFS boot sector structure
typedef struct {
    uint8_t  jump[3];
    char     oem_id[8];
    uint16_t bytes_per_sector;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t  zeroes1[3];
    uint16_t not_used1;
    uint8_t  media_descriptor;
    uint16_t zeroes2;
    uint16_t sectors_per_track;
    uint16_t number_of_heads;
    uint32_t hidden_sectors;
    uint32_t not_used2;
    uint32_t not_used3;
    uint64_t total_sectors;
    uint64_t mft_cluster;
    uint64_t mft_mirror_cluster;
    int8_t   clusters_per_file_record;
    uint8_t  not_used4[3];
    int8_t   clusters_per_index_record;
    uint8_t  not_used5[3];
    uint64_t volume_serial_number;
    uint32_t checksum;
    uint8_t  bootstrap[426];
    uint16_t end_of_sector_marker;
} __attribute__((packed)) ntfs_boot_sector_t;

// NTFS MFT entry structure
typedef struct {
    uint32_t signature;
    uint16_t offset_of_fixup_array;
    uint16_t number_of_entries_in_fixup_array;
    uint64_t log_file_sequence_number;
    uint16_t sequence_number;
    uint16_t link_count;
    uint16_t offset_to_first_attribute;
    uint16_t flags;
    uint32_t used_size;
    uint32_t allocated_size;
    uint64_t file_reference_to_base_record;
    uint16_t next_attribute_id;
} __attribute__((packed)) ntfs_mft_entry_t;

// NTFS attribute structure
typedef struct {
    uint32_t type;
    uint32_t length;
    uint8_t non_resident;
    uint8_t name_length;
    uint16_t name_offset;
    uint16_t flags;
    uint16_t attribute_id;
} __attribute__((packed)) ntfs_attribute_t;

// NTFS device structure
typedef struct {
    char *device_path;
    ntfs_boot_sector_t boot_sector;
    uint64_t mft_start;
} ntfs_device_t;

// Function declarations
int ntfs_mount(const char *device);
int ntfs_unmount(const char *device);
int ntfs_read_file(const char *device, const char *path, void *buffer, size_t size);
int ntfs_create_file(const char *device, const char *filename);
int ntfs_delete_file(const char *device, uint64_t entry_number);
int ntfs_read_directory(const char *device, const char *path, void *buffer, size_t size);

#endif