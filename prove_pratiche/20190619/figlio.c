#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int i;
	for(i = 0; i < 5; i++){
		printf("figlio\n");
		sleep(1);
	}
}