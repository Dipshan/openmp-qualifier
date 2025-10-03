#ifndef SORT_H
#define SORT_H

// Bubble sort implementations
void bubbleSortSerial(int* array, int size);
void bubbleSortParallel(int* array, int size);

// Quick sort implementations
void quickSortSerial(int* array, int low, int high);
void quickSortParallel(int* array, int low, int high);

// Merge sort implementations
void mergeSortSerial(int* array, int left, int right);
void mergeSortParallel(int* array, int left, int right);

// STL sort reference
void stlSort(int* array, int size);

// Helper functions
int partition(int* array, int low, int high);
void merge(int* array, int left, int mid, int right);

#endif