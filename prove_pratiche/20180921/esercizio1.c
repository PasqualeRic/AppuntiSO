#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <dirent.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <assert.h>

#define BUFSIZE 256

int main(int argc, char *argv[]){
    ssize_t s;
    char toPrint[BUFSIZE];
    struct signalfd_siginfo fdsi;

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGQUIT);
    int sfd = signalfd(-1, &mask, 0);

    for (;;) {
        s = read(sfd, &fdsi, sizeof(fdsi));
        if (s != sizeof(fdsi))
            printf("read\n");

        if (fdsi.ssi_signo == SIGQUIT) {      //sigquit è per test
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char s_t[64];
            assert(strftime(s_t, sizeof(s_t), "%c", tm));

            printf("Got SIGUSR1\n");
            strcpy(toPrint, "USR1");
            strcat(toPrint," ");
            strcat(toPrint, s_t);

            printf("%s\n",toPrint);

            char*filename;
            char *filebuf;
            char filebuf2[BUFSIZE] = "./";
            uint32_t num = fdsi.ssi_pid; 
            sprintf( filebuf, "%d", num );
            filename= strcat(filebuf2,filebuf);
            
            FILE *fileptr = fopen(filename,"w");
            fprintf(fileptr,"%s",toPrint);
            fclose(fileptr);
        }else{
            if (fdsi.ssi_signo == SIGUSR2) {
                time_t t = time(NULL);
                struct tm *tm = localtime(&t);
                char s_t[64];
                assert(strftime(s_t, sizeof(s_t), "%c", tm));

                printf("Got SIGUSR2\n");
                strcpy(toPrint, "USR2");
                strcat(toPrint," ");
                strcat(toPrint, s_t);

                char*filename;
                char *filebuf;
                char filebuf2[BUFSIZE] = "./";
                uint32_t num = fdsi.ssi_pid;
                sprintf( filebuf, "%d", num );
                filename= strcat(filebuf2,filebuf);
                
                FILE *fileptr = fopen(filename,"w");
                fprintf(fileptr,"%s",toPrint);
                fclose(fileptr);

            }
        }
    }
}