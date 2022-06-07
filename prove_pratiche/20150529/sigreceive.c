#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>

#define BUFSIZE 256

void handler(){

}

int main(int argc, char*argv[]){

    sigset_t mask;
    ssize_t s;
    struct signalfd_siginfo fdsi;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    signal(SIGUSR1, handler);
    int fd = signalfd(-1,&mask,0);

    printf("sigreceive pid: %d\n",getpid());

    while(1){
        s = read(fd,&fdsi, sizeof(fdsi));
        
        if(fdsi.ssi_signo == SIGUSR1){
            printf("SIGUSR1\n");

            char buffer[BUFSIZE];
            strcpy(buffer, "/tmp/giro");

            int length = snprintf( NULL, 0, "%d", getpid() );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", getpid() );

            strcat(buffer, str);
            FILE* source = fopen(buffer, "r");
            if( source == NULL ){
                printf("file not found\n");
            }else{
                char c;
                while ( (c = fgetc(source)) != EOF ){
                    putchar(c);
                }
                remove(buffer);
            }
            
            int senderpid = fdsi.ssi_pid;
            kill(senderpid,SIGUSR1);
        }
        if(fdsi.ssi_signo == SIGUSR2){
            return 0;
        }
    }
    return 0;
}