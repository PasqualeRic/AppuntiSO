#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#define MAXFILES 256
#define BUFSIZE 256

ino_t inodes[MAXFILES];
int counts[MAXFILES];
int count = 0;

void initCounters(){
    for (int i=0;i<MAXFILES; i++) 
        counts[i] =0;
}

int counter(char*path){
    struct dirent *dir;

    DIR* d = opendir(path);
    if(!d) {
        printf("Error finding path");
        return 0;    
    }

    while((dir = readdir(d)) != NULL){
        if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && (dir->d_type == DT_REG || dir->d_type == DT_DIR)){
            ino_t inode  = dir->d_ino;
            int found = 0;
            for(int i = 0; i<count; i++){
                if(inode == inodes[i]){
                    found = 1;
                    counts[i]++; 
                }
            }
            if(!found) {
                inodes[count]=inode;
                counts[count]++;
                count++;
            }
            if (dir->d_type == DT_DIR) {
                char buffer[BUFSIZE];
                strcpy(buffer,path);
                strcat(buffer, "/");
                strcat(buffer,dir->d_name);
                counter(buffer);
            }
        }
    }
    return 1;
}

int main(int argc, char *argv[]){
    char*path;
    if (argc>1) path = argv[1];
    else path = "./";

    initCounters();

    if(counter(path) == 0){
        return 0;
    }

    int x=0;
    for (int j=1; j<count; j++){
        for(int i=0;i<count;i++){
            if(counts[i]==j)
                x++;
        }
        if(x>0)
            printf("Files with %d names: %d\n",j,x);
        x=0;
    }

    printf("File totali (esclusa la directory passata): %d\n", count);
}