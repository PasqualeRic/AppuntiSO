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

int main(int argc, char *argv[]){
    int pidv[MAX_ARGS];
	char* cmd[MAX_ARGS];
    int status;
    int i = 1, j = 0, k = 0, z = 0;

    for(int y = 0; y < MAX_ARGS; y++)
		pidv[y] = 0;

    while(i < argc){
		if(strcmp(argv[i], "//") != 0){
			cmd[j] = argv[i];
			j++;	
		}
		else{                               //fine di un comando, facciamo partire il processo	
            startproc(cmd, pidv, j, k);
			k++;
			j = 0;
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
