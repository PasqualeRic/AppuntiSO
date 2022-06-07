#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>

#define BUFSIZE 256

char*pid;

void handler(){

}

void handler2(){
    kill(atoi(pid), SIGUSR2);
}

int main(int argc, char*argv[]){

    sigset_t mask;
    ssize_t s;
    struct signalfd_siginfo fdsi;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGINT);
    signal(SIGUSR1, handler);
    signal(SIGINT, handler2);
    int fd = signalfd(-1,&mask,0);

    pid = argv[1];
    char buffer[BUFSIZE];
    strcpy(buffer, "/tmp/giro");
    strcat(buffer, pid);
    while(1){
        FILE* file = fopen(buffer,"w");
        char c;
        while ( (c=getchar()) != EOF ){
            fputc(c, file);
        }
        printf("endstring\n");
        fclose(file);
        kill(atoi(pid), SIGUSR1);

        s = read(fd,&fdsi, sizeof(fdsi));
        
        if(fdsi.ssi_signo == SIGINT){
            return 0;
        }
    }
    

}