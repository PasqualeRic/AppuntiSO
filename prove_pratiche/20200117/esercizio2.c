#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 256

int recdir(char *path, ino_t finode, char *destpath, char* option){
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
                if(strcmp(option,"c") == 0 && strcmp(toUse,destpath) != 0){
                    FILE* original = fopen(destpath, "r");
                    FILE* copy = fopen("./copy", "w");
                    char ch;
                    while ((ch = fgetc(original)) != EOF)
                        fputc(ch, copy);
                    rename("./copy", toUse);
                    remove("./copy");

                }else if(strcmp(option,"s") == 0 && strcmp(toUse,destpath) != 0){
                    symlink(destpath, "newsimlink");
                    rename("./newsimlink", toUse);
                    remove("./newsimlink");
                }
			}else{
                stat(toUse, &st);
			    if(st.st_ino == finode){
                    printf("symlink   %s\n", toUse);
                    if(strcmp(option,"l") == 0){
                        link(destpath, "newphislink");
                        rename("./newphislink", toUse);
                        remove("./newphislink");
                    }
			    }
            }
			recdir(toUse, finode, destpath, option);
		}
	}
}

int main(int argc, char* argv[]){
	struct stat st;
    char buffer1[BUF_SIZE];
    char buffer2[BUF_SIZE];
    char*opt;

    switch(getopt(argc, argv, "cls")){
        case 'c':
        case 'l':
        case 's':{
            stat(argv[2], &st);
            realpath(argv[3],buffer1);
		    realpath(argv[2],buffer2);
            opt = &(argv[1][1]);
		    recdir(buffer1, st.st_ino, buffer2, opt);
            break;
        }
        case '?':{
            printf("comando non trovato\n");
            break;
        }
        default:{
            stat(argv[1], &st);
            realpath(argv[2],buffer1);
		    realpath(argv[1],buffer2);
		    recdir(buffer1, st.st_ino, buffer2, opt);
        }
    }
}