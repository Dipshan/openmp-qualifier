# Project - Tour d’Algorithms: OpenMP Qualifier

### Author: Deepshan Adhikari
### Email: deepadh@siue.edu
### Student ID: 800846035

---

### Project Description
This is a C++ project that implements and compares serial vs parallel versions of three sorting algorithms using OpenMP.

The project investigates performance scalability on multi-core architectures through Bubble Sort, Quick Sort, and Merge Sort.

Each algorithm has both serial and parallel implementations, plus a reference STL sort for comparison.

All programs measure and display execution times for performance analysis.

Features
The project provides the following functionalities:

Multiple Sorting Algorithms: Implements Bubble Sort, Quick Sort, and Merge Sort with both serial and parallel versions.

OpenMP Parallelization: Uses OpenMP directives for efficient multi-core parallel processing.

Performance Timing: Precisely measures execution time using high-resolution clocks.

Input Validation: Validates command line arguments for array size and random seed.

Sorting Verification: Automatically verifies that each sort produces correctly ordered results.

Cross-Platform Compatibility: Handles OpenMP availability with graceful fallbacks.

Comprehensive Testing: Allows performance comparison across different array sizes and algorithms.

Algorithms & Parallelization Strategies
Bubble Sort (O(n²))
Serial: Standard nested loops comparing adjacent elements

Parallel: OpenMP parallelization of the inner loop using #pragma omp parallel for

Quick Sort (O(n log n) expected)
Serial: Recursive divide-and-conquer with pivot partitioning

Parallel: Task-based parallelism using #pragma omp task for recursive calls

Merge Sort (O(n log n) worst-case)
Serial: Recursive divide-and-conquer with merging of sorted halves

Parallel: Task parallelism for division phase with #pragma omp taskwait for synchronization

Reference Implementation
STL Sort: Uses std::sort() as a performance benchmark reference

Project Structure:

openmp_qualifier/  
├── CMakeLists.txt              // CMake build configuration  
├── Makefile                    // Make build configuration  
├── README                      // Project documentation (this file)  
├── common.h                    // Common utilities and headers  
├── common.cpp                  // Common function implementations
├── bubbleSort/  
│   ├── bss.cpp                 // Serial Bubble Sort implementation  
│   └── bsp.cpp                 // Parallel Bubble Sort implementation
├── quickSort/  
│   ├── qss.cpp                 // Serial Quick Sort implementation  
│   └── qsp.cpp                 // Parallel Quick Sort implementation  
│
├── mergeSort/  
│   ├── mss.cpp                 // Serial Merge Sort implementation  
│   └── msp.cpp                 // Parallel Merge Sort implementation  
│
├── reference.cpp               // STL sort reference implementation  
└── report.pdf                  // Performance analysis report  

Executables

The project builds 7 separate executables:

bss - Serial Bubble Sort

bbp - Parallel Bubble Sort

qss - Serial Quick Sort

qsp - Parallel Quick Sort

mss - Serial Merge Sort

msp - Parallel Merge Sort

reference - STL Sort Reference

How to Compile and Run
Using CLion IDE (Recommended)
Open the project in CLion

Ensure OpenMP is installed: brew install libomp (on macOS)

Click the green play button ▶️ to build and run individual executables

Use CLion's built-in terminal to test with command line arguments

Using Command Line (Make)
bash
# Build all executables
make

# Run individual sorting algorithms
./bss 10000 42        # Serial Bubble Sort with 10,000 elements
./bbp 10000 42        # Parallel Bubble Sort with 10,000 elements
./qss 100000 42       # Serial Quick Sort with 100,000 elements  
./qsp 100000 42       # Parallel Quick Sort with 100,000 elements
./mss 100000 42       # Serial Merge Sort with 100,000 elements
./msp 100000 42       # Parallel Merge Sort with 100,000 elements
./reference 1000000 42 # STL Sort with 1,000,000 elements

# Clean build files
make clean
Using Command Line (CMake)
bash
# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run executables from build directory
./bss 5000 123
Command Line Usage
All executables follow the same command format:

bash
./executable_name [array_size] [random_seed]
Parameters:

array_size: Number of random integers to generate and sort (recommended: 1,000-1,000,000)

random_seed: Seed value for reproducible random number generation

Examples:

bash
# Small test case
./bss 1000 42

# Medium performance test
./qsp 50000 123

# Large-scale test
./reference 1000000 456
Output Format
Each program outputs execution time and verification status:

text
OpenMP: ENABLED (Max threads: 8)
Array size: 10000
Parallel Quick Sort Time: 0.04567 seconds
Sorting verified: OK
Output Includes:

OpenMP status and available threads

Array size being processed

Execution time in seconds

Sorting verification result

Performance Analysis
The project includes a comprehensive report (report.pdf) with:

Execution Time Graphs: Comparing serial vs parallel performance for each algorithm

Architectural Analysis: Explanation of performance behaviors based on CPU and memory architecture

Hyper-Threading Effects: Investigation of hyper-threading impact on parallel performance

Scalability Analysis: How algorithms scale with increasing core counts

Dependencies & Requirements
C++ Compiler: GCC/Clang with C++14 support

OpenMP: libomp (install via Homebrew on macOS: brew install libomp)

CMake: Version 3.10+ or Make utility

Memory: Sufficient RAM for large array allocations

Platform Compatibility
macOS: Fully supported (requires OpenMP installation via Homebrew)

Linux: Native support with OpenMP typically pre-installed

Windows: Supported via WSL2 or MinGW with OpenMP

Notes
The parallel versions will gracefully fall back to serial execution if OpenMP is not available

For meaningful performance comparisons, use array sizes ≥10,000 elements

Hyper-threading analysis requires a processor with hyper-threading capability

All sorting implementations include validation to ensure correct results