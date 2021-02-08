#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){

    int row = atoi(argv[1]);
    int col = atoi(argv[2]);

    typedef char char2D[1][1];

    char2D *ptr;

    ptr = calloc( row*col, sizeof(char) );

    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            (*ptr)[i][j] = '-';
        }
    }

    for (int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%c", (*ptr)[i][j]);
        }
        printf("\n");
    }

    free(ptr);
    return 0;
}
