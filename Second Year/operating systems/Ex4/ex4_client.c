//Tomer Hadar
#include <sys/fcntl.h>
#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "string.h"
#include "stdlib.h"



void handler(){
    alarm(0);
    int fd;
    char result[11] = {0}, myPid[6], fileName[20] = "to_client_";
    int pid = getpid();
    sprintf(myPid, "%d", pid);
    strcat(strcat(fileName, myPid), ".txt");
    fd = open(fileName, O_RDONLY, 777);
    if(fd == -1){
        printf("ERROR_FROM_EX4\n");
        exit(-1);
    }
    int i = 0;
    while (read(fd, &result[i++], 1));
    close(fd);
    remove(fileName);
    if(!strcmp(result, "NaN")){
        printf("CANNOT_DIVIDE_BY_ZERO\n");
        exit(1);
    }
    printf("%s\n", result);
}


void handleAlarm(){
    printf("Client closed because no response was received from the server for 30 seconds");
    exit(1);
}

//check validation of command line arguments.
int Valid(int len, char* argv[]){
    if(len != 5)
        return 0;
    int i,j;
    for(i = 1; i < 5; i++){
        for(j = 0; j < strlen(argv[i]); j++){
            if((argv[i][j] >= '0' && argv[i][j] <= '9') || (j == 0 && argv[i][j] == '-'))
                continue;
            else
                return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]){
    if(!Valid(argc, argv)){
        printf("ERROR_FROM_EX4\n");
        exit(-1);
    }
    char arr[3][10];
    int i;
    //set signals and handlers.
    signal(SIGUSR2, handler);
    signal(SIGALRM, handleAlarm);
    int fd, seconds, counter = 0;
    char myPid[7];

    while(counter < 10){
        if(!access("to_srv.txt", F_OK)){
            seconds = (rand() % 6) + 1;
            sleep(seconds);
            counter++;
        } else
            break;
    }

    if(counter == 10){
        printf("ERROR_FROM_EX4\n");
        exit(1);
    }
    for ( i = 0; i < 3; i++) {
        strcpy(arr[i], argv[i + 2]);
    }
    fd = open("to_srv.txt", O_CREAT | O_RDWR, 777);
    if(fd == -1){
        printf("ERROR_FROM_EX4\n");
        exit(-1);
    }
    pid_t pid = getpid();
    sprintf(myPid, "%d", pid);
    strcat(myPid, "\n");
    strcat(arr[0],"\n");
    strcat(arr[1],"\n");
    strcat(arr[2],"\n");
    write(fd, myPid, strlen(myPid));
    write(fd, arr[0], strlen(arr[0]));
    write(fd, arr[1], strlen(arr[1]));
    write(fd, arr[2], strlen(arr[2]));
    kill(atoi(argv[1]), SIGUSR1);
    alarm(30);
    pause();
    return 0;
}
