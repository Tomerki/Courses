//Tomer Hadar 207651027
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct commandHistory{
    char command[100];
    int command_pid;
}typedef commandHistory;



void DefineEnvironmentVariables(int len, char** pathArray) {
    char* path = getenv("PATH");
    int i;
    for(i = 1; i < len; i++){
        strcat(path, ":");
        strcat(path, pathArray[i]);
    }
    setenv("PATH", path, 0);
}

void getArguments(char* command, char* arg[]){
    char* token = strtok(command, " ");
    int i=1;
    while(token){
        token = strtok(NULL, " ");
        *(arg+i) = token;
        i++;
    }
}

void PrintAllCommandHistory(commandHistory history[100], int len){
    int i = 0;
    while(i < len){
        printf("%d\t", history[i].command_pid);
        printf("%s\n", history[i].command);
        i++;
    }
}

void ActiveShell(){
    commandHistory myHistory[100];
    int commandNumber = 0;


    while(1){
        int checkError;
        printf("$ ");
        fflush(stdout);
        scanf(" %[^\n]", myHistory[commandNumber].command);
        myHistory[commandNumber].command_pid = getpid();
        char userCommand[100];
        strcpy(userCommand, myHistory[commandNumber].command);
        int status;
        char* arg[100];
        getArguments(userCommand, arg);
        char* commandName = strtok(userCommand, " ");
        arg[0] = commandName;
        if(!strcmp(commandName, "cd")){
            checkError = chdir(arg[1]);
            if(checkError == -1){
                perror("chdir failed");
            }
        }
        else if(!strcmp(commandName, "history")){
            PrintAllCommandHistory(myHistory, commandNumber + 1);
        }
        else if(!strcmp(commandName, "exit")){
            exit(1);
        }
        else{
            pid_t pid = fork();
            if(pid == -1){
                perror("fork failed");
            }
            else if(!pid){
                checkError = execvp(commandName, arg);
                if(checkError == -1){
                    perror("execvp failed");
                }
                exit(1);
            }
            else{
                checkError = wait(&status);
                if(checkError == -1){
                    perror("wait failed");
                }

            }
            myHistory[commandNumber].command_pid = pid;
        }
        commandNumber++;
    }
}

int main(int argc, char **argv){
    if(argc > 1)
        DefineEnvironmentVariables(argc, argv);
    ActiveShell();
    return 0;
}