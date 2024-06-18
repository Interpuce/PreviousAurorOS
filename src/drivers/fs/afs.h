// ======================================================================
//                            AurorOS Driver
// ======================================================================

// => The AurorOS filesystem driver.
//      This file is basically an implementation of the AurorOS filesystem
//      and provides API calls to read files, etc.

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_AFS_DEVICES 1024

struct afs_inode {
    uint32_t inode_number;
    uint32_t size;
    uint64_t created_timestamp;
    uint64_t modified_timestamp;
};

struct afs_file {
    struct afs_inode inode;
    uint8_t *data;
    char *filename;
    struct afs_file *next;
};

struct afs_directory {
    struct afs_inode inode;
    struct afs_directory *children;
    size_t num_children;
    char *dirname;
    struct afs_directory *next;
};

struct afs_disk {
    struct afs_file *file_list;
    struct afs_directory *directory_list;
    uint32_t next_inode_number;
    char *disk_name;
};

static struct afs_disk disks[MAX_AFS_DEVICES];
static int num_disks = 0;

void afs_init() {
    // Initialization code here
    for (int i = 0; i < MAX_AFS_DEVICES; i++) {
        disks[i].file_list = NULL;
        disks[i].directory_list = NULL;
        disks[i].next_inode_number = 1;
        disks[i].disk_name = NULL;
    }
    num_disks = 0;
}

int afs_add_disk(const char *disk_name) {
    if (num_disks >= MAX_AFS_DEVICES) return -1;
    disks[num_disks].disk_name = strdup(disk_name);
    if (!disks[num_disks].disk_name) return -1;
    num_disks++;
    return 0;
}

struct afs_disk *afs_find_disk(const char *disk_name) {
    for (int i = 0; i < num_disks; i++) {
        if (strcmp(disks[i].disk_name, disk_name) == 0) {
            return &disks[i];
        }
    }
    return NULL;
}

int afs_create_file(const char *disk_name, const char *filename) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return -1;

    struct afs_file *current = disk->file_list;
    while (current) {
        if (strcmp(current->filename, filename) == 0) {
            return -1; // File already exists
        }
        current = current->next;
    }

    struct afs_file *new_file = (struct afs_file *)malloc(sizeof(struct afs_file));
    if (!new_file) return -1;

    new_file->filename = strdup(filename);
    if (!new_file->filename) {
        free(new_file);
        return -1;
    }

    new_file->inode.inode_number = disk->next_inode_number++;
    new_file->inode.size = 0;
    new_file->inode.created_timestamp = time(NULL);
    new_file->inode.modified_timestamp = new_file->inode.created_timestamp;
    new_file->data = NULL;
    new_file->next = disk->file_list;
    disk->file_list = new_file;

    return 0;
}

int afs_delete_file(const char *disk_name, const char *filename) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return -1;

    struct afs_file **current = &disk->file_list;
    while (*current) {
        if (strcmp((*current)->filename, filename) == 0) {
            struct afs_file *to_delete = *current;
            *current = (*current)->next;
            free(to_delete->filename);
            free(to_delete->data);
            free(to_delete);
            return 0;
        }
        current = &(*current)->next;
    }
    return -1; // File not found
}

struct afs_file *afs_open_file(const char *disk_name, const char *filename) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return NULL;

    struct afs_file *current = disk->file_list;
    while (current) {
        if (strcmp(current->filename, filename) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL; // File not found
}

int afs_read_file(struct afs_file *file, void *buffer, size_t count) {
    if (!file || !buffer) return -1;
    if (count > file->inode.size) count = file->inode.size;
    memcpy(buffer, file->data, count);
    return (int)count;
}

int afs_write_file(struct afs_file *file, const void *buffer, size_t count) {
    if (!file || !buffer) return -1;
    uint8_t *new_data = (uint8_t *)realloc(file->data, count);
    if (!new_data) return -1;
    file->data = new_data;
    memcpy(file->data, buffer, count);
    file->inode.size = count;
    file->inode.modified_timestamp = time(NULL);
    return (int)count;
}

void afs_close_file(struct afs_file *file) {
    // For this filesystem, actually nothing needs to be done
}

int afs_create_directory(const char *disk_name, const char *dirname) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return -1;

    struct afs_directory *current = disk->directory_list;
    while (current) {
        if (strcmp(current->dirname, dirname) == 0) {
            return -1; // Directory already exists
        }
        current = current->next;
    }

    struct afs_directory *new_directory = (struct afs_directory *)malloc(sizeof(struct afs_directory));
    if (!new_directory) return -1;

    new_directory->dirname = strdup(dirname);
    if (!new_directory->dirname) {
        free(new_directory);
        return -1;
    }

    new_directory->inode.inode_number = disk->next_inode_number++;
    new_directory->inode.size = 0;
    new_directory->inode.created_timestamp = time(NULL);
    new_directory->inode.modified_timestamp = new_directory->inode.created_timestamp;
    new_directory->children = NULL;
    new_directory->num_children = 0;
    new_directory->next = disk->directory_list;
    disk->directory_list = new_directory;

    return 0;
}

int afs_delete_directory(const char *disk_name, const char *dirname) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return -1;

    struct afs_directory **current = &disk->directory_list;
    while (*current) {
        if (strcmp((*current)->dirname, dirname) == 0) {
            struct afs_directory *to_delete = *current;
            *current = (*current)->next;
            free(to_delete->dirname);
            free(to_delete->children);
            free(to_delete);
            return 0;
        }
        current = &(*current)->next;
    }
    return -1; // Directory not found
}

struct afs_inode *afs_list_directory(const char *disk_name, const char *dirname, size_t *num_entries) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) {
        *num_entries = 0;
        return NULL;
    }

    struct afs_directory *current = disk->directory_list;
    while (current) {
        if (strcmp(current->dirname, dirname) == 0) {
            *num_entries = current->num_children;
            return current->children;
        }
        current = current->next;
    }
    *num_entries = 0;
    return NULL; // Directory not found
}

int afs_get_metadata(const char *disk_name, const char *name, struct afs_inode *inode) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return -1;

    struct afs_file *file = disk->file_list;
    while (file) {
        if (strcmp(file->filename, name) == 0) {
            *inode = file->inode;
            return 0;
        }
        file = file->next;
    }

    struct afs_directory *directory = disk->directory_list;
    while (directory) {
        if (strcmp(directory->dirname, name) == 0) {
            *inode = directory->inode;
            return 0;
        }
        directory = directory->next;
    }

    return -1; // File or directory not found
}

int afs_update_metadata(const char *disk_name, const char *name, const struct afs_inode *inode) {
    struct afs_disk *disk = afs_find_disk(disk_name);
    if (!disk) return -1;

    struct afs_file *file = disk->file_list;
    while (file) {
        if (strcmp(file->filename, name) == 0) {
            file->inode = *inode;
            return 0;
        }
        file = file->next;
    }

    struct afs_directory *directory = disk->directory_list;
    while (directory) {
        if (strcmp(directory->dirname, name) == 0) {
            directory->inode = *inode;
            return 0;
        }
        directory = directory->next;
    }

    return -1; // File or directory not found
}