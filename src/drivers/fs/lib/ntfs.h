#ifndef NTFS_H
#define NTFS_H

#include <stdint.h>
#include <stddef.h>

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

int ntfs_mount(const char *device);
int ntfs_unmount(void);
int ntfs_read_file(const char *path, void *buffer, size_t size);