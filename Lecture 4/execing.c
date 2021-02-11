#include <stdio.h>
#include <unistd.h>

/* beginning of 2/11/21 lecture 
 * replaces current process image with a new
 * process image.
 */

int main(){
    char * argv[] = { "ls", "-l", NULL };
    execv(argv[0],argv);
    perror("execv must have failed or we wouldn't be here");
    return 0;
}
