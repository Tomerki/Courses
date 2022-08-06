//Tomer Hadar
#include <sys/fcntl.h>
#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"

//handler signals from clients.
void handler(){
    alarm(0);
    signal(SIGUSR1, handler);
    pid_t pid;
    //child Process to handle the client signal
    pid = fork();
    if(!pid){
        char arg[4][10] = {'0'};
        int fd, i, j;
        fd = open("to_srv.txt", O_RDONLY , 777);
        if(fd == -1){
            printf("ERROR_FROM_EX4\n");
            exit(-1);
        }
        for(j = 0; j < 4; j++){
            i = 0;
            while(read(fd, &arg[j][i], 1) > 0 && arg[j][i] != '\n')
                i++;
            arg[j][i] = '\0';
        }
        int firstNum = atoi(arg[1]);
        int operator = atoi(arg[2]);
        int secondNum = atoi(arg[3]);
        close(fd);
        remove("to_srv.txt");
        int result;
        char sResult[10], clientFile[20] = "to_client_";
        fd = open(strcat(strcat(clientFile, arg[0]), ".txt"), O_CREAT | O_RDWR, 777);
        if(fd == -1){
            printf("ERROR_FROM_EX4\n");
            exit(-1);
        }
        if(secondNum == 0 && operator == 4){
            write(fd, "NaN", 3);
            close(fd);
            kill(atoi(arg[0]), SIGUSR2);
            exit(1);
        }
        switch (operator) {
            case 1:
                result = firstNum + secondNum;
                break;
            case 2:
                result = firstNum - secondNum;
                break;
            case 3:
                result = firstNum * secondNum;
                break;
            case 4:
                result = firstNum / secondNum;
                break;
            default:
                printf("Error, Invalid Operator\n");
                exit(-1);
        }
        sprintf(sResult, "%d", result);
        write(fd, sResult, strlen(sResult));
        close(fd);
        kill(atoi(arg[0]), SIGUSR2);
        exit(1);
   }
}

//handler for alarm signal
void alarmHandler(){
    printf("The server was closed because no response was received for the last 60 seconds\n");
    while (wait(NULL) != -1);
    exit(1);
}

//define signals and wait in endless while loop to get one.
int main(){
    signal(SIGUSR1, handler);
    signal(SIGALRM, alarmHandler);
    while(1){
        alarm(60);
        pause();
    }
    return 0;
}
