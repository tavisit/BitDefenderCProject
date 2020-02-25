#pragma once
#include "common.h"
#include "ccvector.h"
#include "string.h"

/* The main function that implements the swapping of values
  first  --> first number to be swapped,
  second  --> second number to be swapped */
void swapValues(int* first, int* second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}
/* The main function that implements the partition
 Vector[] --> vector to be sorted,
  low  --> Starting index,
  high  --> Ending index */
int partition(int *Vector, int low, int high)
{
    int pivot = Vector[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot 
        if (Vector[j] < pivot)
        {
            i++;    // increment index of smaller element 
            swapValues(&Vector[i], &Vector[j]);
        }
    }
    swapValues(&Vector[i + 1], &Vector[high]);
    return (i + 1);
}

/* The main function that implements the sort
 Vector[] --> vector to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void sortCCVector(int *Vector, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, Vector[p] is now
           at right place */
        int pi = partition(Vector, low, high);

        // Separately sort elements before 
        // partition and after partition 
        sortCCVector(Vector, low, pi - 1);
        sortCCVector(Vector, pi + 1, high);
    }
}
/* The main function that implements the reversing of the vector
 Vector[] --> vector to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void reverseVector(int *Vector,int low, int high) {
    high--;
    while (low < high)
    {
        swapValues(&Vector[low], &Vector[high]);
        low++;
        high--;
    }

}
/*Verify if the Index and Count variables are valid

*/
int indexValid(int Index, int Count) {
    if (Count < Index) return 0;
    if (Index < 0) return 0;
    return 1;

}

