#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * tokenize(char * str, int * count){
    char tok = strtok(str, " " );
    char *argvector[80];
    while(tok!= NULL){
        printf("Loading: %s\n", argvector[*count]);
        argvector[*count] = tok;
        tok = strtok(NULL, " ");
        *count++;
    }
    argvector[*count] = '\n';
    return argvector;
}
void print(char ** string, int len){
    for(int i = 0; i < len; i++){
        printf("argument: %s\n", string[i]);
    }
}

int countOccurance(char string[]){
    int len = strlen(string);
    int count = 0;
    for(int i = 0 ; i < len; i++){
        if (strcmp(string, " ") == 0){
            count++;
        }
    }
    return count;
}
int main(void){
    char string[] = "hello my name is kori\n";
    char *p = strtok(string, " ");
    int occur = countOccurance(string);
    char *array[4];

    int i = 0;
    while (p != NULL){
        printf("%d", i);
        printf("%s\n", array[i]);
        array[i++] = p;
        p = strtok(NULL, " ");
    }
    for (int i = 0; i < occur; i++){
        printf("%s\n", array[i]);
    }
    return 0;
    
}
