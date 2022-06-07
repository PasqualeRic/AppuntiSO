#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define BUFSIZE 8
#define DELETEMASK 1000000000

int main(int argc, char *argv[]){
    int fd, wfd;
	char* path = argv[1];
	int i;

	fd = inotify_init();
	wfd = inotify_add_watch(fd,path,IN_DELETE);

    while(1){
        struct inotify_event event[BUFSIZE];
		int n = read(fd,event,sizeof(struct inotify_event)*BUFSIZE);
		for(int i=0; i < (n/sizeof(struct inotify_event)); i++){
            printf("action detected %#08x\n",event[i].mask & DELETEMASK);
			if((event[i].mask & DELETEMASK) == IN_DELETE){
                printf("file with name: %s deleted\n",event[i].name);
				char name[256];
				strcpy(name, path);
				strcat(name, "/");
				strcat(name, event[i].name);
				int tmpfd = open(name,O_CREAT | O_WRONLY, 0666);
				close(tmpfd);
			}
		}
    }
}