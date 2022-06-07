#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <wait.h>
#include <string.h>

void sig_handler(){
}


void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}



void rx(){
    printf("pid rx: %d\n",getpid());
    ssize_t s;
    struct signalfd_siginfo signal;
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);

    int fd = signalfd(-1, &mask, 0);
    int true = 1;
    while(true){
        s = read(fd,&signal,sizeof(signal));
        if (signal.ssi_signo == SIGUSR1) {
            printf("Got SIGUSR1\n");
        }else{
            if (signal.ssi_signo == SIGUSR2) {
                printf("Got SIGUSR2\n");
            }else{
                printf("received not recognised signal\n");
            }
        }   
    }
    close(fd);
    
}

void tx(pid_t rxpid, char*stringa){
    printf("tx ha parametri: %d e %s\n",rxpid, stringa);
    int length = strlen(stringa);
    for (int i = 0; i<length;i++){
        char output[9];
        itoa(stringa[i], output, 2);
        for(int j=0; j<7; j++){
            printf("char: %c\n",output[j]);
            if(atoi(&output[j])){
                printf("Sending signal 1\n");
                kill(rxpid, SIGUSR1);
            }else{
                printf("Sending signal 1\n");
                kill(rxpid, SIGUSR2);
            }
        }
    }
}

int main(int argc, char*argv[]){
    int txpid,rxpid; 
    char*stringa = "ciao";
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    if(!(rxpid = fork())){
        rxpid = getpid();
        if(!(txpid = fork())){
            tx(rxpid,stringa);
            return 0;
        }
        rx();
    }
    for(int i=0; i<2;i++){
        int status;
        waitpid(-1,&status,0);
    }
    return 0;
}