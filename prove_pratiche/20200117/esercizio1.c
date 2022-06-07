#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256

int recdir(char *path, ino_t finode, char *destpath){
	char buf[BUF_SIZE];
	DIR *d = opendir(path);
	struct dirent* dirf;
	struct stat st;
	if(!d)
		return 1;
	char newpath[BUF_SIZE];
    strcpy(newpath,path);
    strcat(newpath,"/");

	while(dirf = readdir(d)){
        char toUse[BUF_SIZE];
        strcpy(toUse,newpath);
        strcat(toUse,dirf->d_name);
        if(strcmp(dirf->d_name, ".") != 0 && strcmp(dirf->d_name, "..") != 0){
            lstat(toUse, &st);
			if(st.st_ino == finode){
				printf("phlink   %s\n", toUse);
			}else{
                stat(toUse, &st);
			    if(st.st_ino == finode){
                    printf("symlink   %s\n", toUse);
			    }
            }
			recdir(toUse, finode, destpath);
		}
	}
}

int main(int argc, char** argv){
	struct stat st;
	stat(argv[1], &st);

    char buffer1[BUF_SIZE];
    char buffer2[BUF_SIZE];

	realpath(argv[2],buffer1);
	realpath(argv[1],buffer2);
	recdir(buffer1, st.st_ino, buffer2);
	return 0;
}