#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <stdint.h>
#include <sys/poll.h>

int main(int argc, char*argv[]){

    int milliseconds[argc-1];
    uint64_t exp;
    int fd[argc-1];
    struct itimerspec tm[argc-1];
    struct pollfd ufds[argc-1];

    for (int i=1;i<argc;i++){
        milliseconds[i-1]=atoi(argv[i]);
        fd[i-1] = timerfd_create(CLOCK_REALTIME,0);  
        tm[i-1].it_value.tv_sec = (milliseconds[i-1] * 1000000) / 1000000000;
        tm[i-1].it_value.tv_nsec = (milliseconds[i-1] * 1000000) % 1000000000;
        tm[i-1].it_interval.tv_nsec=0;
        tm[i-1].it_interval.tv_sec=0;
        timerfd_settime(fd[i-1],0,&(tm[i-1]),NULL);  
        ufds[i-1].fd = fd[i-1];
        ufds[i-1].events = POLLIN;   
    }
    for(int i=0;i<argc-1;i++){
        poll(ufds+i, argc-1-i,-1);
        printf("%d\n",milliseconds[i]);
    }
}