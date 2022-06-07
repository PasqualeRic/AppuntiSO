#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int condiv;

int main(int argc, char *argv[]){
    for (int i=0; i<10;i++){
        srand(time(NULL));
        int random = (rand() % 10);
        printf("%d\n",random);
        condiv = random;
        sleep(2);
    }   
}