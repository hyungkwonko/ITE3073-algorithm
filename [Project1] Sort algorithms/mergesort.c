
// Introduction to algorithm class assignment 1
// Mergesort code
// Name: Hyung-Kwon Ko
// Student #: 2014018940


/* My Implementation */

#include<stdio.h>
#include<stdlib.h> // to use malloc function

void merge(int *arr, int size1, int size2);

void mergeSort(int* arr, int size) {
    
    int i;
    
    if(size == 1) return; // stop condition for the recursion(when there is only one element in the given array)
    
    // Since merge algorithm is based on two main parts 'divide' & 'conquer', I will apply them one by one.
    int size1 = size / 2; // will be the size of first array
    int size2 = size - size1; // 2nd array's size

    //printf("\n");
    ////print elements in the array1 
    //for(i=0; i<size1; i++) { 
    //    printf("arr1 elements: %d \n", arr[i]);
    //}
    ////print elements in the array2 
    //for(i=size1; i<size1+size2; i++) { 
    //    printf("arr2 elements: %d \n", arr[i]);
    //}
    //// checking size to see if it's working well
    //printf("size: %d\n", size);
    //printf("size1: %d\n", size1);
    //printf("size2: %d\n\n", size2);
    
    // divide using recursion so as to save memory
    mergeSort(arr, size1);
    mergeSort(arr+size1, size2);
    
    // Now start conquering
    merge(arr, size1, size2);
    //printf("merged!\n"); // to help noticing if it's merged well
}

void merge(int *arr, int size1, int size2) {
    
    int *temp = (int*)malloc(sizeof(int)*(size1+size2));
    int ptr1 = 0; // abbreviation of array one pointer
    int ptr2 = 0;

    while(ptr1 < size1 && ptr2 < size2) {
        if(arr[ptr1] < arr[size1 + ptr2]) {
            temp[ptr1 + ptr2] = arr[ptr1]; 
            ptr1++; // increase one level since this element has poped out
        }
        if(arr[size1 + ptr2] <= arr[ptr1]) {
            temp[ptr1 + ptr2] = arr[size1 + ptr2];
            ptr2++; // the same process as above
        }
    }
    
    // if there is left elements in the first array, we will move them in sequence
    while(ptr1 < size1) {
        temp[ptr1 + ptr2] = arr[ptr1];
        ptr1++;
    }
    // likewise if there is left elements in the second array, we will move them in sequence
    while(ptr2 < size2) {
        temp[ptr1 + ptr2] = arr[size1 + ptr2];
        ptr2++;
    }


    //// Halfway check for merging operation(now commented out)
    //printf("\n");
    //printf("temporarily sorted array!\n");
    for(int i=0; i<size1+size2; i++) {
    //    printf("temp%d: %d\n", i, temp[i]);
        arr[i] = temp[i]; // allocate temp values to the output arary
    }
    free(temp);
}

