//Tomer Hadar
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

//function to close files and exit program if some command didn't work, and we need to close files that open.
void exitProgram(int arr[], int len){
    int i;
    for(i = 0; i < len; i++){
        close(arr[i]);
    }
    exit(-1);
}


//write to results.csv all the user results
void writeResults(char *name, int grade, int resultFd) {
    switch (grade) {
        case 1:
            write(resultFd, name, strlen(name));
            write(resultFd, ",100,EXCELLENT\n", 15);
            break;
        case 2:
            write(resultFd, name, strlen(name));
            write(resultFd, ",50,WRONG\n", 10);
            break;
        case 3:
            write(resultFd, name, strlen(name));
            write(resultFd, ",75,SIMILAR\n", 12);
            break;
        default:
            write(resultFd, name, strlen(name));
            write(resultFd, ",10,COMPILATION_ERROR\n", 22);
            break;
    }
}

//run the user program and compare it with the correct output.
int runUserProgram(char pathToFile[150], char pathsArray[3][150], int errorFd, int fdResults) {
    int result = -1, Output, input, gccError, st, num;
    if ((Output = open("outputFile.txt", O_TRUNC | O_RDWR | O_CREAT, 0777)) < 0) {
        write(STDOUT_FILENO, "Error in: open\n", 15);
        int arr[] = {errorFd, fdResults};
        exitProgram(arr, 2);
    }
    if ((input = open(pathsArray[1], O_RDONLY)) < 0) {
        write(STDOUT_FILENO, "Error in: open\n", 15);
        int arr[] = {errorFd, Output, fdResults};
        exitProgram(arr, 3);
    }
    //redirect io to files
    if (dup2(input, 0) == -1) {
        write(STDOUT_FILENO, "Error in: dup2\n", 15);
        int arr[] = {errorFd, Output, input, fdResults};
        exitProgram(arr, 4);
    }
    if (dup2(Output, 1) == -1) {
        write(STDOUT_FILENO, "Error in: dup2\n", 15);
        int arr[] = {errorFd, Output, input, fdResults};
        exitProgram(arr, 4);
    }
    if (dup2(errorFd, 2) == -1) {
        write(STDOUT_FILENO, "Error in: dup2\n", 15);
        int arr[] = {errorFd, Output, input, fdResults};
        exitProgram(arr, 4);
    }
    //fork for compile user program
    pid_t pid = fork();
    if (!pid) {
        char *arg[5] = {"gcc", pathToFile, "-o", "a.out", NULL};
        if (execvp("gcc", arg) == -1) {
            write(STDOUT_FILENO, "Error in: execvp\n", 17);
            exit(-1);
        }
    } else {
        waitpid(pid, &gccError, 0);
        if (!WEXITSTATUS(gccError)) {
            //if compiled then another fork for run the program.
            pid_t childPid = fork();
            if (!childPid) {
                char *arg[2] = {"./a.out", NULL};
                if (execvp("./a.out", arg) == -1) {
                    write(STDOUT_FILENO, "Error in: execvp\n", 17);
                    exit(-1);
                }
            } else {
                waitpid(childPid, NULL, 0);
                //another fork for compare the user output with the correct output
                pid_t child = fork();
                if (!child) {
                    char *arg[4] = {"./comp.out", pathsArray[2], "outputFile.txt", NULL};
                    if (execvp("./comp.out", arg) == -1) {
                        write(STDOUT_FILENO, "Error in: execvp\n", 17);
                        exit(-1);
                    }
                } else {
                    waitpid(child, &st, 0);
                    //extract comp.out return value
                    result = WEXITSTATUS(st);
                }
            }
        } else{
            result = -1;
        }

    }
    close(input);
    close(Output);
    return result;
}


void checkFor_C_File(char path[150], char pathToFiles[3][150], char *userName, int resultFd, int errorsFd) {
    DIR *myDir;
    struct dirent *element;
    char copyPath[150];
    char *search;
    int noFile = 1, grade;
    if ((myDir = opendir(path))) {
        while ((element = readdir(myDir))) {
            struct stat myState;
            if (strcmp(element->d_name, ".") == 0 || strcmp(element->d_name, "..") == 0)
                continue;
            strcpy(copyPath, path);
            strcat(strcat(copyPath, "/"), element->d_name);
            if (!stat(copyPath, &myState)) {
                if (S_ISREG(myState.st_mode)) {
                    if ((search = strrchr(element->d_name, '.')) == NULL)
                        continue;
                    //check if the file is a C file
                    if (!strcmp(".c", search)) {
                        noFile = 0;
                        grade = runUserProgram(copyPath, pathToFiles, errorsFd, resultFd);
                        break;
                    }
                }
            } else {
                write(STDOUT_FILENO, "Error in: stat\n", 15);
                closedir(myDir);
                return;
            }
        }
        if (noFile) {
            write(resultFd, userName, strlen(userName));
            write(resultFd, ",0,NO_C_FILE\n", 13);
            closedir(myDir);
        } else {
            writeResults(userName, grade, resultFd);
            closedir(myDir);
        }
    }
}

//go over all users directory one by one and handle them.
void scanUsersDirectory(char pathArray[3][150]) {
    DIR *myDir;
    struct dirent *element;
    int resultFd, errorsFd;
    //open errors File
    if ((errorsFd = open("errors.txt", O_WRONLY | O_CREAT, 0777)) < 0) {
        write(STDOUT_FILENO, "Error in: open\n", 15);
        int arr[] = {errorsFd};
        exitProgram(arr, 1);
    }
    //open Results file
    if ((resultFd = open("results.csv", O_APPEND | O_WRONLY | O_CREAT, 0777)) < 0) {
        write(STDOUT_FILENO, "Error in: open\n", 15);
        int arr[] = {resultFd, errorsFd};
        exitProgram(arr, 2);
    }
    if ((myDir = opendir(pathArray[0]))) {
        while ((element = readdir(myDir))) {
            char copyPath[150];
            struct stat myState;
            strcpy(copyPath, pathArray[0]);
            strcat(strcat(copyPath, "/"), element->d_name);
            if (!stat(copyPath, &myState)) {
                if (S_ISDIR(myState.st_mode)) {
                    if (strcmp(element->d_name, ".") != 0 && strcmp(element->d_name, "..") != 0) {
                        checkFor_C_File(copyPath, pathArray, element->d_name, resultFd, errorsFd);
                    }
                }
            } else
                write(STDOUT_FILENO, "Error in: stat\n", 15);
        }
    }
    //close files
    close(resultFd);
    close(errorsFd);
    closedir(myDir);
}


void getPathFromConf(char *pathToConf, char arr[3][150]) {
    char readChar;
    int fd, i = 0, rd, j;
    if ((fd = open(pathToConf, O_RDONLY)) < 0) {
        write(STDOUT_FILENO, "Error in: open\n", 15);
        exit(-1);
    }
    for (j = 0; j < 3; j++) {
        while ((rd = read(fd, &readChar, 1) > 0) && (readChar != '\n')) {
            if (rd == -1) {
                write(STDOUT_FILENO, "Error in: open\n", 15);
                exit(-1);
            }
            arr[j][i++] = readChar;
        }
        arr[j][i] = '\0';
        i = 0;
    }
    //close file
    close(fd);
}


void checkValidPaths(char pathArray[3][150]) {
    DIR *userDir = opendir(pathArray[0]);
    if (!userDir) {
        write(2, "Not a valid directory\n", 22);
        exit(-1);
    }
    closedir(userDir);
    if (access(pathArray[1], F_OK)) {
        write(2, "Input file not exist\n", 21);
        exit(-1);
    }
    if (access(pathArray[2], F_OK)) {
        write(2, "Output file not exist\n", 22);
        exit(-1);
    }

}

//int argc, char **argv
int main(int argc, char **argv) {
    char pathArray[3][150];
    getPathFromConf(argv[1], pathArray);
    checkValidPaths(pathArray);
    scanUsersDirectory(pathArray);
    remove("outputFile.txt");
    return 0;
}
