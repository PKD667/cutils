/*
The CUtils Library is a collection of C functions.
It can be used for any C project, but it was originally made for the Libspm/CCCP project.
It is licensed under the GNU General Public License v3.0.

 * Copyright (C) 2019-2024 PKD <pkd@unsuspicious.org>

*/
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"


#ifndef CUTILS_H
#define CUTILS_H


// Path: cutils.c

/*
General system management
Functions : 
 * rmrf  - Remove a file or a folder (`rm -rf`)
 * rdfile - Read an entire file (`cat`)
 * wrfile - Write an entire file (`>`)
 * pmkdir - Create a folder (`mkdir -p`)
 * ls  - List files in a folder (`ls`)
 * mvsp - Move a file or a folder and create the destination folder if it doesn't exist (`install -D`)
 * isdir - Check if a folder exists (`test -d`)


*/

// remove a file or a folder recursively
int rmrf(char *path);

// read entire file safely
long rdfile(const char* filePath,char** buffer);

// write entire file safely
int wrnfile(const char* filePath,char* buffer,long size);
#define wrfile(filePath,buffer) wrnfile(filePath,buffer,strlen(buffer))

/*
    Check if a dir exists : 
        * 0 - doesn't exist
        * 1 - exists
        * 2 - Not a directory
*/
int isdir (const char *d);
// create dir recursivelty (similar to mkdir -p)
int pmkdir (const char *dir);
//  move a file and create the dir if it doesn't exist
int mvsp(char* old_path,char* new_path);
// LIST  file in a dir
char** ls(char* path);
// exec a shell command and return the output
char* exec(const char* cmd);

/*
String utils
Functions : 
 * popchar - Remove a character from a string
 * popcharn - Remove a character from a string (with a size limit)
 * splita - Split a string into an array of strings
 * countc - Count the number of occurences of a char in a string
 * strinarr - Check if a string is in an array
*/

#define popcharn(str,pos,s_size) if (pos < s_size) { memmove(&str[pos], &str[pos + 1], s_size - pos - 1); str[s_size-1] = '\0'; }
#define popchar(str,pos) popcharn(str,pos,strlen(str))

// split and alloc
//YOU NEED TO PASS A WRITABLE ARRAY. DON'T FREE IT. IT'S USED AS A POOL.
unsigned int splita (char* string,char delim,char*** dest);

// to count the number of occurences of a char in a string
unsigned int countc(const char* string,char c);

// check if a string is in an array
int strinarr( char* val, char** arr,long arrsize);


/*
Hashtable implementation
Functions : 
 * hm_create - Create a new hashtable
 * hm_add - Add a key-value pair to a hashtable
 * hm_get - Get a value from a hashtable
 * hm_rm - Remove a key-value pair from a hashtable
 * hm_visualize - Print the content of a hashtable
 * hm_hash - Hash a string
*/

// a key-value pair
typedef struct {
    char* key;
    void* value;
} pair;

// an item in the hashtable
// it is basically a list of key-value pairs
// it is used to handle collisions
typedef struct {
    pair* data;
    unsigned int size;
    unsigned int capacity;
} item;

// the hashtable
typedef struct {
    item* items;
    unsigned int capacity;
} hashtable;

// create a new hashtable
hashtable* hm_create(unsigned int capacity);

// add a key-value pair to a hashtable
int hm_add(hashtable* hm, char* key, void* value);

// get a value from a hashtable
void* hm_get(hashtable* hm, char* key);

// remove a key-value pair from a hashtable
int hm_rm(hashtable* hm, char* key);

// print the content of a hashtable
int hm_visualize(hashtable* hm);

// hash a string
unsigned int hm_hash(hashtable* hm, char* key);

// here we are converting a pair list into a hash table
hashtable* hm_init(void* kvlist[][2],int size);




/*
Logging and debug utils
Functions : 
 * msg - Print a formatted message to stdout
 * dbg - Print a formatted message with debug options
*/
// level of the message for msg() function
enum level {
    INFO,
    ERROR,
    WARNING,
    MEMORY,
    FATAL
};

extern int DEBUG;
extern char* DEBUG_FN;
extern char* DEBUG_FILE;

// a tool to have cool terminal output
int msg(enum level msgLevel, const char* message,...);

int f_dbg__(int level,int line,const char* function,const char* file,char* message,...);
#define dbg(level,message,...) f_dbg__(level,__LINE__,__func__,__FILE__,message,##__VA_ARGS__)


// memory safety and debugging
void* dbg_malloc(size_t size,char* file,int line);
void* dbg_calloc(size_t nmemb,size_t size,char* file,int line);
void* dbg_realloc(void* ptr,size_t size,char* file,int line);
char* dbg_strdup(char* str,char* file,int line);

void dbg_free(void* ptr,char* file,int line);

#if MEMCHECK == 1 // only define these if we're doing memory checking
    #define malloc(size) dbg_malloc(size,__FILE__,__LINE__)
    #define calloc(nmemb,size) dbg_calloc(nmemb,size,__FILE__,__LINE__)
    #define realloc(ptr,size) dbg_realloc(ptr,size,__FILE__,__LINE__)
    #define strdup(str) dbg_strdup(str,__FILE__,__LINE__)
    #define free(ptr) dbg_free(ptr,__FILE__,__LINE__)
#endif

int check_leaks();

#endif




