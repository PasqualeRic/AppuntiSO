//nota: per evitare problemi con i file userò una directory test di default invece di quella corrente

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFSIZE 256

int value =  864000;

void modifyAllFilesIn(char *path, int type){
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
                struct stat attr;
                char buffer[BUFSIZE];
                strcat(buffer, path);
                strcat(buffer, dir->d_name);
                stat(buffer, &attr);

                printf("Last modified time: %s", ctime(&attr.st_mtime));
                
                struct timeval times[2];
                if(type){
                    times[0].tv_sec = attr.st_atim.tv_sec + value;
                    times[0].tv_usec = 0;
                    times[1].tv_sec = attr.st_mtim.tv_sec;
                    times[1].tv_usec = 0;
                }else{
                    times[0].tv_sec = attr.st_atim.tv_sec;
                    times[0].tv_usec = 0;
                    times[1].tv_sec = attr.st_mtim.tv_sec + value;
                    times[1].tv_usec = 0;
                }
                
                utimes(buffer, times);
            }
        }
        closedir(d);
    }
}

void modifyTheseFiles(char *files[]){

}

int main(int argc, char*argv[]){

    char* files[argc];

    FILE *fileptr = fopen("./data.txt","r");
    fscanf(fileptr,"%d",&value);
    fclose(fileptr);

    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    localtime( &rawtime );

    switch(getopt(argc, argv, "amth")){
        case 't':{
            char*val = argv[2];
            FILE *fileptr = fopen("./data.txt","w");
            value = fprintf(fileptr,"%s",val);
            fclose(fileptr);
            break;
        }
        case 'm':{
            if (argc > 2){
                for (int i=2; i<argc;i++){
                    files[i-2] = argv[i];
                }
            } else modifyAllFilesIn("./testdir/", 0);
            break;
        }
        case 'a':{
            if (argc > 2){
                for (int i=2; i<argc;i++){
                    files[i-2] = argv[i];
                }
            } else modifyAllFilesIn("./testdir/", 1);
            break;
        }
        case 'h':{
            printf("-a: Mofifica la data di accesso di: %d\n",value);
            printf("-m: Mofifica la data di modifica di: %d\n",value);
            printf("-t: Mofifica il valore di invecchiamento\n");
            break;
        }
        case '?':{
            printf("Comando non riconosciuto\n");
            break;
        }
        default:{
            modifyAllFilesIn("./testdir/",0);
        }
    }
}