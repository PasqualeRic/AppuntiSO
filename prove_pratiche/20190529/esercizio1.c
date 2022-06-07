#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <sys/eventfd.h>

int condiv = 0;
int semp, semc;
uint64_t u = 1;

void *producer(){
    for (int i=0; i<10;i++){
        read(semp, &u, sizeof(uint64_t));
		condiv = rand()%1000;
		printf("Produced %d\n", condiv);
		write(semc, &u, sizeof(uint64_t));
		usleep(50000+rand()%500000);
    }   
}

void *consumer(){
    for (int i=0; i<10;i++){
        read(semc, &u, sizeof(uint64_t));
		printf("Consumed %d\n", condiv);
		write(semp, &u, sizeof(uint64_t));
		usleep(50000+rand()%500000);
    }
}

int main(){
	semp = eventfd(1, 0);
	semc = eventfd(0, 0);
	pthread_t p, c;
	pthread_create(&p, 0, producer, 0);
	pthread_create(&c, 0, consumer, 0);
	pthread_join(p,0);
	pthread_join(c,0);
	return 0;
}