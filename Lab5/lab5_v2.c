#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

int zad1(void){

    srand(time(NULL));
    int a = rand() % 11;
    int b = rand() % 11 + 20;
    printf("Wylosowane liczby to: a = %d, b = %d\n", a, b);

    pid_t pid = fork();

    if(pid == 0){
        int suma = a+b;
        exit(suma);
    }
    else{
        int status;
        exit(&status);
        printf("Suma liczb to: %d + %d = %d",a, b, WEXITSTATUS(status));
    }


    return 0;
}


int main(int argc, char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "zad1") == 0){
            return zad1();
        }
    }
}