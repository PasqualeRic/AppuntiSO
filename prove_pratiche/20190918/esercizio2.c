#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 8
#define BUF_SIZE 256

void startproc(char* cmd[], int pidv[], int j, int k){
    char bin[BUF_SIZE] = "/bin/";
			strcat(bin, cmd[0]);            //   /bin/comando
			cmd[j] = 0;
			if(!(pidv[k] = fork())){
				if(execve(bin, cmd, NULL))
					perror("exec: ");
            }
}
/*
int globalNumProc = 0;
int globalIndex = -1;
char* cmds[MAX_ARGS];

void getAllCommands(char* separedBy, int start, int argc, char *argv[]){
    char* cmd[MAX_ARGS];
    int y=0;
    int j=0;
    for(int i = start; i<argc; i++){
        if(strcmp(argv[i], separedBy) != 0){
			cmd[j] = argv[i];
			j++;	
		}else{
            for(int k=0; k<j;k++){
                if(k==0) {
                    char buf[BUF_SIZE] = "/bin/";
                    strcat(buf,cmd[k]);
                    cmds[y] = buf;
                }else{
                    char buff[BUF_SIZE];
                    strcpy(buff,cmds[y]);
                    strcat(buff," ");
                    strcat(buff,cmd[k]);
                    cmds[y] = buff;
                }
            }

            y++;           
            j=0;
        }
    }
    printf("%s\n",cmds[1]);
    for(int k=0; k<j;k++){
        if(k==0) {
            char buf[BUF_SIZE] = "/bin/";
            strcat(buf,cmd[k]);
            cmds[y] = buf;
            
        }else {
            char buff[BUF_SIZE];
            strcpy(buff,cmds[y]);
            strcat(buff," ");
            strcat(buff,cmd[k]);
            cmds[y] = buff;
            
        }
        
    }
    globalNumProc = y+1;
}

char* nextCommand(){
    globalIndex++;
    if(globalIndex<globalNumProc)
        return cmds[globalIndex];
}
*/
int main(int argc, char *argv[]){
    int pidv[MAX_ARGS];
	char* cmd[MAX_ARGS];
    int status;
    int i = 2, j = 0, k = 0, z = 0;
    int maxProc = atoi(argv[1]);
    printf("%d\n",maxProc);
    int activeProc = 0;

    for(int y = 0; y < MAX_ARGS; y++)
		pidv[y] = 0;

    while(i < argc){
		if(strcmp(argv[i], "//") != 0){
			cmd[j] = argv[i];
			j++;	
		}
		else{                               //fine di un comando, facciamo partire il processo	
            startproc(cmd, pidv, j, k);
            activeProc++;
			k++;
			j = 0;
            if(activeProc == maxProc){
                while(z < MAX_ARGS && pidv[z] != 0){
		            waitpid(-1, &status, 0);
		            z++;
                    activeProc--;
                    break;
	            }
            }
        }
		i++;
        if(i == argc) startproc(cmd, pidv, j, k);    //ultimo processo (la stringa non finisce con //)
	}	
	while(z < MAX_ARGS && pidv[z] != 0){
		waitpid(pidv[z], &status, 0);
		z++;
	}
	return 0;
}
