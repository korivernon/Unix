#include <stdio.h> 
#include <string.h>
#include <unistd.h>
#include <stdbool.h> 
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_LEN 80
#define TRUE 1
#define EXITCOND 0
#define EX exit\n

void runShell(void){
    while(TRUE){
        printf("trapshell\n$ ");
        char command[BUF_LEN]; // buffer line
        if (!fgets(command, BUF_LEN, stdin)) {
            break;
        }
        
        if (strcmp(command, "exit\n") == EXITCOND || strcmp(command, "exit\0") == EXITCOND){
            break;
        } // if the line is exit\n then exit
        // split command and return into argv
        int pid = fork();
        char *p = strtok(command, " ");
        char *array[80];
        int i = 0;
        while (p != NULL){
            array[i++] = p;
            p = strtok(NULL, " ");
        }
        array[i++] = NULL;
        if (pid == 0){ // child  process
            execvp(array[0], array);
            fprintf(stderr, "execlp err: child process could not execlp\n\n");
            break;
        }
        else{
            wait(0); // parent process
        }
    }
}

int main(void){
    runShell();
    return 0;
}
