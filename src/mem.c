
#include "../cutils.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define MAX_PTRS 4096

typedef struct {
    void* ptr;
    int size;
    const char* file;
    int line;
} ptr_entry;

typedef struct {
    ptr_entry entry;
    const char* free_file;
    int free_line;
} freed_ptr_entry;

ptr_entry alloced_ptrs[MAX_PTRS] = {0};
int alloced_ptrs_i = 0;

freed_ptr_entry freed_ptrs[MAX_PTRS] = {0};
int freed_ptrs_i = 0;

int log_ptr(void* ptr,int size, const char* file, int line)
{
    if (alloced_ptrs_i >= MAX_PTRS)
    {
        dbg(1, "log_ptr: max pointer count exceeded");
        return 1;
    }
    alloced_ptrs[alloced_ptrs_i].ptr = ptr;
    alloced_ptrs[alloced_ptrs_i].file = file;
    alloced_ptrs[alloced_ptrs_i].line = line;
    alloced_ptrs_i++;
    return 0;
}

int unlog_ptr(void* ptr, const char* file, int line)
{
    for (int i = 0; i < alloced_ptrs_i; i++) {
        if (alloced_ptrs[i].ptr == ptr) {
            freed_ptrs[freed_ptrs_i].entry = alloced_ptrs[i];
            freed_ptrs[freed_ptrs_i].free_file = file;
            freed_ptrs[freed_ptrs_i].free_line = line;
            freed_ptrs_i++;
            alloced_ptrs[i].ptr = NULL;
            return alloced_ptrs[i].size;
        }
    }
    return -1;
}

char* find_dfree(char* ptr)
{
    for (int i = 0; i < freed_ptrs_i; i++) {
        if (freed_ptrs[i].entry.ptr == ptr) {
            return (char*) freed_ptrs[i].free_file;
        }
    }
    return NULL;
}

int check_leaks()
{
    int leaks = 0;
    for (int i = 0; i < alloced_ptrs_i; i++) {
        if (alloced_ptrs[i].ptr != NULL) {
            dbg(1, "Leak: %p: %s:%d", alloced_ptrs[i].ptr, alloced_ptrs[i].file, alloced_ptrs[i].line);
            leaks++;
        }
    }
    return leaks;
}

void* dbg_malloc(size_t size, char* file, int line)
{
    dbg(4, "dbg_malloc: %s:%d - %zu bytes", file, line, size);
    void* ptr = malloc(size);
    if (ptr == NULL) {
        dbg(1, "dbg_malloc: malloc failed");
    }
    log_ptr(ptr,size, file, line);
    return ptr;
}

void* dbg_calloc(size_t nmemb, size_t size, char* file, int line)
{
    dbg(4, "dbg_calloc: %s:%d - %zu bytes", file, line, nmemb * size);
    void* ptr = calloc(nmemb, size);
    if (ptr == NULL) {
        dbg(1, "dbg_calloc: calloc failed");
    }
    log_ptr(ptr,size, file, line);
    return ptr;
}

void* dbg_realloc(void* ptr, size_t size, char* file, int line)
{
    void* newptr = realloc(ptr, size);
    if (newptr == NULL) {
        dbg(1, "dbg_realloc: realloc failed");
    }
    int s = unlog_ptr(ptr, file, line);
    if (s < 0)
    {
        char* pos = find_dfree((char*) ptr);
        if (pos != NULL)
        {
            dbg(1, "dbg_free: trying to free already freed at %s pointer --> %p", pos, ptr);
        } else {
            dbg(1, "dbg_free: trying to free unallocated pointer --> %p", ptr);
        }
    }
    dbg(4, "dbg_free: %s:%d %p - %zu bytes", file, line, ptr, s);
    log_ptr(newptr,size, file, line);
    return newptr;
}

char* dbg_strdup(char* str, char* file, int line)
{
    size_t size = strlen(str) + 1;
    dbg(4, "dbg_strdup: %s:%d - %zu bytes", file, line, size);
    char* newstr = strdup(str);
    if (newstr == NULL) {
        dbg(1, "dbg_strdup: strdup failed");
    }
    log_ptr(newstr,size, file, line);
    return newstr;
}

void dbg_free(void* ptr, char* file, int line)
{
    int s = unlog_ptr(ptr, file, line);
    if (s < 0)
    {
        char* pos = find_dfree((char*) ptr);
        if (pos != NULL)
        {
            dbg(1, "dbg_free: trying to free already freed at %s pointer --> %p", pos, ptr);
        } else {
            dbg(1, "dbg_free: trying to free unallocated pointer --> %p", ptr);
        }
    }
    dbg(4, "dbg_free: %s:%d %p - %zu bytes", file, line, ptr, s);
    free(ptr);
}

