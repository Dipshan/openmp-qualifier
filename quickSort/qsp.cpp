// qsp.cpp - Parallel Quicksort using OpenMP Tasks
// Implements a parallel quicksort algorithm for the Tour d'Algorithms project.

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <omp.h>

// A threshold for subarray size. If a subarray is smaller than this,
// it will be sorted serially, as the overhead of creating parallel tasks
// is not worth it for small arrays.
constexpr int PARALLEL_CUTOFF = 1000;

/**
 * @brief Generates a vector of random integers.
 * @param size The number of integers to generate.
 * @param seed The seed for the random number generator.
 * @return A std::vector<int> containing the random numbers.
 */
std::vector<int> generateRandomArray(int size, int seed) {
    srand(seed);
    std::vector<int> data;
    data.reserve(size); // Pre-allocate memory to avoid reallocations
    for (int i = 0; i < size; ++i) {
        data.push_back(std::rand() % 1000000);
    }
    return data;
}

/**
 * @brief Swaps two integer values.
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Partitions the array for Quicksort using median-of-three pivot selection.
 * This helps avoid the worst-case O(n^2) behavior on sorted/nearly-sorted data.
 * @param data The vector to be partitioned.
 * @param left The starting index of the subarray.
 * @param right The ending index of the subarray.
 * @return The index of the pivot element after partitioning.
 */
int partition(std::vector<int>& data, int left, int right) {
    // Median-of-three pivot selection
    int mid = left + (right - left) / 2;
    if (data[mid] < data[left]) {
        swap(&data[left], &data[mid]);
    }
    if (data[right] < data[left]) {
        swap(&data[left], &data[right]);
    }
    if (data[mid] < data[right]) {
        swap(&data[mid], &data[right]);
    }
    // Now, the pivot is at data[right]
    int pivotValue = data[right];
    int i = (left - 1);

    for (int j = left; j < right; ++j) {
        if (data[j] <= pivotValue) {
            i++;
            swap(&data[i], &data[j]);
        }
    }
    swap(&data[i + 1], &data[right]);
    return (i + 1);
}

/**
 * @brief The recursive Quicksort function, parallelized with OpenMP tasks.
 * @param data The vector to be sorted.
 * @param left The starting index of the subarray.
 * @param right The ending index of the subarray.
 */
void parallelQuicksort(std::vector<int>& data, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(data, left, right);

        // Check if the subarray is large enough to benefit from parallelization
        bool is_large_enough = (right - left) > PARALLEL_CUTOFF;

        // Create a task for the left subarray
        #pragma omp task shared(data) if(is_large_enough)
        parallelQuicksort(data, left, pivotIndex - 1);

        // Create a task for the right subarray
        #pragma omp task shared(data) if(is_large_enough)
        parallelQuicksort(data, pivotIndex + 1, right);
        
        // Note: An implicit taskwait occurs at the end of the single region in main.
        // If this function were called outside of a task region, we would need #pragma omp taskwait here.
    }
}


int main(int argc, char** argv) {
    if (argc < 3) {
        // Updated usage message to match project specification 
        std::cerr << "Usage: " << argv[0]
                  << " [number of random integers to generate] [seed value for random number generation]"
                  << std::endl;
        return -1;
    }

    int size = std::stoi(argv[1]);
    int seed = std::stoi(argv[2]);

    std::vector<int> data = generateRandomArray(size, seed);

    // Start timing
    auto startTime = std::chrono::high_resolution_clock::now();

    // The main parallel region.
    // A team of threads is created here.
    #pragma omp parallel
    {
        // The 'single' pragma ensures that only one thread kicks off the sorting process.
        // 'nowait' allows other threads to start picking up tasks immediately
        // without waiting for the master thread to finish the initial call.
        #pragma omp single nowait
        parallelQuicksort(data, 0, data.size() - 1);
    } // Threads synchronize here, ensuring all tasks are complete.

    // Stop timing
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;

    // Print running time to stderr as requested [cite: 49]
    std::cerr << elapsed.count() << std::endl;

    return 0;
}