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

// Functions should start with afs_

static struct afs_file *file_list = NULL;
static struct afs_directory *directory_list = NULL;
static uint32_t next_inode_number = 1;

void afs_init() {
    // Initialization code here
    file_list = NULL;
    directory_list = NULL;
    next_inode_number = 1;
}

int afs_create_file(const char *filename) {
    // Check if the file already exists
    struct afs_file *current = file_list;
    while (current) {
        if (strcmp(current->filename, filename) == 0) {
            return -1; // File already exists
        }
        current = current->next;
    }

    // Create a new file
    struct afs_file *new_file = (struct afs_file *)malloc(sizeof(struct afs_file));
    if (!new_file) return -1;

    new_file->filename = strdup(filename);
    if (!new_file->filename) {
        free(new_file);
        return -1;
    }

    new_file->inode.inode_number = next_inode_number++;
    new_file->inode.size = 0;
    new_file->inode.created_timestamp = time(NULL);
    new_file->inode.modified_timestamp = new_file->inode.created_timestamp;
    new_file->data = NULL;
    new_file->next = file_list;
    file_list = new_file;

    return 0;
}

int afs_delete_file(const char *filename) {
    struct afs_file **current = &file_list;
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

struct afs_file *afs_open_file(const char *filename) {
    struct afs_file *current = file_list;
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

int afs_create_directory(const char *dirname) {
    // Check if the directory already exists
    struct afs_directory *current = directory_list;
    while (current) {
        if (strcmp(current->dirname, dirname) == 0) {
            return -1; // Directory already exists
        }
        current = current->next;
    }

    // Create a new directory
    struct afs_directory *new_directory = (struct afs_directory *)malloc(sizeof(struct afs_directory));
    if (!new_directory) return -1;

    new_directory->dirname = strdup(dirname);
    if (!new_directory->dirname) {
        free(new_directory);
        return -1;
    }

    new_directory->inode.inode_number = next_inode_number++;
    new_directory->inode.size = 0;
    new_directory->inode.created_timestamp = time(NULL);
    new_directory->inode.modified_timestamp = new_directory->inode.created_timestamp;
    new_directory->children = NULL;
    new_directory->num_children = 0;
    new_directory->next = directory_list;
    directory_list = new_directory;

    return 0;
}

int afs_delete_directory(const char *dirname) {
    struct afs_directory **current = &directory_list;
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

struct afs_inode *afs_list_directory(const char *dirname, size_t *num_entries) {
    struct afs_directory *current = directory_list;
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

int afs_get_metadata(const char *name, struct afs_inode *inode) {
    struct afs_file *file = file_list;
    while (file) {
        if (strcmp(file->filename, name) == 0) {
            *inode = file->inode;
            return 0;
        }
        file = file->next;
    }

    struct afs_directory *directory = directory_list;
    while (directory) {
        if (strcmp(directory->dirname, name) == 0) {
            *inode = directory->inode;
            return 0;
        }
        directory = directory->next;
    }

    return -1; // File or directory not found
}

int afs_update_metadata(const char *name, const struct afs_inode *inode) {
    struct afs_file *file = file_list;
    while (file) {
        if (strcmp(file->filename, name) == 0) {
            file->inode = *inode;
            return 0;
        }
        file = file->next;
    }

    struct afs_directory *directory = directory_list;
    while (directory) {
        if (strcmp(directory->dirname, name) == 0) {
            directory->inode = *inode;
            return 0;
        }
        directory = directory->next;
    }

    return -1; // File or directory not found
}