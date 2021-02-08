#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//write function to file...??

void initBoard(char **board, int col)
{
    int i;
    for (i = 0; i < col; i++)
    {
        board[i] = malloc(col * sizeof(char));
    }
}

void printBoard(char **board, int row, int col, int currGen)
{
    int i, j;
    printf("Generation: %d\n", currGen);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void checkNeighbors(char **board, int i, int j, int neigh)
{
    //check top
    if (i > 0 && board[i - 1][j] == '*')
    {
        neigh++;
    }
    //check left
    if (j > 0 && board[i][j - 1] == '*')
    {
        neigh++;
    }
    //check right
    if (j < 9 && board[i][j + 1] == '*')
    {
        neigh++;
    }
    //check bottom
    if (i < 9 && board[i + 1][j] == '*')
    {
        neigh++;
    }
    //check left upper diagonal
    if ((i > 0 && j > 0) && board[i - 1][j - 1] == '*')
    {
        neigh++;
    }
    //check right upper diagonal
    if ((i > 0 && j < 9) && board[i - 1][j + 1] == '*')
    {
        neigh++;
    }
    //check left lower digonal
    if ((i < 9 && j > 0) && board[i + 1][j - 1] == '*')
    {
        neigh++;
    }
    //check right lower diagonal
    if ((i < 9 && j < 9) && board[i + 1][j + 1] == '*')
    {
        neigh++;
    }
    printf("neighbors in cycle: %d\n", neigh);
}
void evolve(char **board, int row, int col, int currGen)
{
    printBoard(board, row, col, currGen);
    int i, j, neigh;

    char **temp = malloc(row * sizeof(char *));
    initBoard(temp, col);

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            neigh = 0;
            checkNeighbors(board, i, j, neigh);
            if (board[i][j] == '-')
            {
                if (neigh == 3)
                {
                    temp[i][j] = '*';
                }
                else
                {
                    temp[i][j] = board[i][j];
                }
            }
            else if (board[i][j] == '*')
            {
                if (neigh < 2 || neigh < 3)
                {
                    board[i][j] = '-';
                }
                else
                {
                    temp[i][j] = board[i][j];
                }
            }
        }
    }
    board = temp;
    free(board);
}

void loadLife(FILE *fptr, int row, int col, int gen)
{
    /* Load the game of life with the number of columns, then
     * output the game into the struct called board
     */
    //printf("row: %d, col: %d, gen: %d\n", row, col, gen);

    char **board = malloc(row * sizeof(char *));
    initBoard(board, col);

    char line[col]; //max linelength
    int currRow = 0;
    while (fgets(line, sizeof(line), fptr))
    {
        int i;
        for (i = 0; i < col; i++)
        {
            if (line[i] == '*')
            {
                board[currRow][i] = '*';
            }
            else
            {
                board[currRow][i] = '-';
            }
        }
        currRow++;
    }
    // continue filling rows
    while (currRow < row)
    {
        int i;
        for (i = 0; i < col; i++)
        {
            board[currRow][i] = '-';
        }
        currRow++;
    }
    /*
    for (int currGen = 0; currGen < gen; currGen++)
    {
        evolve(board, row, col, currGen);
    }
*/
    printBoard(board, row, col, 0);
    fclose(fptr);
    free(board);
}

/*
 * The checkFile function will take in a file descriptor
 * and a char pointer and check to see if that file exists.
 * If the file does exist, it will open that file
 */
void checkFile(FILE *fptr)
{
    if (fptr == NULL)
    {
        printf("life: error, cannot read file\n");
        exit(0);
    }
}
/*
 * This will convert a single integer
 * that we need for the function
 */
void convSingleInt(char *arg, int *hold)
{
    char c[512];
    strcpy(c, arg);
    char *num = c;
    int temp = atoi(num);
    *hold = temp;
}

/* decision fork function will assign correct values
 * and take the correct path to complete task
 */
void decisionFork(int argc, char *argv[])
{
    int row = 10, col = 10, gen = 10;
    FILE *fptr;
    if (argc == 1)
    {
        fptr = fopen("life.txt", "r");
        loadLife(fptr, row, col, gen);
    }
    else if (argc == 3)
    {
        fptr = fopen("life.txt", "r");
        convSingleInt(argv[1], &row);
        convSingleInt(argv[2], &col);
        loadLife(fptr, row, col, gen);
    }
    else if (argc == 4)
    {
        fptr = fopen(argv[3], "r");
        checkFile(fptr);
        convSingleInt(argv[1], &row);
        convSingleInt(argv[2], &col);
        loadLife(fptr, row, col, gen);
    }
    else if (argc == 5)
    {
        fptr = fopen(argv[3], "r");
        checkFile(fptr);
        convSingleInt(argv[1], &row);
        convSingleInt(argv[2], &row);
        convSingleInt(argv[4], &gen);
        loadLife(fptr, row, col, gen);
    }
    else
    {
        for (int i = 0; i < argc; i++)
        {
            printf("%d input: %s\n", i, argv[i]);
        }

        printf("life: error in input given in command line\n");
        exit(1);
    }
}
int main(int argc, char *argv[])
{
    /*
     * Here we will split and determine what happens.
     * rows, columns, filename, and generations will be defaulted
     * to original values.
     */
    decisionFork(argc, argv);
}
