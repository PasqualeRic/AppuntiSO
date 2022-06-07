#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <string.h>

void handler(int sig, siginfo_t *info, void *ucontext) {}

int main(int argc, char*argv[]){

    char*path = argv[1];

    sigset_t mask;
    int sfd;
    struct signalfd_siginfo fdsi;
    ssize_t s;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);    //da sostituire

    sfd = signalfd(-1,&mask,0);

    int count1 = 0, count2 = 0;

    FILE* fileptr = fopen(path,"w");

    pid_t pid = getpid();
    char * mypid = malloc(sizeof(pid_t));
    sprintf(mypid, "%d", pid);
    fprintf(fileptr,"%s", mypid);
    fclose(fileptr);


    struct sigaction new,info;
    sigaction(SIGUSR1,NULL,&info);
    new.sa_flags=0;
    sigemptyset(&(new.sa_mask));
    new.sa_handler = &handler;
    sigaction(SIGUSR1,&new,&info);

    struct sigaction new2,info2;
    sigaction(SIGUSR2,NULL,&info2);
    new2.sa_flags=0;
    sigemptyset(&(new2.sa_mask));
    new2.sa_handler = &handler;
    sigaction(SIGUSR2,&new2,&info2);

    while(1){
        s = read(sfd, &fdsi,sizeof(fdsi));
        if (fdsi.ssi_signo == SIGUSR1) {
            count1++;
            printf("SIGNUSR1 count: %d\n",count1);
        }
        if (fdsi.ssi_signo == SIGUSR2) {        //da sostituire
            count2++;
            printf("SIGNUSR2 count: %d\n",count2);
        }
    }
}