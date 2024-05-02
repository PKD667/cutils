# CUtils - A C Utilities Library

CUtils is a collection of utility functions and tools written in C, designed to simplify common programming tasks in C projects.

## Getting Started

To use CUtils in your project, clone this repository and include the `cutils.h` header file in your C source files.

## Running Tests

To run the unit tests for CUtils, execute the following command:

```
make test
```

## Benchmarking Suite

To ensure the performance of CUtils remains optimal, a benchmarking suite has been added. This suite measures the execution time of critical functions within the library.

### Running the Benchmarking Suite

To run the benchmarking suite, execute the following command:

```
make benchmark
```

This will compile and run the benchmark tests for functions such as `rmrf`, `rdfile`, `wrfile`, `pmkdir`, `mvsp`, `ls`, `splita`, and `countc`. The results will be displayed in the console.

### Interpreting Benchmark Results

The benchmark results are displayed in nanoseconds (ns) and provide an insight into the performance of each function. Lower values indicate better performance. Use these results to identify potential bottlenecks or areas for optimization.

### Automatic Benchmark Updates

The repository is configured with GitHub Actions to automatically run the benchmarking suite and update the `README.md` with the latest results upon every push. This ensures that the performance data is always up-to-date.

## Automated Testing and Benchmarking with GitHub Actions

CUtils now leverages GitHub Actions to automatically run the test suite and benchmarking suite upon every push to the repository and on pull requests. This ensures that the code quality and performance are consistently monitored and maintained.

### Test Suite Automation

The test suite is executed automatically using the `make test` command through the GitHub Actions workflow defined in `.github/workflows/run_tests.yml`. This workflow triggers on every push and pull request to the repository.

![Test Workflow Status](https://github.com/PKD667/cutils/actions/workflows/run_tests.yml/badge.svg)

### Benchmark Suite Automation

Similarly, the benchmarking suite is run using the `make benchmark` command via the GitHub Actions workflow found in `.github/workflows/run_benchmarks.yml`. This workflow is triggered on every push to the repository.

![Benchmark Workflow Status](https://github.com/PKD667/cutils/actions/workflows/run_benchmarks.yml/badge.svg)

## Contributing

Contributions to CUtils are welcome. Please submit a pull request or open an issue to discuss proposed changes or additions.
