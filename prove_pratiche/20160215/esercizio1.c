#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 256

int main(int argc, char*argv[]){
    char*path;
    if(argc>1) path = argv[1];
    else path = "./";
    
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
            //printf("lastChar: %c\n",buffer[size-1]);
            if(isdigit(buffer[size-1]))
                printf("File: %s\n",buffer);
        }
    }
    return 42;


}