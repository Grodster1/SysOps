#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LICZBA_DZIECI 10

int zad4(void){
    printf("Poczatek\n");
    //pid_t parentPid = getpid();
    pid_t childPid = fork(); //child PID
    if(childPid == 0){ //child
        printf("Child\n");
        printf("Child PID: %d\n", getpid());
        printf("My parent's PID: %d\n", getppid());
        //execlp("ls", "ls", "-a", NULL);
        for(int i = 0; i < 20; ++i){
            printf("Child %d\n", i+1);
            sleep(1); 
        }
        //perror("Blad uruchomienia programu");
        exit(1);
    }
    else{
        printf("Parent\n");
        //printf("Child PID: %d\n", childPid);
        for(int i = 0; i < 10; ++i){
            printf("Parent %d\n", i+1);
            sleep(1); 
        }
        printf("Parent: Koniec petli, czekam na zakonczenie procesu dziecka\n");
        int status;
        waitpid(childPid, &status, 0);
        printf("Status: %d\n", status);
        printf("Parent: Koniec\n");
        return 0;
    }
        
}

int zad5(void){

    printf("Parent: start\n");
    if (fork() == 0)
    {
        printf("Child: start\n");
        sleep(10);
        printf("Child: Parent PID: %d\n", getppid());
        sleep(30);
        printf("Orhpan: Parent PID: %d\n", getppid());
        printf("Child: end\n");
        exit(0);
    }
    printf("Parent: wait 30 seconds\n");
    sleep(30);
    printf("Parent: end\n");
    exit(0);
}

int zad6(void){
    printf("Parent: start\n");
    if(fork() == 0){
        printf("Child: start\n");
        printf("Child: end\n");
        exit(0);
    }
    else{
        sleep(30);
        printf("Parent: before wait()\n");
        wait(NULL);
        printf("Parent: end\n");
        exit(0);
    }
}

int zad7(void){
    pid_t parent_pid = getpid();
    pid_t pid;
    printf("Parent PID: %d\n", parent_pid);
    for(int i = 0; i < LICZBA_DZIECI; ++i){
        pid = fork();
        if(pid < 0){
            perror("Fork error");
            exit(1);
        }
        else if(pid == 0){
            printf("Child %d (PID: %d) - created\n", i, getpid());
            sleep(2);
            printf("Child %d (PID: %d) - finished\n", i, getpid());
            exit(0);
        }
    }
    int status;
    for (int i = 0; i < LICZBA_DZIECI; i++) {
        wait(&status); 
    }

    printf("Parend (PID: %d) - cleaned after all children\n", parent_pid);
    return 0;
}

int main(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "zad4") == 0){
            return zad4();
        }
        
        if(strcmp(argv[1], "zad5") == 0){
            return zad5();
        }

        if(strcmp(argv[1], "zad6") == 0){
            return zad6();
        }

        if(strcmp(argv[1], "zad7") == 0){
            return zad7();
        }
    }
    return 0;
}