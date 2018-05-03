//
// Created by root on 3/11/17.
//

#include <stdio.h>

void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

void selectSort(int arr[], int size){
    int i, j, smallest, smallestIndex;
    for(i=0; i<size; i++){
        smallest = arr[i];
        smallestIndex=i;
        for(j=i; j<size; j++){
            if(arr[j] <= smallest) {
                smallest = arr[j];
                smallestIndex = j;
            }
        }
        swap(&arr[smallestIndex], &arr[i]);
    }
}


int main(){
    int arr[] = {9,8,7,6,45,5,4,3,2,1,2};
    int i=0;
    selectSort(arr, sizeof(arr)/sizeof(arr[0]));
    for(i = 0; i<sizeof(arr)/sizeof(arr[0]); i++){
        printf("%d ", arr[i]);
    }


}

