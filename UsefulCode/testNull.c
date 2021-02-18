#include <stdio.h>
#include <stdlib.h>

int main(){
    
    char * test = "-i";
    char * test2 = "-i";
    char * test3 = "-in";

    char * testArr[] = { test, test2, test3 };

    char * grabber[3];

    for (int i =0; i < 3; i++){
        grabber[i] = testArr[i];
    }
    for(int i = 0; i < 3; i++){
        printf("%s bloop\n", grabber[i]);
    }

    if ( testArr[0] == testArr[1] ){
        printf("yes\n");
    }

    for ( int i = 0; i < 3; i++ ){
        printf("testing %s\n", testArr[i]);
        for (int j = 0; testArr[i][j] != '\0'; j++){
            if(testArr[i][j] == 'i'){
                if (testArr[i][j+1] == '\0'){
                    printf("word: %s it works\n", testArr[i]);
                }
            }
        }
    }
    return 0;
}
