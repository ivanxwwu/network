//
// Created by root on 17-8-20.
//

#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

void maxHeapify(int array[], int i, int heap_size);
void buildMaxHeap(int array[],int len);
void heapsort(int array[],int len);

void swap(int *x, int *y)
{

    int temp;
    temp=*x;
    *x=*y;
    *y=temp;
}

void maxHeapify(int array[], int i, int heap_size)
{
    int largest;
    int _left=2*i;
    int _right=2*i+1;

    if (_left<=heap_size && array[_left]>array[i])
    {
        largest=_left;
    }
    else
        largest=i;

    if (_right<=heap_size && array[_right]>array[largest])
    {
        largest=_right;
    }

    if (largest!=i)
    {
        swap(&array[largest],&array[i]);
        maxHeapify(array,largest,heap_size);
    }
}

void buildMaxHeap(int array[],int len)
{

    int heap_size=len;
    int i = len/2;
    for (; i>=1; i--)
    {
        maxHeapify(array,i,heap_size);
    }
}

void heapsort(int array[],int len)
{
    int heap_size=len;
    buildMaxHeap(array,len);
    int i = len;
    for (; i>=2; i--)
    {
        swap(&array[1],&array[i]);
        heap_size--;
        maxHeapify(array,1,heap_size);
    }
}


int main(){
    int array[]={0,14,10,8,7,9,3,2,4,1};
    int len=9;
    heapsort(array,len);
}