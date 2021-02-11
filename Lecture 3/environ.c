/*

ENVIRON

*/
#include <stdio.h> // printf
#include <time.h> // time, time_t, ctime
#include <unistd.h> // sleep

extern char **environ;

int main () {
    for (int i = 0; environ[i] != NULL; ++i){
        puts(environ[i]);
    }
    //argv arr has the array of chrptrs
    for (char** p = environ; *p != NULL; ++p){
        puts(*p);
    }
    
}