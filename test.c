#include "cutils.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>

int popchar_test()
{
    char str[] = "Hello World";
    printf("%s\n",str);
    popchar(str,6);
    printf("%s\n",str);
    return 0;
}

void test_dbg_malloc()
{
    char* str = dbg_malloc(10, __FILE__, __LINE__);
    assert(str != NULL);
    dbg_free(str, __FILE__, __LINE__);
}

void test_dbg_calloc()
{
    int* arr = dbg_calloc(5, sizeof(int), __FILE__, __LINE__);
    assert(arr != NULL);
    for (int i = 0; i < 5; i++)
    {
        assert(arr[i] == 0);
    }
    dbg_free(arr, __FILE__, __LINE__);
}

void test_dbg_realloc()
{
    char* str = dbg_malloc(10, __FILE__, __LINE__);
    str = dbg_realloc(str, 20, __FILE__, __LINE__);
    assert(str != NULL);
    dbg_free(str, __FILE__, __LINE__);
}

void test_dbg_strdup()
{
    char* str = dbg_strdup("hello", __FILE__, __LINE__);
    assert(str != NULL);
    assert(strcmp(str, "hello") == 0);
    dbg_free(str, __FILE__, __LINE__);
}

void test_dbg_free()
{
    char* str = dbg_malloc(10, __FILE__, __LINE__);
    dbg_free(str, __FILE__, __LINE__);
}

void test_check_leaks()
{
    int leaks = check_leaks();
    assert(leaks == 0);

    char* str = dbg_malloc(10, __FILE__, __LINE__);
    leaks = check_leaks();
    assert(leaks == 1);

    dbg_free(str, __FILE__, __LINE__);
    leaks = check_leaks();
    assert(leaks == 0);
}

void test_isdir()
{
    assert(xisdir("src") == 0);
    assert(xisdir("src/system.c") == 2);
    assert(xisdir("src/doesnotexist") == 1);
}

// Add tests for file operations
void test_rmrf() {
    // Test implementation for rmrf
}

void test_rdfile() {
    // Test implementation for rdfile
}

void test_wrfile() {
    // Test implementation for wrfile
}

void test_pmkdir() {
    // Test implementation for pmkdir
}

void test_mvsp() {
    // Test implementation for mvsp
}

void test_ls() {
    // Test implementation for ls
}

// Add tests for string utilities
void test_splita() {
    // Test implementation for splita
}

void test_countc() {
    // Test implementation for countc
}

// Add tests for system management functions
void test_xisdir() {
    // Test implementation for xisdir
}

void test_exec() {
    // Test implementation for exec
}

int main(int argc, char const *argv[])
{

    DEBUG = 4;

    printf("Running tests...\n");
    printf("popchar_test()\n");
    popchar_test();
    printf("test_dbg_malloc()\n");
    test_dbg_malloc();
    printf("test_dbg_calloc()\n");
    test_dbg_calloc();
    printf("test_dbg_realloc()\n");
    test_dbg_realloc();
    printf("test_dbg_strdup()\n");
    test_dbg_strdup();
    printf("test_dbg_free()\n");
    test_dbg_free();
    printf("test_check_leaks()\n");
    test_check_leaks();
    // Add calls to new test functions here
    printf("All tests passed!\n");
    return 0;
}
