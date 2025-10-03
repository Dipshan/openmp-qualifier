#include "common/common.h"
#include <algorithm>

int main(int argc, char **argv) {
    int size, seed;

    if (argc == 3) {
        // Command line mode
        size = std::stoi(argv[1]);
        seed = std::stoi(argv[2]);
    } else {
        // Interactive mode
        std::cout << "=== STL Sort Reference ===" << std::endl;
        size = getUserInput();
        std::cout << "Enter seed value for random number generation: ";
        std::cin >> seed;
    }

    // Validation
    if (size < 1) {
        std::cerr << "Size must be at least 1 element." << std::endl;
        return -1;
    }
    if (size > MAX_ELEMENTS) {
        std::cerr << "Size cannot exceed " << MAX_ELEMENTS << " elements." << std::endl;
        return -1;
    }

    int *array = randNumArray(size, seed);

    std::cout << "\nSorting " << size << " elements (random numbers 1-" << MAX_RANDOM_VALUE << ")..." << std::endl;
    printArray(array, size, "Random Array");

    auto start = std::chrono::high_resolution_clock::now();
    std::sort(array, array + size);
    auto end = std::chrono::high_resolution_clock::now();

    printArray(array, size, "Sorted Array");

    std::chrono::duration<double> duration = end - start;
    std::cout << "STL Sort Time: " << duration.count() << " seconds" << std::endl;

    if (isSorted(array, size)) {
        std::cout << "Successfully sorted!" << std::endl;
    } else {
        std::cout << "Sorting failed!" << std::endl;
    }

    delete[] array;
    return 0;
}
