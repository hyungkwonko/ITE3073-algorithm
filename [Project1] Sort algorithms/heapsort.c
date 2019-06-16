
// introduction to algorithm class assignment 1
// Heap sort
// Name: HyungKwon Ko
// Student #: 2014018940

/* My Implementation */

#include <stdio.h>

// re-declare at first to avoid the warning sign
void heapify(int heap[], int *node, int ithValue, int m);
int sort(int heap[], int *node);

void heapSort(int* arr, int size) {
    
    int i, j;
    int max = 0;
    int node = 0;
    int temp;
    
    // Finding max value. It will be placed at arr[0].
    // I will exclude this max value, arr[0], for making heap since it makes all calculations difficult.
    for(i=0; i<size; i++) {
        if(max < arr[i]) {
            max = arr[i];
            j = i; // index of the max value
        }  
    }
    
    temp = arr[0];
    arr[0] = max; // arr[0] is now the maximum value among the array
    arr[j] = temp; // the earlier arr[0] is now in arr[j]. they are swapped

    // make binary max heap
    for(i=1; i<size; i++) {
        heapify(arr, &node, arr[i], max);
    }
    
    //// print the heap to check if it's working well(commented out)
    //for(i=0; i<size; i++) {
    //    printf("arr[%d]: %d\n", i, arr[i]);
    //}

    // sort them out in reverse order
    for(i=node; i>=1; i--) {
        arr[i] = sort(arr, &node);
    }
    // move all elements by one index left and put max value at the last
    for(i=0; i<size-1; i++) {
        arr[i] = arr[i+1];
    }
    arr[size-1] = max;

}

void heapify(int heap[], int *node, int ithValue, int m) {
    
    int n;
    ++(*node);
    heap[*node] = ithValue; // insert ith value to the last heap

    heap[0] = m; // fix it as maximum value to make the calculation easier

    n = *node;
    
    // move the inserted heap upward as long as it satisfies the condition
    while(heap[n/2] < ithValue) {
        heap[n] = heap[n/2]; // drag the parental value down to the child's heap if it's smaller than the last heap(swap)
        n /= 2; // do it recursively
    }

    heap[n] = ithValue; // place the inserted value to the position where the while conditional statement ends
}

int sort(int heap[], int *node) {

    int n;
    int parent = 1; // first heap
    int child = 2; // second heap
    int tempRoot; // temporal place to store given value

    int popValue = heap[1]; // this value will be popped out from the array

    heap[1] = heap[*node]; // the last heap is now on the top level
    --(*node); // since heap[1] will be removed, node size decreases by 1
    tempRoot = heap[1]; // we copy this to temporal place since we have to move downward and will be replaced by the value of one of its child nodes

    n = *node; // n is the # of nodes in tree
    while(parent <= n/2) { // run until reach the second to last deep level
        child = parent << 1; // move one bit left e.g.) 2->4, 4->8..
        if(child < n && heap[child] < heap[child+1]) // if the value of the right child heap is bigger than left's then add 1
            child++;
        if(tempRoot > heap[child]) break; // stop if the heap is stable(nothing to move)
        heap[parent] = heap[child]; // child heap move to parent heap
        parent = child; // remember the index
    }

    heap[parent] = tempRoot; // input the value to the suitable(found) place

    return popValue; // return the value that we assigned at the very beginning of this class
    // This process will be recursively done 'size-1' times
}
