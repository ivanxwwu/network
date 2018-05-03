#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <strings.h>
#include <sys/wait.h>
#include <sys/un.h>
#include <signal.h>
#include <iostream>
using namespace std;
void f(int arr[10]){
    cout << sizeof(arr) << endl;
}


int main (void) {
    int arr[10] = {0};
    cout << sizeof(arr) << endl;
    f(arr);

}


