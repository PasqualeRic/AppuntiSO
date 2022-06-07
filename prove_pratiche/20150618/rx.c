#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <wait.h>
#include <string.h>

void sig_handler(){
}


void rx(){
    printf("pid rx: %d\n",getpid());
    ssize_t s;
    struct signalfd_siginfo signal;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    int fd = signalfd(-1, &mask, 0);
    int true = 1;
    while(true){
        s = read(fd,&signal,sizeof(signal));
        if (signal.ssi_signo == SIGUSR1) {
            printf("Got SIGUSR1\n");
        }else{
            if (signal.ssi_signo == SIGUSR2) {
                printf("Got SIGUSR2\n");
            }else{
                printf("received not recognised signal\n");
            }
        }   
    }
    close(fd);
    
}

int main(int argc, char*argv[]){
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    rx();
    return 0;
}