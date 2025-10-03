#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>

extern const int MAX_ELEMENTS;
extern const int MAX_RANDOM_VALUE;

int *randNumArray(int size, int seed);

bool isSorted(const int *array, int size);

void printArray(const int *array, int size, const char *label);

int getUserInput();

#endif
