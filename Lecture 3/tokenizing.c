/*

Tokenizing

*/
#include <stdio.h>

char arr[] = "       one   two  three";
char *s = strtok(arr, " "); //get first Token

while (s != NULL) {
    printf("token: %s\n", s);
    s = strtok(NULL, " "); // get next token
}