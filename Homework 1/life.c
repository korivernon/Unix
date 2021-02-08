#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void loadLife(FILE *fptr, int row, int col, int gen){
    /* Load the game of life with the number of columns, then
     * output the game into the struct called board
     */
    printf("row: %d, col: %d, gen: %d\n", row, col, gen);

    fclose(fptr);
}

/*
 * The checkFile function will take in a file descriptor
 * and a char pointer and check to see if that file exists.
 * If the file does exist, it will open that file
 */
void checkFile(FILE *fptr){
    if (fptr == NULL){
        printf("life: error, cannot read file\n");
        exit(0);
    }
}
/*
 * This will convert a single integer
 * that we need for the function
 */
void convSingleInt(char * arg, int * hold){
    char c[512];
    strcpy(c, arg);
    char *num = c;
    int temp = atoi(num);
    *hold = temp;
}

/* decision fork function will assign correct values
 * and take the correct path to complete task
 */
void decisionFork(int argc, char *argv[]){
    int row = 10, col = 10, gen = 10;
    FILE *fptr;
    if (argc == 1){
        fptr = fopen("life.txt", "r");
        loadLife(fptr,  row, col, gen);
    }
    else if (argc == 3){
        fptr = fopen("life.txt", "r");
        convSingleInt(argv[1], &row);
        convSingleInt(argv[2], &col);
        loadLife(fptr, row, col, gen);
    }
    else if (argc == 4){
        fptr = fopen(argv[3], "r");
        checkFile(fptr);
        convSingleInt(argv[1], &row);
        convSingleInt(argv[2], &col);
        loadLife(fptr, row, col, gen);
    }
    else if (argc == 5){
        fptr = fopen(argv[3], "r");
        checkFile(fptr);
        convSingleInt(argv[1], &row);
        convSingleInt(argv[2], &row);
        convSingleInt(argv[4], &gen);
        loadLife(fptr,  row, col, gen);
    }
    else {
        for (int i = 0; i < argc; i++){
            printf("%d input: %s", i, argv[i]);
        }

        printf("life: error in input given in command line\n");
        exit(1);
    }
}
int main(int argc, char *argv[]){
    /*
     * Here we will split and determine what happens.
     * rows, columns, filename, and generations will be defaulted
     * to original values.
     */
    decisionFork(argc, argv);
}
