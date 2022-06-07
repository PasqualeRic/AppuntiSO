#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFSIZE 256

int main(int argc, char*argv[]){

    int numProc;
    char*file1;
    char*file2;
    int fd;

    switch(getopt(argc, argv, "j")){
        case 'j':{
            numProc = atoi(argv[2]);
            file1 = argv[3];
            file2 = argv[4];
            break;
        }
        case '?':{
            printf("opzione non riconosciuta\n");
            return 0;
        }
        default:{
            numProc = 2;
            file1 = argv[1];
            file2 = argv[2];
        }
    }

    fd = open(file1, O_RDONLY);
	int length1 = lseek(fd, 0, SEEK_END);
    close(fd);

    fd = open(file2, O_RDONLY);
	int length2 = lseek(fd, 0, SEEK_END);
    close(fd);

    if(length1 != length2) {
        printf("I file sono diversi per lunghezza\n");
        return 0;
    }

    int pids[numProc];
    int lengths[numProc+1];
    lengths[0] = 0;
    for(int i=1;i<numProc;i++){
        lengths[i] = lengths[i-1] + length1/numProc;
    }
    lengths[numProc] = length1;

    for(int i=0;i<numProc;i++){
        if(!(pids[i]=fork())){
            int fd1 = open(file1,O_RDONLY);
            int fd2 = open(file2,O_RDONLY);

            char buf1;
            char buf2;

            lseek(fd1, lengths[i], 0);
		    lseek(fd2, lengths[i], 0);
            for(int k = lengths[i];k<lengths[i+1];k++){
                read(fd1, &buf1, sizeof(char));
			    read(fd2, &buf2, sizeof(char));

                if(buf1 != buf2){
                    close(fd1);
                    close(fd2);
                    return 1;
                }
            }
            close(fd1);
            close(fd2);
            return 0;
        }
    }
    int i;
    int status;
	for(i = 0; i < numProc; i++){
		waitpid(-1, &status, 0);
		printf("Status %d: %d\n", i, WEXITSTATUS(status));
		if(WEXITSTATUS(status) == 1){
			printf("Different.\n");
			return 0;
		}
	}
    printf("i file sono uguali\n");
    return 0;
}