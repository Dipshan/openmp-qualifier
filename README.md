# Project - Tour d’Algorithms: OpenMP Qualifier

### Authors: 
    Deepshan Adhikari
    deepadh@siue.edu
    Student ID: 800846035

    Sabin Ghimire

    Sumit Shrestha

---

### Project Description
- This is a C++ project that implements and compares serial and parallel versions of three sorting algorithms using OpenMP.
- The project investigates performance scalability on multicore architectures through detailed analysis of Bubble Sort, Merge Sort, and Quick Sort.
- Each algorithm has both serial and parallel implementations, plus a reference STL sort for comparison.
- All programs measure and display execution times for performance analysis.

---

### Features
The project provides the following functionalities:
- **Multiple Sorting Algorithms:** Implements Bubble Sort, Quick Sort, and Merge Sort with both serial and parallel versions.
- **OpenMP Parallelization:** Uses OpenMP directives for efficient multi-core parallel processing.
- **Performance Timing:** Precisely measures execution time using high-resolution clocks.
- **Input Validation:** Validates command line arguments for array size and random seed.
- **Sorting Verification:** Automatically verifies that each sort produces correctly ordered results.
- **Cross-Platform Compatibility:** Handles OpenMP availability with graceful fallbacks.
- **Comprehensive Testing:** Allows performance comparison across different array sizes and algorithms.

---

### Algorithms & Parallelization Strategies

#### Bubble Sort (O(n²))
- Serial: Standard nested loops comparing adjacent elements.
- Parallel: OpenMP parallelization of the inner loop using ```#pragma omp parallel for```

#### Merge Sort (O(n log n) -> worst-case)
- Serial: Recursive divide-and-conquer with merging of sorted halves
- Parallel: Task parallelism for division phase with ```#pragma omp taskwait``` for synchronization

#### Quick Sort (O(n log n) -> expected)
- Serial: Recursive divide-and-conquer with pivot partitioning
- Parallel: Task-based parallelism using ```#pragma omp task``` for recursive calls

#### Reference Implementation
- STL Sort: Uses std::sort() as a performance benchmark reference

---

### Project Structure:
```
openmp_qualifier/  
├── bubbleSort/  
│     ├── bsp.cpp               // Parallel Bubble Sort implementation
│     ├── bss.cpp               // Serial Bubble Sort implementation
├── common/
│     ├── common.cpp            // Common function implementations
│     ├── common.h              // Common utilities and headers  
├── mergeSort/  
│     ├── msp.cpp               // Parallel Merge Sort implementation  
│     ├── mss.cpp               // Serial Merge Sort implementation  
├── quickSort/  
│     ├── qsp.cpp               // Parallel Quick Sort implementation  
│     ├── qss.cpp               // Serial Quick Sort implementation  
├── CMakeLists.txt              // CMake build configuration  
├── main.cpp                    // main file of the program (entry point)
├── Makefile                    // Make build configuration  
├── README.md                   // Project documentation (this file)  
├── reference.cpp               // STL sort reference implementation
├── sort.h                      // Function declarations for all sorting algortihtms
```

---

### Executables
The project builds 7 separate executables:
- bsp - Bubble Sort Parallel
- bss - Bubble Sort Serial
- msp - Merge Sort Parallel
- mss - Merge Sort Serial
- qsp - Quick Sort Parallel
- qss - Quick Sort Serial
- reference - STL Sort Reference

---

### How to Compile and Run
Using CLion IDE (Recommended)
```
# Build all executables
make all

# Build only serial versions (if OpenMP fails)
make serial

# Test all algorithms
make test

# Run individual algorithms

Syntax: ./executable_name [array_size] [random_seed]

./bsp 10000 42           // Parallel Bubble Sort with 10,000 elements using seed size 42
./bss 10000 42           // Serial Bubble Sort with 10,000 elements using seed size 42
./msp 100000 42          // Parallel Merge Sort with 100,000 elements using seed size 42
./mss 100000 42          // Serial Merge Sort with 100,000 elements using seed size 42
./qsp 100000 42          // Parallel Quick Sort with 100,000 elements using seed size 42
./qss 100000 42          // Serial Quick Sort with 100,000 elements using seed size 42
./reference 1000000 42   // STL Sort with 1,000,000 elements using seed size 42
```

---

### Performance Analysis

The project includes a comprehensive report (report.pdf) with:
- **Execution Time Graphs:** Comparing serial vs parallel performance for each algorithm
- **Architectural Analysis:** Explanation of performance behaviors based on CPU and memory architecture
- **Hyper-Threading Effects:** Investigation of hyper-threading impact on parallel performance
- **Scalability Analysis:** How algorithms scale with increasing core counts

---

### Dependencies & Requirements
- **C++ Compiler:** GCC/Clang with C++14 support
- **OpenMP:** libomp (install via Homebrew on macOS: brew install libomp)
- **CMake:** Version 3.10+ or Make utility
- **Memory:** Sufficient RAM for large array allocations (tested in 16GB RAM of Macbook M4 Pro)

---

### Platform Compatibility
- **macOS:** Fully supported (requires OpenMP installation via Homebrew)
- **Linux:** Native support with OpenMP typically pre-installed
- **Windows:** Supported via WSL2 or MinGW with OpenMP

---

### Notes
- The parallel versions will gracefully fall back to serial execution if OpenMP is not available
- For meaningful performance comparisons, use array sizes greater than 10,000 elements
- Hyper-threading analysis requires a processor with hyper-threading capability
- All sorting implementations include validation to ensure correct results