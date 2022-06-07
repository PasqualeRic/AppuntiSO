#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <stdint.h>

int main(int argc, char*argv[]){

    int milliseconds = atoi(argv[1]);
    uint64_t exp;
    int fd = timerfd_create(CLOCK_REALTIME,0);

    struct itimerspec tm;
    tm.it_value.tv_sec = (milliseconds * 1000000) / 1000000000;
    tm.it_value.tv_nsec = (milliseconds * 1000000) % 1000000000;
    tm.it_interval.tv_nsec=0;
    tm.it_interval.tv_sec=0;
    timerfd_settime(fd,0,&tm,NULL);

    ssize_t s = read(fd, &exp, sizeof(uint64_t));
    if (s != sizeof(uint64_t))
        printf("read\n");     
}