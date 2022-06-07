#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <signal.h>

void handler(){

}

int main(int argc, char*argv[]){

    sigset_t mask;
    ssize_t s;
    struct signalfd_siginfo fdsi;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    signal(SIGUSR1, handler);
    int fd = signalfd(-1,&mask,SFD_NONBLOCK);
    while(1){
        s = read(fd,&fdsi, sizeof(fdsi));
        char c;
        while ( (c=getchar()) != EOF ){
            putchar(c);
        }
        if(fdsi.ssi_signo == SIGUSR1){
            printf("SIGUSR1\n");
        }
    }
    return 0;
}