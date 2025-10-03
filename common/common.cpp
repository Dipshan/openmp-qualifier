#include "common.h"

const int MAX_ELEMENTS = 50000;
const int MAX_RANDOM_VALUE = 50000;

int *randNumArray(const int size, const int seed) {
    srand(seed);
    int *array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = (std::rand() % MAX_RANDOM_VALUE) + 1; // Numbers between 1-50,000
    }
    return array;
}

bool isSorted(const int *array, const int size) {
    for (int i = 0; i < size - 1; i++) {
        if (array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

void printArray(const int *array, const int size, const char *label) {
    std::cout << label << " [" << size << " elements]: ";
    if (size <= 10) {
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
    } else {
        for (int i = 0; i < 5; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << "... ";
        for (int i = size - 5; i < size; i++) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << std::endl;
}

int getUserInput() {
    int size;
    while (true) {
        std::cout << "Enter number of elements to sort (1-" << MAX_ELEMENTS << "): ";
        std::cin >> size;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Please enter a number between 1 and " << MAX_ELEMENTS << "." << std::endl;
        } else if (size < 1) {
            std::cout << "Size must be at least 1 element." << std::endl;
        } else if (size > MAX_ELEMENTS) {
            std::cout << "Size cannot exceed " << MAX_ELEMENTS << " elements." << std::endl;
        } else {
            break;
        }
    }
    return size;
}
