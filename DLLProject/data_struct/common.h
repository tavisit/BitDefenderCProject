#pragma once

#include "stdlib.h"
#include "ccvector.h"

#define CC_UNREFERENCED_PARAMETER(X) X

typedef enum booleanType { false, true } boolean;

// Set of Functions to perform quick sort
int partition(int *Vector, int low, int high);
void swapValues(int *first, int *second);
void sortCCVector(int *Vector, int min, int max);

// Function to reverse the Vector
void reverseVector(int *Vector,int low, int high);

boolean isNumber(char *string);

// Verify if the index input is valid
int indexValid(int Index, int Count);