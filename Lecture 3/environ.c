/*

ENVIRON

the extern keyword is used to extend the visibility of variables/functions.

since functions are visible throughout the program by default, the use of extern is not needed in function declarations or definitions 
*/
#include <stdio.h> // printf
#include <time.h> // time, time_t, ctime
#include <unistd.h> // sleep

extern char **environ;

int main () {
    char * blah = "Blah";
    int i;
    for (i = 0; environ[i] != NULL; ++i){
        puts(environ[i]);
    }

    clearenv();
    //argv arr has the array of chrptrs
 /*   for (char** p = environ; *p != NULL; ++p){
        puts(*p);
    }*/
    
}
