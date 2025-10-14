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

void quickSort_parallel(int *array, int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);

        // Create parallel tasks for the recursive calls
#pragma omp task
        {
            quickSort_parallel(array, low, pi - 1);
        }
#pragma omp task
        {
            quickSort_parallel(array, pi + 1, high);
        }
    }
}

int main(int argc, char **argv) {
    int size, seed;

    // Per project requirements, only use command-line arguments [cite: 22]
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " [amount of random nums to generate] [seed value for rand]" << std::endl;
        return -1;
    }

    size = std::stoi(argv[1]);
    seed = std::stoi(argv[2]);

    int *array = randNumArray(size, seed);

    auto start = std::chrono::high_resolution_clock::now();

    // Create a parallel region for the tasks to run in
#pragma omp parallel
    {
        // Have a single thread start the initial sort call
#pragma omp single nowait
        {
            quickSort_parallel(array, 0, size - 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    // The executable must print the running time [cite: 49]
    std::cout << "Parallel Quick Sort Time: " << duration.count() << " seconds" << std::endl;

    // Optional: You can add verification if you want
    // if (!isSorted(array, size)) {
    //     std::cerr << "Sorting failed!" << std::endl;
    // }

    delete[] array;
    return 0;
}
