#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "common/common.h"
#include "sort.h"

// Function declarations for each sorting algorithm
void runBubbleSortSerial(int* array, int size);
void runBubbleSortParallel(int* array, int size);
void runQuickSortSerial(int* array, int size);
void runQuickSortParallel(int* array, int size);
void runMergeSortSerial(int* array, int size);
void runMergeSortParallel(int* array, int size);
void runReferenceSort(int* array, int size);

// Function pointer type for sorting functions
typedef void (*SortFunction)(int*, int);

// Structure to map executable names to sorting functions
struct SortAlgorithm {
    std::string name;
    SortFunction function;
    std::string description;
};

// Array of available sorting algorithms
SortAlgorithm algorithms[] = {
    {"bss", runBubbleSortSerial, "Bubble Sort Serial"},
    {"bsp", runBubbleSortParallel, "Bubble Sort Parallel"},
    {"qss", runQuickSortSerial, "Quick Sort Serial"},
    {"qsp", runQuickSortParallel, "Quick Sort Parallel"},
    {"mss", runMergeSortSerial, "Merge Sort Serial"},
    {"msp", runMergeSortParallel, "Merge Sort Parallel"},
    {"reference", runReferenceSort, "STL Reference Sort"}
};

const int NUM_ALGORITHMS = sizeof(algorithms) / sizeof(algorithms[0]);

void printUsage(const std::string& programName) {
    std::cerr << "Usage: " << programName << " [algorithm] [array_size] [random_seed]" << std::endl;
    std::cerr << std::endl;
    std::cerr << "Available algorithms:" << std::endl;
    for (int i = 0; i < NUM_ALGORITHMS; i++) {
        std::cerr << "  " << algorithms[i].name << " - " << algorithms[i].description << std::endl;
    }
    std::cerr << std::endl;
    std::cerr << "Examples:" << std::endl;
    std::cerr << "  " << programName << " bss 10000 42" << std::endl;
    std::cerr << "  " << programName << " qsp 50000 123" << std::endl;
}

int main(int argc, char** argv) {
    // Check command line arguments
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    std::string algorithmName = argv[1];
    int size, seed;

    // Parse array size
    try {
        size = std::stoi(argv[2]);
        if (size <= 0) {
            throw std::invalid_argument("Array size must be positive");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid array size '" << argv[2] << "'. " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Parse random seed
    try {
        seed = std::stoi(argv[3]);
    } catch (const std::exception& e) {
        std::cerr << "Error: Invalid random seed '" << argv[3] << "'. " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Find the requested algorithm
    SortFunction selectedAlgorithm = nullptr;
    std::string algorithmDescription;

    for (int i = 0; i < NUM_ALGORITHMS; i++) {
        if (algorithms[i].name == algorithmName) {
            selectedAlgorithm = algorithms[i].function;
            algorithmDescription = algorithms[i].description;
            break;
        }
    }

    if (selectedAlgorithm == nullptr) {
        std::cerr << "Error: Unknown algorithm '" << algorithmName << "'" << std::endl;
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    // Display program information
    std::cout << "=== OpenMP Sorting Algorithm ===" << std::endl;
    std::cout << "Algorithm: " << algorithmDescription << std::endl;
    std::cout << "Array Size: " << size << std::endl;
    std::cout << "Random Seed: " << seed << std::endl;
    std::cout << "================================" << std::endl;

    // Generate random array
    int* array = randNumArray(size, seed);
    
    if (array == nullptr) {
        std::cerr << "Error: Failed to allocate memory for array" << std::endl;
        return EXIT_FAILURE;
    }

    // Display first few elements (for verification)
    if (size <= 20) {
        std::cout << "Original Array: ";
        printArray(array, size);
    } else {
        std::cout << "First 10 elements of original array: ";
        printArray(array, 10);
    }

    // Execute the selected sorting algorithm
    try {
        selectedAlgorithm(array, size);
    } catch (const std::exception& e) {
        std::cerr << "Error during sorting: " << e.what() << std::endl;
        delete[] array;
        return EXIT_FAILURE;
    }

    // Verify the result
    if (isSorted(array, size)) {
        std::cout << "Sorting completed successfully." << std::endl;
    } else {
        std::cerr << "Sorting failed!" << std::endl;
    }

    // Display first few elements of sorted array
    if (size <= 20) {
        std::cout << "Sorted Array: ";
        printArray(array, size);
    } else {
        std::cout << "First 10 elements of sorted array: ";
        printArray(array, 10);
    }

    // Clean up
    delete[] array;

    return EXIT_SUCCESS;
}

// Implementation of sorting algorithm wrappers
void runBubbleSortSerial(int* array, int size) {
    Timer timer;
    timer.start();
    bubbleSortSerial(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}

void runBubbleSortParallel(int* array, int size) {
    Timer timer;
    timer.start();
    bubbleSortParallel(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}

void runQuickSortSerial(int* array, int size) {
    Timer timer;
    timer.start();
    quickSortSerial(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}

void runQuickSortParallel(int* array, int size) {
    Timer timer;
    timer.start();
    quickSortParallel(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}

void runMergeSortSerial(int* array, int size) {
    Timer timer;
    timer.start();
    mergeSortSerial(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}

void runMergeSortParallel(int* array, int size) {
    Timer timer;
    timer.start();
    mergeSortParallel(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}

void runReferenceSort(int* array, int size) {
    Timer timer;
    timer.start();
    referenceSort(array, size);
    double elapsed = timer.stop();
    std::cout << "Execution Time: " << elapsed << " seconds" << std::endl;
}