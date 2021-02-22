#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;
int BUF = 512;
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

void printNewEnviron(char ** argv){

    for(int i = 0; argv[i] != NULL; i ++){
        printf("%s\n", argv[i]);
    }
}

void addToEnv(char * thing){

    char**newEnviron = malloc(BUF*sizeof(char*));

    int i = 0;

    for (i = 0; environ[i] != NULL; i++){
        
        if (i + 1 > BUF){
            resize(newEnviron, &BUF);
        }
        newEnviron[i] = environ[i];
    }
    newEnviron[i+1] = thing;
    newEnviron[i+2] = NULL;
    printNewEnviron(newEnviron);
    environ = newEnviron;
}

void printEnviron()
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        puts(environ[i]);
    }
}


int main(){

    char * thing = "\n";
    addToEnv(thing);
    
    return 0;
}
