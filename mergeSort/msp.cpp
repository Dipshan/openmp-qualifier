#include "../common/common.h"
#include <omp.h>   // OpenMP header

void merge(int *array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *L = new int[n1];
    int *R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = array[left + i];
    for (int j = 0; j < n2; j++) R[j] = array[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) array[k++] = L[i++];
        else array[k++] = R[j++];
    }

    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int *array, int left, int right, int depth=0) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        // Limit depth to avoid too many threads
        if (depth < 4) {
            #pragma omp task shared(array)
            mergeSort(array, left, mid, depth + 1);

            #pragma omp task shared(array)
            mergeSort(array, mid + 1, right, depth + 1);

            #pragma omp taskwait
        } else {
            // Beyond a certain depth, do it serially
            mergeSort(array, left, mid, depth + 1);
            mergeSort(array, mid + 1, right, depth + 1);
        }
        merge(array, left, mid, right);
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
        std::cout << "=== Parallel Merge Sort ===" << std::endl;
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
    #pragma omp parallel
    {
        #pragma omp single
        mergeSort(array, 0, size - 1);
    }
    auto end = std::chrono::high_resolution_clock::now();

    printArray(array, size, "Sorted Array");

    std::chrono::duration<double> duration = end - start;
    std::cout << "Parallel Merge Sort Time: " << duration.count() << " seconds" << std::endl;

    if (isSorted(array, size)) {
        std::cout << "Successfully sorted!" << std::endl;
    } else {
        std::cout << "Sorting failed!" << std::endl;
    }

    delete[] array;
    return 0;
}
