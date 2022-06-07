#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define CHARBUFFER 256
#define FILEBUFFER 256
#define BUFSIZE 8
#define DELETEMASK 1000000000
#define MAXFILES 3

typedef struct fl{
    char* path;
    char* file;
    struct fl* next;
}fl;

fl*flhead;

fl *createNode(){
    fl *newNode = malloc(sizeof(fl));
    newNode->path = "";
    newNode->file = "";
    newNode->next = NULL;
    return newNode;
}

char *getFileData(char*name){
    fl* copy = flhead;
    while(strcmp(copy->path,name)!=0 && copy->next != NULL){
        copy = copy->next;
    }
    if(strcmp(copy->path,name)==0){
        return copy->file;
    }else{
        printf("file non ripristinabile\n");
        return "";
    }
}

void storeCurrentFilesIn(char *path){
    DIR *dir = opendir(path);
    struct dirent* e;
    int i=0;
    while(e = readdir(dir)){
        if(strcmp(e->d_name,".")!=0 && strcmp(e->d_name,"..")!=0){
            char toUse[CHARBUFFER];
            strcpy(toUse,path);
            strcat(toUse,e->d_name);

            printf("saved file: %s\n",toUse);

            fl* copy = flhead;
            while(copy->next != NULL){
                copy = copy->next;
            }
            copy->next = createNode();
            copy=copy->next;
            copy->path=toUse; 

            char saved[FILEBUFFER];
            FILE* tocopy = fopen(toUse, "r");
            char ch;
            while ((ch = fgetc(tocopy)) != EOF)
                strcat(saved,&ch);
            copy->file=saved;
        } 
    }
}

int main(int argc, char *argv[]){
    int fd, wfd;
	char* path = argv[1];
	int i;

    flhead = createNode();
    storeCurrentFilesIn(path);

	fd = inotify_init();
	wfd = inotify_add_watch(fd,path,IN_DELETE);

    while(1){
        struct inotify_event event[BUFSIZE];
		int n = read(fd,event,sizeof(struct inotify_event)*BUFSIZE);
		for(int i=0; i < (n/sizeof(struct inotify_event)); i++){
			if((event[i].mask & DELETEMASK) == IN_DELETE){
                printf("file with name: %s deleted\n",event[i].name);
				char name[256];
				strcpy(name, path);
				strcat(name, event[i].name);

                char*file = getFileData(name);    //non ritorna bene il file, controllare salvataggio
                FILE *fptr2 = fopen(name, "w");
                char c = file[0];
                int i=1;
                while (c != EOF)
                {
                    fputc(c, fptr2);
                    c = file[i];
                    i++;
                }
			}
		}
    }
}