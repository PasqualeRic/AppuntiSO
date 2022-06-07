#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define BUFSIZE 256
#define MAX_PROC 64

int main(int argc, char*argv[]){
    char* path = argv[1];
    DIR*d = opendir(path);
    struct dirent *dir;
    int j = 0;
    pid_t processes[MAX_PROC];

    while((dir = readdir(d)) != NULL){
        if(strcmp(dir->d_name,".") !=0 && strcmp(dir->d_name,"..")){
            char buf[BUFSIZE];
            strcpy(buf, dir->d_name);
            char*token = strtok(buf,".");
            char*last;
            while(token != NULL){
                last = token;
                token = strtok(NULL,".");
            }
            int i=0;
            int isNum = 1;
            while(last[i]!= '\0'){
                if(!isdigit(last[i]))
                    isNum = 0;
                i++;
            }
            if(isNum){
                if(!(processes[j] = fork())){
                    printf("dir: %s start and wait in %d for %d millisec\n", dir->d_name, j+1,atoi(last));
                    usleep(1000* atoi(last));
                    execve(dir->d_name,0,0);
                    return j;
                }
                j++;
            }
        }
    }
    int k;
    int status;
    for(k=0; k<j;k++){
        waitpid(-1, &status,0);
        printf("Finished process started as %d\n", WEXITSTATUS(status)+1);
    }
    return 0;
}