#include <stdio.h>
#include <unistd.h>

/* beginning of 2/11/21 lecture 
 * replaces current process image with a new
 * process image.
 *
 * exec is only going to return if exec fails!
 * once exec has replaced the current memory image with
 * the present memory image, then it will not return.
 *
 * perhaps you did not have executable permission... if
 * exec fails. 
 *
 * the notion of "When do we come back from exec" does
 * not exist; the only time we come back from exec is
 * if we get a return statement.
 *
 * exec always returns -1 -> indicates success.. you
 * do not have to check return value
 */

int main(){
    char * argv[] = { "ls", "-l", NULL };
    execv(argv[0],argv);
    perror("execv must have failed or we wouldn't be here");
    return 0;
}
