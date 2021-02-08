#include <stdio.h>
#include <stdlib.h>

void printArr(char ** arr, int row, int col){

    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int row = 2, col = 2;
    char ** arr = malloc(row * sizeof(char *));

    int i, j;

    for (i = 0; i < col; i++){
        arr[i] = malloc(col * sizeof(char));
    }

    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            arr[i][j] = '-';
        }
    }

    printArr(arr, row, col);
/*
    for (i = 0; i < row; i++){
        for (j = 0; j < col; j++){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
*/
    free(arr);
    return 0;

}
