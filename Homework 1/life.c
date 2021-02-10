///------------------------------------------------///
///   Class:          <UNIX SYSTEM PROGRAMMING>    ///
///   Description:    <Game of Life>               ///
///   Author:         <Kori Vernon>                ///
///   Date:           <02/09/2021>                 ///
///------------------------------------------------///
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * The initBoard function will take in a char** and an amoount
 * of column and create a two dimensional character array. 
 */
void initBoard(char **board, int col)
{
    int i;
    for (i = 0; i < col; i++)
    {
        board[i] = malloc(col * sizeof(char));
    }
}
/*
 * The printBoard function will take in the row, col, game board,
 * along with the current generation number and will print out
 * the contents to the command line. 
 */
void printBoard(char **board, int row, int col, int currGen)
{
    int i, j;
    printf("Generation %d:\n", currGen);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }

    printf("================================\n");
}
/* This function prints the board to the file, which upon further
 * analysis... doesn't actually need to be created
 */
void printBoardToFile(FILE *outfile, char **board, int row, int col, int currGen)
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            fputc(board[i][j], outfile);
        }
        fputc('\n', outfile);
    }
}
void checkNeighbors(char **board, int x, int y, int neigh, int maxRow, int maxCol)
{
    //check top
    if (x > 0 && board[x - 1][y] == '*')
    {
        neigh++;
    }
    //check left
    if (y > 0 && board[x][y - 1] == '*')
    {
        neigh++;
    }
    //check right
    if (y < maxCol && board[x][y + 1] == '*')
    {
        neigh++;
    }
    //check bottom
    if (x < maxRow && board[x + 1][y] == '*')
    {
        neigh++;
    }
    //check left upper diagonal
    if ((x > 0 && y > 0) && board[x - 1][y - 1] == '*')
    {
        neigh++;
    }
    //check right upper diagonal
    if ((x > 0 && y < maxCol) && board[x - 1][y + 1] == '*')
    {
        neigh++;
    }
    //check left lower digonal
    if ((x < maxRow && y > 0) && board[x + 1][y - 1] == '*')
    {
        neigh++;
    }
    //check right lower diagonal
    if ((x < maxRow && y < maxCol) && board[x + 1][y + 1] == '*')
    {
        neigh++;
    }
    //printf("neighbors in cycle: %d\n", neigh);
}

void evolve(char **board, int row, int col, int currGen)
{
    printBoard(board, row, col, currGen);
    int i, j, neigh;
    char **nextGen = malloc(row * sizeof(char *));
    initBoard(nextGen, col);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            neigh = 0;
            checkNeighbors(board, i, j, neigh, row, col);
            if (board[i][j] == '-')
            {
                if (neigh == 3)
                {
                    nextGen[i][j] = '*';
                }
                else
                {
                    nextGen[i][j] = board[i][j];
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
                    nextGen[i][j] = board[i][j];
                }
            }
        }
    }
    board = nextGen;
    free(nextGen);
}
/* Load the game of life with the number of rows and columns
 * then run game.
 */
void loadLife(FILE *fptr, int row, int col, int gen)
{
    char **board = malloc(row * sizeof(char *)); //initialize the board
    initBoard(board, col);
    char line[col];     // prepare to read lines in to the maximum column
    int currRow = 0, i; // initialize integer variables
    while (fgets(line, sizeof(line), fptr))
    { 
        for (i = 0; i < col; i++)
        {
            if (line[i] > col){printf("(%d, %d): %c\n", currRow, i,line[i] );}
            if (line[i] == '*') //this may not exist
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
    // continue filling rows if the file ends prematurely
    while (currRow < row)
    {
        int i;
        for (i = 0; i < col; i++)
        {
            board[currRow][i] = '-';
        }
        currRow++;
    }

    for (int currGen = 0; currGen < gen; currGen++)
    {
        evolve(board, row, col, currGen);
    }

    fclose(fptr); // close used files
    free(board);  // free board space
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
        exit(1); // 0 implies everything went fine
    }
}
/*
 * This will convert a single integer
 * that we need for the function
 */
void convSingleInt(char *arg, int *hold)
{
    long int tempLong = strtol(arg, NULL, 10);
    *hold = tempLong;
}
/* The decision fork function will assign correct values
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
/*
 * Here we will split and determine what happens.
 * rows, columns, filename, and generations will be defaulted
 * to original values.
 */
int main(int argc, char *argv[])
{
    decisionFork(argc, argv);
}
