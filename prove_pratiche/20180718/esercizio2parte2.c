#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <string.h>

#define BUFSIZE 256

int main(int argc, char*argv[]){

    char*pidpath = argv[1];

    FILE* file = fopen(pidpath,"r");
    int pid;
    fscanf(file,"%d",&pid);
    printf("pid: %d\n", pid);
    fclose(file);

    kill(pid, SIGUSR1);

    char comm[BUFSIZE] = "/bin/";
    strcat(comm,argv[2]);
    char* args[argc];
    for(int i=2;i<=argc;i++){
        if(i == argc){
            args[i-2] = 0;
        }else args[i-2] = argv[i];
    }
    execv(comm,args);

    kill(pid, SIGUSR2);    //non prende signusr2
}

