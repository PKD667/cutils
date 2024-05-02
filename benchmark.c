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
    // Benchmark implementation for rmrf
}

void benchmark_rdfile() {
    // Benchmark implementation for rdfile
}

void benchmark_wrfile() {
    // Benchmark implementation for wrfile
}

void benchmark_pmkdir() {
    // Benchmark implementation for pmkdir
}

void benchmark_mvsp() {
    // Benchmark implementation for mvsp
}

void benchmark_ls() {
    // Benchmark implementation for ls
}

void benchmark_splita() {
    // Benchmark implementation for splita
}

void benchmark_countc() {
    // Benchmark implementation for countc
}

int main() {
    uint64_t start, end;

    start = get_time_ns();
    benchmark_rmrf();
    end = get_time_ns();
    printf("rmrf benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_rdfile();
    end = get_time_ns();
    printf("rdfile benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_wrfile();
    end = get_time_ns();
    printf("wrfile benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_pmkdir();
    end = get_time_ns();
    printf("pmkdir benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_mvsp();
    end = get_time_ns();
    printf("mvsp benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_ls();
    end = get_time_ns();
    printf("ls benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_splita();
    end = get_time_ns();
    printf("splita benchmark: %lu ns\n", end - start);

    start = get_time_ns();
    benchmark_countc();
    end = get_time_ns();
    printf("countc benchmark: %lu ns\n", end - start);

    return 0;
}
