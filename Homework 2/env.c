#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/*
 * This function will determine the length of the environment
 * to be used for environment allocation. 
 */
int envLen()
{
    int i, sz = 0;
    for (i = 0; environ[i] != NULL; i++)
    {
        sz++;
    }
    return sz;
};

/*
 * This function validifies arguments by counting the 
 * ENV_VAR=STATUS pairs passed into the command line
 * function call. 
 */
int validArgs(char *argv[], int start)
{
    int i, validArg = 0;
    for (i = start; argv[i] != NULL; i++)
    {
        if (strchr(argv[i], '=') != NULL)
        {
            validArg++;
        }
    }
    return validArg;
}

/*
 * Checks to see if the input is inside of the environment array.
 * If the input does not exist, a -1 is returned, and if it does exist
 * then index is returned so that it can be modified in a parent function.
 */
int checkEnv(char **envArr, char *line)
{
    int varLen, i;
    for (i = 0; envArr[i] != NULL; i++)
    {
        varLen = (strchr(line, '=') - line);
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
    char **newEnv = malloc((envLen + numLines + 1) * sizeof(char *));
    for (i = 0; i < envLen; i++)
    {
        newEnv[i] = malloc((strlen(environ[i]) + 1) * sizeof(char));
        newEnv[i] = environ[i];
    }
    return newEnv;
}
/*
 * Put the line in the env array.
 */
void envPutLine(char *argv[], char *line, char **newEnv, int *i, int *key, int *store)
{
    *key = checkEnv(newEnv, line);
    if (*key != -1)
    {
        *store = *i;
        *i = *key;
    }
    newEnv[*i] = malloc((strlen(line) + 1) * sizeof(char));
    newEnv[*i] = line;
    if (*key != -1)
    {
        if (*store == -1)
        {
            exit(1);
        }
        *i = *store - 1;
    }
}
/*
 * This function creates the environment and places the Key Value Pairs
 * where they belong.
 */
char **makeEnv(char *argv[], int flag, int numLines, int envLen)
{
    int arg_i = 1 - flag, key, store = -1;
    char **newEnv = NULL, *line = NULL;
    if (flag == 0)
    {
        newEnv = envalloc(numLines, envLen);
    }
    else
    {
        newEnv = malloc((numLines + 1) * sizeof(char *));
        envLen = 0;
    }
    for (int i = envLen; i < envLen + numLines; i++)
    {
        line = (char *)argv[arg_i];
        if (line == NULL)
        {
            return newEnv;
        }
        //put a line in into env
        envPutLine(argv, line, newEnv, &i, &key, &store);
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
    int flag = 0;
    for (int i = 1; i < argc; i++)
    {
        if ((strncmp(argv[i], "-i", 2) == 0))
        {
            flag--;
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
    if ((start + numLines) < argc)
    {
        if (execvp(argv[start + numLines], (argv + start + numLines)) == -1)
        {
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    int flag, start, numLines;
    if (argc == 1)
    {
        printEnv();
        return 0;
    }
    flag = findToggle(argv, argc);
    start = 1 - flag;
    numLines = validArgs(argv, start);
    if (numLines)
    {
        environ = makeEnv(argv, flag, numLines, envLen());
    }
    callCommand(argv, argc, numLines, start);
    printEnv();
    return 0;
}