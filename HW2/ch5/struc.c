
#include <stdio.h>
#include <string.h>

typedef struct{
    int key;
    int height;

}element;

int main(){

    element a;
    a.key=1;
    printf("%d ",a.key);
    
    printf("%d ",a.height);
    return 0;
}