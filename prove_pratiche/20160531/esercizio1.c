#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>

#define BUFSIZE 256

typedef struct elem{
    char* name;
    int value;
    struct elem *next;
}elem;

elem* newElem(){
    elem*new = malloc(sizeof(elem));
    new->next = NULL;
    new->value = 0;
    new->name = " ";
    return new;
}

void insertOrderedByValue(elem*head, elem*e){
    elem*copy = head;
    elem*prev = copy;
    while(copy->value <= e->value && copy->next != NULL){
            prev = copy;
            copy=copy->next;
    }
    if(copy->value < e->value){
        copy->next = newElem();
        copy = copy->next;
        copy->name = e->name;
        copy->value = e->value;
    }else{
        e->next = copy;
        prev->next = e;
    }
}

int main(int argc, char*argv[]){
    char* path = argv[1];
    DIR*d = opendir(path);
    struct dirent *dir;

    elem *head = newElem();

    while((dir = readdir(d)) != NULL){
        if(strcmp(dir->d_name,".") !=0 && strcmp(dir->d_name,"..")){
            char buf[BUFSIZE];
            strcpy(buf, dir->d_name);
            char*token = strtok(buf,".");
            char*last;
            while(token != NULL){
                last = token;
                token = strtok(NULL,".");
            }
            int i=0;
            int isNum = 1;
            while(last[i]!= '\0'){
                if(!isdigit(last[i]))
                    isNum = 0;
                i++;
            }
            if(isNum){
                elem*e = newElem();
                e->name = dir->d_name;
                e->value = atoi(last);
                //printf("%d\n",e->value);
                insertOrderedByValue(head,e);
            }
            
        }
    }
    elem *copy = head; 
    while(copy != NULL){
        if(strcmp(copy->name," ") != 0){
            printf("%s\n",copy->name);
        }
        copy = copy->next;
    }

}