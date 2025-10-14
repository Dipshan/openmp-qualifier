#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm> // For std::swap
#include <cstdlib>   // For std::rand, std::srand

/**
 * @brief Generates an array of random integers.
 * @param size The number of elements in the array.
 * @param seed The seed for the random number generator.
 * @return A pointer to the dynamically allocated array.
 */
int* randNumArray(const int size, const int seed) {
    std::srand(seed);
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 1000000;
    }
    return array;
}

/**
 * @brief Partitions the array for the Quick Sort algorithm.
 * @param array The array to be partitioned.
 * @param low The starting index.
 * @param high The ending index.
 * @return The partitioning index.
 */
int partition(int* array, int low, int high) {
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

/**
 * @brief Performs a serial Quick Sort on an array with Median-of-Three pivot selection.
 * @param array The array to sort.
 * @param low The starting index of the portion to sort.
 * @param high The ending index of the portion to sort.
 */
void quickSort_serial(int* array, int low, int high) {
    if (low < high) {
        // --- START: Median-of-Three Pivot Selection ---
        // This prevents the worst-case O(n^2) behavior and stack overflow.
        int mid = low + (high - low) / 2;
        if (array[mid] < array[low]) {
            std::swap(array[low], array[mid]);
        }
        if (array[high] < array[low]) {
            std::swap(array[low], array[high]);
        }
        if (array[mid] < array[high]) {
            std::swap(array[mid], array[high]);
        }
        // The median of the three is now in array[high], ready for partitioning.
        // --- END: Median-of-Three Pivot Selection ---
        
        int pi = partition(array, low, high);

        quickSort_serial(array, low, pi - 1);
        quickSort_serial(array, pi + 1, high);
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " [number of random integers] [seed value]" << std::endl;
        return -1;
    }

    int size = std::stoi(argv[1]);
    int seed = std::stoi(argv[2]);

    int* array = randNumArray(size, seed);

    auto start = std::chrono::high_resolution_clock::now();
    quickSort_serial(array, 0, size - 1);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    std::cout << duration.count() << std::endl;

    delete[] array;
    return 0;
}

