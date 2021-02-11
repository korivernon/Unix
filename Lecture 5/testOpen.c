#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// write and read return how many bytes were read/written

const char * const BUF = "Default junk to write\n";

int main(int argc, char *argv[]){
    int fd = open("testOpen.txt", O_WRONLY | O_CREAT, 0666);
    if (fd == -1){
        perror("Failed to create testOpen.txt");
        exit(1);
    }
    if (argc > 1){
        if (write(fd, argv[1], strlen(argv[1])) < 0){
            perror("Failed to write testOpen.txt");
            exit(1);
        }
    } else if (write(fd, BUF, strlen(BUF)) < 0){
        perror("Failed to write to testOpen.txt");
            exit(1);
    }
    fprintf(stdout, "Finished writing testOpen.txt\n");
    if (close(fd) < 0){
        perror("Couldn't close testOpen.txt\n");
        exit(1);
    }
    return 0;
}
