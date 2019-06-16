
// Introduction to algorithm class assignment 2
// Countsort code
// Name: Hyung-Kwon Ko
// Student #: 2014018940

/* My Implementation */

// FYI, in this code I did not take the stable state of the output into account to make it faster than quick sort algorithm.

#include <stdio.h>
#include <stdlib.h>

int tableSize(int* arr, int size) // this will catch the max value and will use it making the occurrence array
{
    int i = 0;
    int max = 0;

    for(i=0; i < size; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max; // return max value
}

void countSort(int* arr, int size)
{
    int i = 0;
    int maxValue = tableSize(arr, size);
    int* occurTable = (int*) calloc(maxValue, sizeof(int)); // i used calloc for dynamic allocation and its initial condition to 0s at ease

    for(i=0; i<size; i++) {
        occurTable[arr[i]]++; // make the occurrence array
    }

    int j = 0;
    int index = 0;
    
    for(j=0; j<=maxValue; j++) { // double conditional loop
        while(occurTable[j] > 0) { // do while the occurrence element has positive value
            arr[index] = j;
            occurTable[j]--; // since we used one, subtract one
            index++; // index move one to the right position

            if(index > size) { // if the index>size, escape the while loop
                break;
            }
        }
    }
}
