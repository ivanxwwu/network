//
// Created by root on 3/11/17.
//

//
// Created by root on 3/11/17.
//

#include <stdio.h>

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

void swapSort(int arr[], int size){
    for(i=0; i<size; i++){
        for(j=0; j<size-i; j++){
            if(arr[i] < arr[j]) {
                swap(&arr[j], &arr[i]);
            }
        }
        swap(&arr[smallestIndex], &arr[i]);
    }
}


int main(){
    int arr[] = {9,8,7,6,45,5,4,3,2,1,2};
    int i=0;
    swapSort(arr, sizeof(arr)/sizeof(arr[0]));
    for(i = 0; i<sizeof(arr)/sizeof(arr[0]); i++){
        printf("%d ", arr[i]);
    }


}

