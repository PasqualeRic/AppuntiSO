#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <wait.h>

#define BUFSIZE 256
#define MAXPROCS 64

int main(int argc, char*argv[]){

    char*path = argv[1];
    int proc = 0;
    pid_t pids[MAXPROCS];
    struct dirent *dir;
    DIR *d = opendir(path);
    if(!d){
        printf("Wrong path");
        return 0;
    }
    while((dir = readdir(d)) != NULL){
        if(strcmp( dir->d_name, ".") != 0 && strcmp( dir->d_name, "..") != 0){
            char buffer[BUFSIZE];
            strcpy(buffer, dir->d_name);
            int size = strnlen(buffer,BUFSIZE);
            if(isdigit(buffer[size-1])){
                int value = 0;
                //printf("lastChar: %c\n",buffer[size-1]);
                int i = 0;
                while(isdigit(buffer[(size-1)-i]) && i<size-1){
                    value+= (int) pow(10,i) * (buffer[(size-1)-i] - '0');
                    i++;
                }               
                if(!(pids[proc] = fork())){     
                    printf("waiting %s for: %d milliseconds\n",dir->d_name,value);   
                    usleep(1000 * value);
                    char pathbuf[BUFSIZE];
                    strcpy(pathbuf,"./");
                    strcat(pathbuf, dir->d_name);
                    printf("starting execution of %s with pid: %d\n",dir->d_name, getpid() );
                    char *args[] = {pathbuf,(char *)0};
                    /*if (execvp(pathbuf, args) < 0)
                        {
                            printf("error in exec\n");
                        }*/
                    execve(pathbuf, args,0);
                }
                proc++;
            }
        }
    }
    int i;
    int stat;
    for(i = 0; i<proc; i++){
        pid_t pid = waitpid(-1,&stat,0);
        printf("Terminated: %d\n",pid);
    }
    //while ((pid = wait(&stat)) > 0);
    return 0;
}