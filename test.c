#include "cutils.h"

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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
    assert(isdir("src") == 0);
    assert(isdir("src/system.c") == 2);
    assert(isdir("src/doesnotexist") == 1);
}

// Add tests for file operations
void test_rmrf() {
    // Test implementation for rmrf
    // create a directory
    int status = mkdir("test_dir", 0700);
    assert(status == 0); // Assert that directory was created successfully

    // create a file in the directory
    FILE *file = fopen("test_dir/test_file", "w");
    assert(file != NULL); // Assert that file was created successfully
    fclose(file);

    // call rmrf function
    rmrf("test_dir");

    // check if directory still exists
    struct stat st;
    status = stat("test_dir", &st);
    assert(status == -1); // Assert that directory was removed successfully
}

void test_rdfile() {
    // Test implementation for rdfile
    char* test_string = "Hello, World!";
    // create a file
    FILE *file = fopen("test_file", "w");
    assert(file != NULL); // Assert that file was created successfully
    fputs(test_string, file);
    fclose(file);

    // call rdfile function
    char *content;
    long size = rdfile("test_file",&content);

    assert(size == strlen(test_string)); // Assert that size is correct

    // check if content is correct
    assert(strncmp(content, test_string,size) == 0); // Assert that content is correct

    // clean up
    free(content);
    remove("test_file");
}

void test_wrfile() {
    // Test implementation for wrfile
    // call wrfile function
    wrfile("test_file", "Hello, World!");

    // open the file and check its content
    FILE *file = fopen("test_file", "r");
    assert(file != NULL); // Assert that file was opened successfully

    char content[14];
    fgets(content, sizeof(content), file);
    fclose(file);

    // check if content is correct
    assert(strcmp(content, "Hello, World!") == 0); // Assert that content is correct

    // clean up
    remove("test_file");
}

void test_pmkdir() {
    // Test implementation for pmkdir
    const char *path = "/tmp/testdir/subdir";

    // Call the function to test
    pmkdir(path);

    // Check if the directory was created
    struct stat st = {0};
    assert(stat(path, &st) == 0);
    assert(S_ISDIR(st.st_mode));

    // Cleanup
    rmdir("/tmp/testdir/subdir");
    rmdir("/tmp/testdir");
}

void test_mvsp() {
    // Create a temporary file
    FILE *tmp = tmpfile();
    // Get the file name
    char *old_path = tmpnam(NULL);
    // Define a new path
    char *new_path = "/tmp/new_file";

    // Write something to the file
    fputs("Hello, World!", tmp);
    fclose(tmp);

    // Move the file
    int result = mvsp(old_path, new_path);

    // Check if the file was moved successfully
    assert(result == 0);

    // Check if the new file exists
    FILE *new_file = fopen(new_path, "r");
    assert(new_file != NULL);

    // Check the content of the new file
    char content[14];
    fgets(content, sizeof(content), new_file);
    fclose(new_file);
    assert(strcmp(content, "Hello, World!") == 0);

    // Clean up
    remove(new_path);
}
void test_ls() {
    char** result = ls("src");
    assert(result != NULL); // ls should return a non-null result for an existing directory

    // Check if known files are in the result
    int found_system_c = 0;
    for (int i = 0; result[i] != NULL; i++) {
        if (strcmp(result[i], "system.c") == 0) {
            found_system_c = 1;
            break;
        }
    }
    assert(found_system_c); // system.c should be found in the src directory

    // Test with a non-existing directory
    char** result_non_existing = ls("non_existing_directory");
    assert(result_non_existing == NULL); // ls should return NULL for a non-existing directory
}

void test_splita() {
    char** result;
    unsigned int count = splita("Hello,World", ',', &result);

    assert(count == 2); // splita should return 2 for "Hello,World" with ',' as delimiter

    // Check if the split strings are correct
    assert(strcmp(result[0], "Hello") == 0); // First string should be "Hello"
    assert(strcmp(result[1], "World") == 0); // Second string should be "World"

    // Remember to free the result after use
    for (unsigned int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

void test_countc() {
    // Test implementation for countc
    int count = countc("Hello, World!", 'l');
    assert(count == 3); // countc should return 3 for "Hello, World!" with 'l' as the character to count

    count = countc("Hello, World!", 'z');
    assert(count == 0); // countc should return 0 for "Hello, World!" with 'z' as the character to count

    count = countc("", 'l');
    assert(count == 0); // countc should return 0 for an empty string
}

void test_strinarr() {
    char* arr[] = {"Hello", "World", "Test", "Example"};
    long arrsize = sizeof(arr) / sizeof(arr[0]);

    // Test with a value that is in the array
    int index = strinarr("Test", arr, arrsize);
    assert(index == 2); // strinarr should return 2 for "Test" in the given array

    // Test with a value that is not in the array
    index = strinarr("NotInArray", arr, arrsize);
    assert(index == -1); // strinarr should return -1 for a value that is not in the array
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
