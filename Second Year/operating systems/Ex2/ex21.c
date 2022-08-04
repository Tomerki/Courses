//Tomer Hadar 207651027
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int checkEnd(int fileDes, char charToRead){
    int check = 0;
    do{
        if(check == -1)
            return -1;
        if(charToRead != ' ' && charToRead != '\n')
            return 2;
    }while((check = read(fileDes, &charToRead, 1)) > 0);
    return 3;
}

//check if the byte its space or enter.
int checkChar(char check1, char check2, int* res){
    if(check1 == check2)
        return 4;
    else if((check1 == (check2 - 32)) || ((check1 - 32) == check2) || (check1 == '\n'  && check2 == ' ') || (check1 == ' '  && check2 == '\n')){
        *res = 3;
        return 3;
    }
    else if(check1 == ' ' || check1 == '\n'){
        *res = 3;
        return 1;
    }
    else if(check2 == ' ' || check2 == '\n'){
        *res = 3;
        return 2;
    }
    return 0;
}


int checkDiff(char* first, char* second) {
    long readFirst, readSecond;
    int firstFD, secondFD, indicator = 4, res = 1;
    char firstCompByte, secondCompByte;
    if ((firstFD = open(first, O_RDONLY)) < 0)
        exit(-1);
    if ((secondFD = open(second, O_RDONLY)) < 0)
        exit(-1);
    //do-while loop reading byte after byte and compare the bytes from the different files.
    do {
        //according to the indicator value we know from which files we need to read.
        if (indicator >= 3) {
            if(((readFirst = read(firstFD, &firstCompByte, 1)) == -1) || ((readSecond = read(secondFD, &secondCompByte, 1)) == -1)){
                write(STDOUT_FILENO, "Error in: read\n", 15);
                close(firstFD);
                close(secondFD);
                exit(-1);
            }
        } else if (indicator == 1) {
           if((readFirst = read(firstFD, &firstCompByte, 1)) == -1){
               write(STDOUT_FILENO, "Error in: read\n", 15);
               close(firstFD);
               close(secondFD);
               exit(-1);
           }
        } else if (indicator == 2) {
            if((readSecond = read(secondFD, &secondCompByte, 1)) == -1){
                write(STDOUT_FILENO, "Error in: read\n", 15);
                close(firstFD);
                close(secondFD);
                exit(-1);
            }
        } else {
            return 2;
        }

        if (readFirst > 0 && readSecond > 0) {
            indicator = checkChar(firstCompByte, secondCompByte, &res);
        }
        else if(readFirst > 0){
            if((res = checkEnd(firstFD, firstCompByte)) != -1)
                return res;
            else{
                write(STDOUT_FILENO, "Error in: read\n", 15);
                close(firstFD);
                close(secondFD);
                exit(-1);
            }
        }
        else if(readSecond > 0){
            if((res = checkEnd(secondFD, secondCompByte)) != -1)
                return res;
            else{
                write(STDOUT_FILENO, "Error in: read\n", 15);
                close(firstFD);
                close(secondFD);
                exit(-1);
            }
        }
        //while loop last if we can read from at least one of the files.
    }while (readFirst > 0 || readSecond > 0);
    close(firstFD);
    close(secondFD);
    return res;
}


int main(int argc, char **argv){
    //check if argv legal
    if(argc < 3){
        printf("Not Enough Parameters");
        exit(-1);
    }
    return checkDiff(argv[1], argv[2]);
}