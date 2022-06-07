#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>

#define BUFSIZE 256
#define __USE_XOPEN 1

int main(int argc, char*argv[]){
    char* filepath = argv[1];
    FILE *fileptr = fopen(filepath,"r");
    char line[BUFSIZE];
    int first = 1;
    time_t rawcurrenttime;

    while(fscanf(fileptr, "%[^\n] ", line) != EOF){
        char l[BUFSIZE];
        strcpy(l,line);
        if(first){            
            struct tm current;
            first=0;
            char buf[BUFSIZE];

            strncpy(buf,l,15);
            printf("%s\n",l);
            strptime(buf, "%b %d %H:%M:%S", &current);
            rawcurrenttime = mktime(&current);
        }else{
            struct tm new;
            time_t newcurrenttime;

            char buf[BUFSIZE];

            strncpy(buf,l,15);
            strptime(buf, "%b %d %H:%M:%S", &new);
            newcurrenttime = mktime(&new);
            sleep(abs(newcurrenttime-rawcurrenttime));
            printf("%s\n",l);
            rawcurrenttime = newcurrenttime;
        }
    }
    fclose(fileptr);
}