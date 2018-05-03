//
// Created by root on 3/11/17.
//

#include <stdio.h>
#include <netinet/in.h>

void qsort(int *a, int left, int right)
{
    if(left >= right)  return;
    int i = left;
    int j = right;
    int key = a[left];

    while(i < j)
    {
        while(i < j && key <= a[j])j--;
        a[i] = a[j];
        while(i < j && key >= a[i]) i++;
        a[j] = a[i];
    }

    a[i] = key;
    qsort(a, left, i - 1);
    qsort(a, i + 1, right);
}

int main(){
    int arr[] = {9,8,7,6,45,5,4,3,2,1,2};
    //int arr[] = {2,3,1};
    int i=0;
    qsort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
    for(i = 0; i<sizeof(arr)/sizeof(arr[0]); i++){
        printf("%d ", arr[i]);
    }
//    struct sockaddr_in in;
//    int fd = socket(PF_INET, SOCK_STREAM, 0);
//    in.sin_addr =
}
