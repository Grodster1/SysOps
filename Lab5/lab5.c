#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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


int zad1_v2(void){

    srand(time(NULL));
    int a = rand() % 11;
    int b = rand() % 11 + 20;
    printf("Wylosowane liczby to: a = %d, b = %d\n", a, b);

    pid_t pid = fork();

    if(pid == 0){
        printf("Obliczanie sumy w procesie dziecka\n");
        int suma = a+b;
        exit(suma);
    }
    else{
        int status;
        wait(&status);
        printf("Suma liczb to: %d + %d = %d\n",a, b, WEXITSTATUS(status));
    }


    return 0;
}

int zad2_v2(void){
    //int num[1000000];
    pid_t pid;
    int size = 1000000;

    srand(time(NULL));
    int *num = calloc(size, sizeof(int));
    for(int i = 0; i < size; ++i){
        num[i] = rand() % 101;
    }

    for(int j = 0; j < 10; ++j){
        pid = fork();
        float mean = 0;
        
        if(pid == 0){
            for(int k = j*100000; k < (j+1)*100000; ++k){
                mean += (float)num[k];
            }
            mean = mean / 100000;
            exit((int)mean);
        }
    }

    float mean = 0;
    int status;
    for(int l = 0; l < 10; ++l){
        wait(&status);
        mean += WEXITSTATUS(status);
    }

    printf("Mean: %f\n", mean/10);
    free(num);
    return 0;
}

int zad3_v2(void){
    srand(time(NULL));
    //float num[1000000];
    pid_t pid;
    pid_t pids[10];
    FILE *fptr;
    int size = 1000000;

    float *num = calloc(size, sizeof(float));

    for(int i = 0; i < size; ++i){
        num[i] = ((float)rand() - (float)(RAND_MAX/2))/(float)(RAND_MAX/2); 
    }

    for(int j = 0; j < 10; ++j){
        pid = fork();
        char buffer[100];
        float sum = 0;

        if(pid == 0){
            for(int k = j * 100000; k < (j+1)*100000; ++k){
                sum+=num[k];
            }
            sprintf(buffer, "sum%d.txt", getpid());
            fptr = fopen(buffer, "w");
            if(fptr == NULL){
                printf("The file is not opened\n");
            }
            else{
                printf("File opened by: %d\n", getpid());
                fprintf(fptr, "%f\n", sum);
                fclose(fptr);
            }
            exit(0);
        }
        else{pids[j] = pid;}
    }

    float temp;
    float mean = 0;
    int status;
    for(int l = 0; l < 10; ++l){
        char name[100];
        waitpid(pids[l], &status, 0);
        sprintf(name, "sum%d.txt", pids[l]);
        fptr = fopen(name, "r");
        if(fptr == NULL){
            printf("Reading file failed PID: %d\n", pids[l]);
            continue;
        }

        fscanf(fptr, "%f", &temp);
        mean += temp;
        fclose(fptr);
        remove(name);
    }
    printf("Mean: %f\n", mean/size);
    free(num);
    num=NULL;

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

        if(strcmp(argv[1], "zad1_v2") == 0){
            return zad1_v2();
        }

        if(strcmp(argv[1], "zad2_v2") == 0){
            return zad2_v2();
        }

        if(strcmp(argv[1], "zad3_v2") == 0){
            return zad3_v2();
        }
    }
    return 0;
}