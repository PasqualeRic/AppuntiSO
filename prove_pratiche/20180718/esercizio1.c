#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/signalfd.h>

int main(int argc, char*argv[]){

    sigset_t mask;
    int sfd;
    struct signalfd_siginfo fdsi;
    ssize_t s;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGQUIT);    //da sostituire

    sfd = signalfd(-1,&mask,0);

    int count1 = 0, count2 = 0;

    while(1){
        s = read(sfd, &fdsi,sizeof(fdsi));
        if (fdsi.ssi_signo == SIGUSR1) {
            count1++;
            printf("SIGNUSR1 count: %d\n",count1);
        }
        if (fdsi.ssi_signo == SIGQUIT) {        //da sostituire
            count2++;
            printf("SIGNUSR2 count: %d\n",count2);

        }
    }
    
}