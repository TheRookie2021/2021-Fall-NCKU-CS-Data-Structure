#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    bool a=true;
    int b=1;
    printf("size bool: %d, size int: %d\n",sizeof(a) ,sizeof(b));
    //ans: bool= 1 byte, int= 4 bytes
    return 0;
}