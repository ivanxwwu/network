#include <stdio.h>
#include <sys/mman.h>

char* a;



int main()
{
    a = 1;
    printf("%d\n", (12<<1)-1);
}