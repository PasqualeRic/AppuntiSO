#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/sendfile.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/fcntl.h>
#include <time.h>
#include <sys/stat.h>

#define BUFSIZE 256

int main(int argc, char *argv[]){
    char *path = argv[1];

    srand(time(NULL));

    int fd = open(path, O_RDONLY);

    fcntl(fd, F_RDLCK);
    printf("sto bloccando in lettura\n");
    sleep(10);

    fcntl(fd,F_UNLCK);
    printf("sto sbloccando in lettura\n");
    sleep(rand()%10);

    return 0;
}