#include <stdio.h>
#include <unistd.h>
/*
 * using execvp to run "ls -l"
 */

int main(){
    char * argv[] = { "ls", "-l", NULL };
    execvp(argv[0],argv);
    perror("execv must have failed or we wouldn't be here");
    return 0;
}
