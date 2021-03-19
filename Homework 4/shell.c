///------------------------------------------------///
///   Class:          <UNIX SYSTEM PROGRAMMING>    ///
///   Description:    <SHELL IMPLEMENTATION>       ///
///   Author:         <Kori Vernon>                ///
///   Date:           <03/21/2021>                 ///
///------------------------------------------------///
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <unistd.h>

#define BUF_LEN 1024
#define TRUE 1
#define EXITCOND 0
#define ANSI_R "\x1b[31m"
#define ANSI_B "\x1b[34m"
#define RESET "\x1b[0m"

int changeDirectory(char * destination);
/*
 * This function presents a welcome message to the user
 */
void welcome(void);
/*
 * This function changes the current working directory
 * particularly for the cd command
 */
void runShell(void);
/*
 * This function runs is the pilot function that
 * runs the shell.
 */
int parseDecisions(char **argv);
/*
 * This function parses the array for particular inputs
 */
char **tokenize(char *command);
/*
 * Function to tokenize and dynamically reallocate
 * memory, however, the function is not working with
 * code (done after the fact), so I am omitting
 */

int changeDirectory(char *destination)
{
    char buf[BUF_LEN];
    char *getDir = getcwd(buf, sizeof(buf));
    char *dir = strcat(getDir, "/");
    char *dest = strcat(dir, destination); //the destination is in argv
    return chdir(dest);
}

void welcome(void){
    char buf[BUF_LEN];
    char *getDir = getcwd(buf, BUF_LEN);
    printf(ANSI_R "trapshell" RESET);
    printf(ANSI_B "~%s\n" RESET, getDir );
    printf("$ "); 
}

char ** tokenize(char * command){
    const char * sep = " ";
    char **argv = malloc(sizeof(char *));
    if (argv){
        int i = 0;
        char *tok = strtok(command, sep);
        while (tok){
            char ** tempargv = realloc(argv, (i+1) * sizeof(char *)); //declare larger temp argv
            if (tempargv == NULL) break;
            argv = tempargv;
            i++;
            argv[i-2] = malloc(strlen(tok) + 1); //allocate specific amount of space
            if (argv[i-2] != NULL){
                // if this is an available space then copy 
                strcpy(argv[i-2], tok);
                tok = strtok(NULL, sep);
            }
        }
        argv[i-1] = NULL;
    }
    return argv;
}

int parseDecisions(char ** array){
    if (strcmp("exit", array[0]) == 0)
        return -1;
    else if (strcmp("cd", array[0]) == 0)
    { // in the event we have to change dir
        int success = changeDirectory(array[1]);
        if (success == -1)
        {
            printf("cd: error in changing directory\n");
        }
        else
            return 1;
    }
    else if (strcmp("l", array[0]) == 0)
    { // in the event we have "l"
        array[0] = "ls";
        array[1] = "-l", array[2] = NULL;
    }
    return 0;
}
void runShell(void){
    while(TRUE){
        welcome(); //print the welcome statement
        char command[BUF_LEN]; // buffer line
        if (!fgets(command, BUF_LEN, stdin)) break;
        // split command and return into argv
        int len = strlen(command), i = 0, success = 0;
        char *p = strtok(command, " "), *array[BUF_LEN];
        while (p != NULL){
            array[i++] = p;
            p = strtok(NULL, " ");
        }
        array[i++] = NULL; //set the last element to null for execing
        if (command[len-1] == '\n') command[len-1] = '\0';
        success = parseDecisions(array);
        if (success == -1) break;
        else if (success == 1) continue;
        int pid = fork();
        //check fork process to see if it failed 
        if (pid == 0){ // child  process
            if (execvp(array[0], array)){
                fprintf(stderr, "execvp: error, child process could not execvp :(\n");
                break;
            }
        }
        else if (pid == -1){
            printf("fork(): can't fork process\n");
            exit(1);
        }
        else {
            wait(0); // parent process
            printf("\n"); //print another line for separation
        }
    }
}

int main(void){
    runShell();
    return 0;
}
