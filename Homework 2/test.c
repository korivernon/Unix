#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;
/*
 * Ouputs the contents of the environ variable.
 */
void printEnviron()
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        puts(environ[i]);
    }
}
/*
 * This function will find the index of the toggle if it exists. 
 * If the toggle doesn't exist, the answer will be -1. Otherwise, 
 * it will be the index + 1 of the last "-i".
 */
int findToggle(char *argv[], int argc)
{

    int i, toggle = -1;
    for (i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            toggle = i;
        }
    }
    return toggle;
}

/*
 * This function allocates the enviornment on the heap
 */
char **envalloc(int validArgs, int envLen)
{
    char **newEnv = malloc((envLen + validArgs + 1) * sizeof(char *));
    int i = 0;
    for (i = 0; i < envLen; i++)
    {
        newEnv[i] = environ[i];
    }
    return newEnv;
}
/*
 * This function will determine the length of the environment
 * to be used for environment allocation. 
 */
int environLen()
{
    int i, sz = 0;
    for (i = 0; environ[i] != NULL; i++)
    {
        sz++;
    }
    return sz;
}
/*
 * This function validifies arguments by counting the 
 * ENV_VAR=STATUS pairs passed into the command line
 * function call. 
 */
int validArgs(char *argv[], int startInd)
{

    int i, validArg = 0;
    for (i = startInd; argv[i] != NULL; i++)
    {
        if (strchr(argv[i], '=') != NULL)
        {
            // if the pointer exists then we are inc count
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
int checker(char **envArr, char *input)
{
    int retVal = -1, inpLen;
    for (int i = 0; envArr[i] != NULL; i++)
    {
        inpLen = (int)(strchr(input, '=') - input);
        if (strncmp(envArr[i], input, inpLen) == 0)
        {
            retVal = i;
        }
    }
    return retVal;
}
/*
 * This function creates the environment and places the Key Value Pairs
 * where they belong.
 */
char** makeEnv(char * argv[], int envLen, int toggleInd, int validArgs) {
    char **newEnv = NULL, *envKey = NULL;
    int arg_i, i, loc, pair;
    if (toggleInd == -1){
        newEnv = envalloc(validArgs, envLen);
        arg_i = 1;
    } else {
        newEnv = malloc((validArgs+1)*sizeof(char*));
        arg_i = toggleInd+1;
        envLen = 0;
    }
    // add a new entry
    for (i = envLen; i <envLen+validArgs; i++){
        envKey = (char*)argv[arg_i];
        if (envKey == NULL){
            return newEnv; //reached the end
        }
        loc = checker(newEnv, envKey); //find the locatioon
        if (loc != -1){
            pair = i;
            i = loc;
        }
        newEnv[i] = malloc((strlen(envKey)+1) * sizeof(char)); //allocate memory
        newEnv[i] = envKey; //store new key value pair
        arg_i++;
    }
    return newEnv;
}



int main(int argc, char * argv[]){
    int toggle, validC;
    if (argc == 1){ // if only one argument is called
        printEnviron();
        return 0;
    }
    toggle = findToggle(argv, argc); // find the toggle
    validC = validArgs(argv, toggle); // count valid arguments
    if (validC > 0){
        printf("taking first fork");
        environ = makeEnv(argv, environLen(), toggle, validC);
    }
    if ((toggle+validC) < argc){
        if (execvp(argv[toggle+validC], (char* const*)(argv + toggle + validC)) == -1){
            perror("error in entry: invalid command");
            exit(1);
        }
    }
    printEnviron();
    return 0;
}
