
// Introduction to algorithm class assignment 2
// Quicksort code
// Name: Hyung-Kwon Ko
// Student #: 2014018940

/* My implementation */

void quick(int* arr, int left, int right)
{
    int pivot, left_fix, right_fix;

    left_fix = left;
    right_fix = right;
    pivot = arr[left]; // I will use the left most element as a pivot value
    while(left < right) { // recursively run as far as the size of the divided array >= 2
        while((arr[right] >= pivot) && (left < right)) { // find the index that has smaller value than pivot
            right--; // move to left one by one if its value is bigger than pivot value
        }
        if(left != right) { // it will not work it left = right. if left = right this place is for the pivot value and will escape the while loop
            arr[left] = arr[right]; // replace the first element to the one we found that is smaller than pivot value
            left++; // move one step to the right
        }
        while((arr[left] <= pivot) && (left < right)) { 
            left++; // if the order has no problem, keep moving to the right by adding index
        }
        if(left != right) { // the same as above
            arr[right] = arr[left];
            right--;
        }
    }
    arr[left] = pivot; // put pivot value to where it should be(it is the standard that divides two arrays)
    pivot = left; // assign the pivot value's index
    left = left_fix; // turn it back to the original state like above
    right = right_fix; // the same work
    if(left < pivot) { // do it recursively until there is only one element in the divided array
        quick(arr, left, pivot-1);
    }
    if(right > pivot) {
        quick(arr, pivot+1, right);
    }
}

void quickSort(int* arr, int size) 
{
    quick(arr, 0, size-1); // since 0 to size-1, it has [size] number of elements
}
