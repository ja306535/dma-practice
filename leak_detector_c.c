#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#undef malloc
#undef calloc
#undef free

static MEM_LEAK *ptr_start = NULL;
static MEM_LEAK *ptr_next = NULL;

/* Adds allocated memory info into the list */
void add(MEM_INFO alloc_info) {
    MEM_LEAK *mem_leak_info = (MEM_LEAK *) malloc(sizeof(MEM_LEAK));
    if (!mem_leak_info) return; // Prevent NULL dereference

    mem_leak_info->mem_info.address = alloc_info.address;
    mem_leak_info->mem_info.size = alloc_info.size;
    strcpy(mem_leak_info->mem_info.file_name, alloc_info.file_name);
    mem_leak_info->mem_info.line = alloc_info.line;
    mem_leak_info->next = NULL;

    if (ptr_start == NULL) {
        ptr_start = mem_leak_info;
        ptr_next = ptr_start;
    } else {
        ptr_next->next = mem_leak_info;
        ptr_next = ptr_next->next;
    }
}

/* Erases memory info from the list */
void erase(unsigned pos) {
    unsigned index = 0;
    MEM_LEAK *alloc_info, *temp;

    if (pos == 0 && ptr_start) {
        temp = ptr_start;
        ptr_start = ptr_start->next;
        free(temp);
    } else {
        for (index = 0, alloc_info = ptr_start; alloc_info && index < pos; alloc_info = alloc_info->next, ++index) {
            if (pos == index + 1 && alloc_info->next) {
                temp = alloc_info->next;
                alloc_info->next = temp->next;
                free(temp);
                break;
            }
        }
    }
}

/* Deletes all elements from the list */
void clear() {
    MEM_LEAK *temp = ptr_start;
    while (ptr_start) {
        temp = ptr_start;
        ptr_start = ptr_start->next;
        free(temp);
    }
}

/* Replacement for malloc */
void *xmalloc(unsigned int size, const char *file, unsigned int line) {
    void *ptr = malloc(size);
    if (ptr) {
        add_mem_info(ptr, size, file, line);
    }
    return ptr;
}

/* Replacement for calloc */
void *xcalloc(unsigned int elements, unsigned int size, const char *file, unsigned int line) {
    unsigned int total_size = elements * size;
    void *ptr = calloc(elements, size);
    if (ptr) {
        add_mem_info(ptr, total_size, file, line);
    }
    return ptr;
}

void add_mem_info(void *mem_ref, unsigned int size, const char *file, unsigned int line) {
    MEM_INFO mem_info;
    mem_info.address = mem_ref;
    mem_info.size = size;
    strncpy(mem_info.file_name, file, FILE_NAME_LENGTH - 1);
    mem_info.file_name[FILE_NAME_LENGTH - 1] = '\0'; // Ensure null termination
    mem_info.line = line;
    
    add(mem_info);
}

void remove_mem_info(void *mem_ref) {
    MEM_LEAK *alloc_info = ptr_start, *prev = NULL;
    unsigned pos = 0;

    while (alloc_info != NULL) {
        if (alloc_info->mem_info.address == mem_ref) {
            if (prev) {
                prev->next = alloc_info->next;
            } else {
                ptr_start = alloc_info->next;
            }
            free(alloc_info);
            return;
        }
        prev = alloc_info;
        alloc_info = alloc_info->next;
        pos++;
    }
}

void xfree(void *mem_ref) {
    if (mem_ref) {
        remove_mem_info(mem_ref);
        free(mem_ref);
    }
}

void report_mem_leak() {
    FILE *fp = fopen(OUTPUT_FILE, "w");
    if (!fp) return;

    MEM_LEAK *leak = ptr_start;
    while (leak) {
        fprintf(fp, "Memory leak detected: Address=%p, Size=%u, File=%s, Line=%u\n",
                leak->mem_info.address, leak->mem_info.size, leak->mem_info.file_name, leak->mem_info.line);
        leak = leak->next;
    }

    fclose(fp);
    clear(); // Free all remaining memory leaks
}
