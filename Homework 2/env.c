#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;
char *TOGGLE = "-i";

void replaceEnv(char *contents[], int contentsSz)
{

    char **newEnviron = malloc(contentsSz * sizeof(char *));
    int i;
    printf("%d size\n", contentsSz);
    for (i = 0; i < contentsSz; i++)
    {
        printf("LOADING IN: %s\n", contents[i]);
        newEnviron[i] = contents[i];
    }
    newEnviron[i + 1] = NULL;
    environ = newEnviron;
}
/*
 * The checker function returns 1 if the strings
 * are the same up to the '=' sign and 0 if
 * the strings are not the same up to that point.
 */
int checker(char input[], char check[])
{
    int i, res = 1;

    for (i = 0; input[i] != '=' || check[i] != '='; i++)
    {
        if (input[i] != check[i])
        {
            res = 0;
            break;
        }
    }
    return res;
}
/*
 * Resize function to resize our dynamic array when needed
 */
void resize(char **currArr, int *size)
{
    int newSz = (*size) * 2;
    char **tempArr = malloc((newSz) * sizeof(char *));

    for (int i = 0; i < *size; i++)
    {
        tempArr[i] = currArr[i];
    }
    free(currArr);
    *size = newSz;
    currArr = tempArr;
}
void modifyEnv(char *contents[], int contentsSz)
{
    int i, j, replaceBool, maxSz = 512;
    char **newEnviron = malloc(512 * sizeof(char *));

    for (i = 0; i < contentsSz; i++)
    {

        for (j = 0; environ[j] != NULL; j++)
        {
            replaceBool = 1;
            replaceBool = checker(environ[j], contents[i]); //check to replace env variable
            if (j + 2 > maxSz)
            {
                resize(newEnviron, &maxSz); //resize when needed
            }

            if (replaceBool == 0)
            {
                newEnviron[j] = environ[j];
            }
            else
            {
                newEnviron[j] = contents[i];
            }
        }
        if (replaceBool == 0)
        {
            newEnviron[j + 1] = contents[i]; //add to the end
            printf("adding to the end\n");
        }
        newEnviron[j + 2] = NULL;
        environ = newEnviron;
    }
}

void findToggle(char *argv[], int argc, int *findI)
{
    int argvInd;
    for (argvInd = 0; argvInd < argc; argvInd++)
    {
        if (argv[argvInd][0] == '-' && argv[argvInd][1] == 'i' && argv[argvInd][2] == '\0')
        {
            *findI = argvInd; //location of last toggle found
        }
    }
}

void grabContents(char *argv[], int startIndex, int size, char *contents[])
{
    int i;
    for (i = startIndex + 1; i < size; i++)
    {
        //    valid = checkValidity(argv[i+1]);
        contents[i] = argv[i];
    }
}

void printvec(char *charVec[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("index[%d] : %s\n", i, charVec[i]);
    }
}
/* This function is responsible for printing the environment
 */
void printEnviron()
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        puts(environ[i]);
    }
}

int main(int argc, char *argv[])
{
    int findI = 0;
    if (argc == 1)
    {
        // display environment
        for (int i = 0; environ[i] != NULL; i++)
        {

            puts(environ[i]);
        }
    }
    else
    {

        findToggle(argv, argc, &findI);  // find last occurrance of -i
        int contentsSz = argc - (findI); // size of the remaining space

        char *contents[contentsSz];
        grabContents(argv, findI, contentsSz, contents);
        printvec(contents, contentsSz);

        if (findI == 1)
        {
            // replace environment
            replaceEnv(contents, contentsSz);
            printEnviron();
            free(environ);
        }
        else
        {
            // don't replace environment
            modifyEnv(contents, contentsSz);
            printEnviron();
        }
    }
    return 0;
}
