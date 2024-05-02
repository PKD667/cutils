#include "cutils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// High-resolution timer
static inline uint64_t get_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
}

void benchmark_rmrf() {
    uint64_t start = get_time_ns();
    rmrf("test_directory");
    uint64_t end = get_time_ns();
    printf("rmrf execution time: %lu ns\n", end - start);
}

void benchmark_rdfile() {
    char* buffer;
    uint64_t start = get_time_ns();
    rdfile("test_file.txt", &buffer);
    uint64_t end = get_time_ns();
    free(buffer);
    printf("rdfile execution time: %lu ns\n", end - start);
}

void benchmark_wrfile() {
    char* data = "This is a test string for wrfile benchmarking.";
    uint64_t start = get_time_ns();
    wrfile("test_output.txt", data);
    uint64_t end = get_time_ns();
    printf("wrfile execution time: %lu ns\n", end - start);
}

void benchmark_pmkdir() {
    uint64_t start = get_time_ns();
    pmkdir("test_directory/sub_directory");
    uint64_t end = get_time_ns();
    printf("pmkdir execution time: %lu ns\n", end - start);
}

void benchmark_mvsp() {
    uint64_t start = get_time_ns();
    mvsp("test_file.txt", "test_directory/test_file.txt");
    uint64_t end = get_time_ns();
    printf("mvsp execution time: %lu ns\n", end - start);
}

void benchmark_ls() {
    uint64_t start = get_time_ns();
    char** files = ls("test_directory");
    uint64_t end = get_time_ns();
    free(files);
    printf("ls execution time: %lu ns\n", end - start);
}

void benchmark_splita() {
    char* test_string = "This,is,a,test,string,for,splita,benchmarking";
    char** result;
    uint64_t start = get_time_ns();
    splita(test_string, ',', &result);
    uint64_t end = get_time_ns();
    free(result);
    printf("splita execution time: %lu ns\n", end - start);
}

void benchmark_countc() {
    char* test_string = "This is a test string for countc benchmarking.";
    uint64_t start = get_time_ns();
    countc(test_string, 't');
    uint64_t end = get_time_ns();
    printf("countc execution time: %lu ns\n", end - start);
}

int main() {
    printf("Starting benchmarks...\n");

    benchmark_rmrf();
    benchmark_rdfile();
    benchmark_wrfile();
    benchmark_pmkdir();
    benchmark_mvsp();
    benchmark_ls();
    benchmark_splita();
    benchmark_countc();

    printf("Benchmarks completed.\n");

    return 0;
}
