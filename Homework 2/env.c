#include <stdio.h>
#include <stdlib.h>

extern char** environ;
char * TOGGLE = "-i";
void findToggle(char * argv[], int argc, int * findI){
    int argvInd;
    for (argvInd = 0; argvInd < argc; argvInd++){
        if (argv[argvInd] == TOGGLE){
            *findI = 1;
        }
    }
}

void grabContents(char * argv[], int indices, char * contents[]){
    int i;
    for (i = 0; i < indices; i++ ){
        contents[i] = argv[i+1];
    }
}

void printContents(char * contents[], int len){
    for (int i = 0; i < len; i++){
        printf("%s\n", contents[i]);
    }
}
int main(int argc, char * argv[]){
    int findI = 0;
    if (argc == 1){
        // display environment
        for(int i = 0; environ[i] != NULL; i++){
            puts(environ[i]);
        }
    } else {
        char * contents[argc-1];
        grabContents(argv, argc-1, contents);
        findToggle(argv, argc, &findI);
        if (findI == 1){
            // replace environment
            printContents(contents, argc-1);
        } else {
            // don't replace environment
        }
    }
    return 0;
}
