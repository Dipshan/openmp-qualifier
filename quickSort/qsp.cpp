#include "../common/common.h"

int partition(int *array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[high]);
    return i + 1;
}

void quickSort(int *array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

int main(int argc, char **argv) {
    int size, seed;

    if (argc == 3) {
        // Command line mode
        size = std::stoi(argv[1]);
        seed = std::stoi(argv[2]);
    } else {
        // Interactive mode
        std::cout << "=== Parallel Quick Sort ===" << std::endl;
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
    quickSort(array, 0, size - 1);
    auto end = std::chrono::high_resolution_clock::now();

    printArray(array, size, "Sorted Array");

    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel Quick Sort Time: " << duration.count() << " seconds" << std::endl;

    if (isSorted(array, size)) {
        std::cout << "Successfully sorted!" << std::endl;
    } else {
        std::cout << "Sorting failed!" << std::endl;
    }

    delete[] array;
    return 0;
}
