#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm> // For std::swap
#include <cstdlib>   // For std::rand, std::srand
#include <omp.h>     // Include OpenMP library

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
 * @brief Performs a parallel Quick Sort on an array using OpenMP tasks.
 * Includes Median-of-Three pivot selection and a task creation threshold.
 * @param array The array to sort.
 * @param low The starting index of the portion to sort.
 * @param high The ending index of the portion to sort.
 */
void quickSort_parallel(int* array, int low, int high) {
    if (low < high) {
        // --- START: Median-of-Three Pivot Selection ---
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
        // --- END: Median-of-Three Pivot Selection ---

        int pi = partition(array, low, high);

        // Threshold to avoid creating tasks for very small subarrays
        if (high - low > 1000) {
            #pragma omp task
            {
                quickSort_parallel(array, low, pi - 1);
            }
            #pragma omp task
            {
                quickSort_parallel(array, pi + 1, high);
            }
        } else {
            // Sort sequentially if the subarray is small
            quickSort_parallel(array, low, pi - 1);
            quickSort_parallel(array, pi + 1, high);
        }
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

    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            quickSort_parallel(array, 0, size - 1);
        }
    } // Implicit barrier here ensures all tasks are finished.

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << duration.count() << std::endl;

    delete[] array;
    return 0;
}