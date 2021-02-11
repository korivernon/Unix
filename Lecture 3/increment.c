/*

Incrementing

*/
#include <stdio.h>

int inc() {
    static int value = 17;
    
    return value++;
}

int main(){
    
    for (int i = 0; i < 10; ++i){
        printf("%d", inc());
    }
    printf("\n");    
}