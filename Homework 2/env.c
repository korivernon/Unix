///------------------------------------------------///
///   Class:          <UNIX SYSTEM PROGRAMMING>    ///
///   Description:    <ENV COMMAND>                ///
///   Author:         <Kori Vernon>                ///
///   Date:           <02/23/2021>                 ///
///------------------------------------------------///
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/*
 * Checks to see if the input is inside of the environment array.
 * If the input does not exist, a -1 is returned, and if it does exist
 * then index is returned so that it can be modified in a parent function.
 */
int checkEnv(char **envArr, char *line)
{
    int varLen = (strchr(line, '=') - line), i;
    for (i = 0; envArr[i] != NULL; i++)
    {
        if (strncmp(envArr[i], line, varLen) == 0)
        {
            return i;
        }
    }
    return -1;
}

/*
 * Ouputs the contents of the environ variable.
 */
void printEnv()
{
    for (int i = 0; (environ[i] != NULL); i++)
    {
        puts(environ[i]);
    }
}

/*
 * This function allocates the enviornment array on the heap
 * to be used in outside functions. 
 */
char **envalloc(int numLines, int envLen)
{
    int i;
    char **newEnv = malloc((envLen + numLines + 1) * sizeof(char *)); //allocate needed lines
    for (i = 0; i < envLen; i++)
    {
        newEnv[i] = environ[i];
    }
    return newEnv;
}
/*
 * Put the line in the env array.
 */
void envPutLine(char *argv[], char *line, char **newEnv, int i)
{
    int existLoc = checkEnv(newEnv, line), store = -1; // check the key value pair to see if it exists
    if (existLoc != -1) //if input exists inside of env array
    {
        store = i; //set storage == i
        i = existLoc; //assign i to match existing location
    }
    newEnv[i] = line; //place the line inside of new environment
}
/*
 * This function creates the environment and places the Key Value Pairs
 * where they belong.
 */
char **makeEnv(char *argv[], int flag, int numLines, int envLen)
{
    int arg_i = 1 - flag;
    char **newEnv = NULL, *line = NULL;
    if (flag == 0)
    {
        newEnv = envalloc(numLines, envLen);
    }
    else
    {
        newEnv = malloc((numLines + 1) * sizeof(char *)); //allocate only enough 
        envLen = 0;
    }
    for (int i = envLen; i < envLen + numLines; i++)
    {
        line = argv[arg_i];
        if (line == NULL)
        {
            return newEnv;
        }
        //put a line in into env
        envPutLine(argv, line, newEnv, i);
        
        arg_i++;
    }
    return newEnv;
}
/*
 * This function will find the index of the toggle if it exists. 
 * If the toggle doesn't exist, the answer will be -1. Otherwise, 
 * it will be the index + 1 of the last "-i".
 */
int findToggle(char *argv[], int argc)
{
    int flag = 0, i, notSeen = 0;
    for (i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "-i") == 0) && notSeen == 0)
        {
            flag--;
        } else {
            break; // to account for improper behavior; ./env -i -i hi=no -i
        }
    }
    return flag;
}
/*
 * Call the command if it exists using execvp. If it does not exist
 * then exit the process. 
 */
void callCommand(char *argv[], int argc, int start, int numLines)
{
    int count = start + numLines;
    if (count < argc)
    {
        if (execvp(argv[count], (argv + count)) == -1) // call the execvp with passed in arguments if it exists
        {
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    int flag, start, numLines =  0, i, sz = 0;
    ;
    if (argc == 1)
    {
        printEnv();
        return 0;
    }
    flag = findToggle(argv, argc); //find last LEGAL occurence
    start = 1 - flag;
    for (i = start; argv[i] != NULL; i++) // counts the additional number of lines that need to be parsed
    {
        if (strchr(argv[i], '=') != NULL)
        {
            numLines++;
        }
    }
    if (numLines) // find the size of environ
    {
        for (i = 0; environ[i] != NULL; i++)
        {
            sz++;
        }
        //free(environ); ??? is this not allowed before reassignment ?
        environ = makeEnv(argv, flag, numLines, sz); //create the new environment
    }
    callCommand(argv, argc, numLines, start);
    printEnv();
    return 0;
}