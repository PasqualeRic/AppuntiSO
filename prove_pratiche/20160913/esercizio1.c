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
    char *path1 = argv[1];
    char *path2 = argv[2];
    srand(time(NULL));

    int srcfd = open(path1, O_RDONLY);
    struct stat statbuf;
    fstat(srcfd, &statbuf);
    int destfd = open(path2, O_WRONLY | O_CREAT, statbuf.st_mode);

    fcntl(destfd, F_WRLCK);
    printf("sto bloccando per la copia\n");
    sleep(rand()%5);

    int n=1;
    while(n>0)
        n = sendfile(destfd,srcfd, 0, BUFSIZE);

    fcntl(destfd,F_UNLCK);
    printf("sto sbloccando per la copia\n");
    sleep(rand()%5);

    return 0;
}
