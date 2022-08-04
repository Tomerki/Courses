#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define LINE_BREAK '/'
#define FALSE 0
#define TRUE 1
#define NUMS_SIZE 10
#define SIZE 5

/***********************
* Name: Tomer Hadar
* ID: 207651027
* Group: 01
* Assignment: ass4
***********************/

void createBoard(char board[][SIZE * SIZE], char str[]);
void printBoard(char board[][SIZE * SIZE]);
void boardSpacing(char board[][SIZE * SIZE]);
void makeMove(char board[][SIZE * SIZE], char move[]);
int checkStr(char str[]);
int testBoard(char board[][SIZE * SIZE]);
int isSameBoard(char board1[][SIZE * SIZE], char board2[][SIZE * SIZE]);
void completeBoard(char board[][SIZE * SIZE]);
int checkCompleteBoard(char board[][SIZE * SIZE]);
void zeroArray(int arr[], int size);


/******************
* Function Name: 
    createBoard
* Input: 
    gets a matrix without any value and a string. 
* Output: 
    void function,doesnt return a value.
* Function Operation: 
    first, the function send the string to check if its legal according 
    our suduku rules.
    if the string ok, we send the matrix to function that puts spaces inside all the matrix indexes,
    and that because - when we see a letter that indicate on an empty index we just need to promote
    the varible (j) that indicate on the colums according the letter ascii value.
    the function puts the values ​​of the string it receives into the matrix using a while loop.
    the while loop continues until the string reaches his last index (\0).
    1.) when we see '/' we promote the variable (i) that indicate on the rows by 1 and initialize the variable (j)
        that indicate on the colums.
    2.) when we see a letter we promote the variable that indicate on the colums according 
        the ascii value of that letter.
    3.) when we see a number we just put it in the matrix.
******************/
void createBoard(char board[][SIZE * SIZE], char str[])
{
    int i = 0, j = 0, k = 0;
    if (!checkStr(str))
        return;
    boardSpacing(board);
    while (str[k] != '\0')
    {
        if (str[k] == LINE_BREAK)
        {
            i++;
            j = 0;
        }
        else if (str[k] >= 'a' && str[k] <= ('a' + SIZE * SIZE - 1))
            j += str[k] - 'a' + 1;
        else
        {
            board[i][j] = str[k];
            j++;
        }
        k++;
    }
    return;
}
/******************
* Function Name: 
    checkStr.
* Input: 
    gets a string.
* Output: 
    returns int- 0 or 1- TRUE or FALSE.
* Function Operation: 
    the function checks all the conditions for legal board as the description of the istructions.
    the function using a while loop that goes until \0, the function checks if there are enough '\' 
    according the suduku size.
    when the function see a letter, its check if there is enough place in the row for num of
    spaces according the ascii value of the letter ( [the letter]-'a'+1= number of spaces).
    if there is at least 1 ilegal char the function print Error.
  
******************/
int checkStr(char str[])
{
    int i = 0, k = 0, counter = 0;
    while (str[i] != '\0')
    {
        if (str[i] == LINE_BREAK)
        {
            counter++;
            if (k > SIZE * SIZE || counter > SIZE * SIZE - 1)
            {
                printf("Error\n");
                return FALSE;
            }
        }
        else if ((str[i] >= 'a') && str[i] <= ('a' + SIZE * SIZE - 1))
        {
            if (SIZE * SIZE - k < str[i] - 'a' + 1)
            {
                printf("Error\n");
                return FALSE;
            }
        }
        if (k > SIZE * SIZE - 1 || str[i] == LINE_BREAK)
            k = 0;
        else
            k++;
        i++;
    }
    if (counter != (SIZE * SIZE - 1))
    {
        printf("Error\n");
        return FALSE;
    }
    else
        return TRUE;

}
/******************
* Function Name: 
    boardSpacing
* Input:
    gets a matrix.
* Output:
    void function doesnt return a value.
* Function Operation:
    the function using a for loop to initialize the board with spaces in all the indexes.
******************/
void boardSpacing(char board[][SIZE * SIZE])
{
    int i, j;
    for (i = 0; i < SIZE * SIZE; i++)
    {
        for (j = 0; j < SIZE * SIZE; j++)
            board[i][j] = ' ';
    }
    return;
}
/******************
* Function Name:
    makeMove
* Input:
    the function gets a matrix that contain a suduku board and a string that indicate on praticular move 
    in the suduku board.
* Output:
    void function doesnt return a value.
* Function Operation:
    first, the function checks the length of the string and save the result inside a variable
    that able us to compare the length of the string, to the correct length.
    then with strtok function we check which move we should do.
    after we get the move we go inside the appropriate condition and check there if the length is legal.
    after that we using two pointers that help us using the strtok function and checks if the move
    that we got is legal according our suduku rules, if the string passed all the tests we doing The requested move.
    and there is something ilegal the function stops and print the screen Error.
******************/
void makeMove(char board[][SIZE * SIZE], char move[])
{
    int i = 0, j = 0, length;
    int replaceAllLength = 14, changeLength = 12, addLength = 9, deleteLength = 10;
    char* token, *saveToken;
    length = strlen(move);
    token = strtok(move, ",");
    if (!strcmp(move, "replaceAll"))
    {
        if (length != replaceAllLength)
        {
            printf("Error\n");
            return;
        }
        token = strtok(NULL, ",");
        saveToken = token;
        if (*token == ' ' || *token == LINE_BREAK || (*token >= 'a' && *token <= 'a' + SIZE * SIZE - 1))
        {
            printf("Error\n");
            return;
        }
        else
        {
            token = strtok(NULL, ",");
            if (*token == ' ' || *token == LINE_BREAK || (*token >= 'a' && *token <= 'a' + SIZE * SIZE - 1))
            {
                printf("Error\n");
                return;
            }
            else
            {
                for (i = 0; i < SIZE * SIZE; i++)
                {
                    for (j = 0; j < SIZE * SIZE; j++)
                    {
                        if (*saveToken == board[i][j])
                            board[i][j] = *token;
                    }
                }
            }
        }
    }
    else if (!strcmp(move, "change"))
    {
        if (length != changeLength)
        {
            printf("Error\n");
            return;
        }
        token = strtok(NULL, ",");
        saveToken = strtok(NULL, ",");
        //saving the indexes we should change.
        if ((*token >= '0' && *token < (SIZE * SIZE + '0')) && (*saveToken >= '0' && *saveToken < (SIZE * SIZE + '0')))
        {
            i = *token - '0';
            j = *saveToken - '0';
        }
        else
        {
            printf("Error\n");
            return;
        }
        token = strtok(NULL, ",");
        if (*token == ' ' || *token == LINE_BREAK || (*token >= 'a' && *token <= 'a' + SIZE * SIZE - 1))
        {
            printf("Error");
            return;
        }
        if (board[i][j] != ' ')
            board[i][j] = *token;
        else
        {
            printf("Error\n");
            return;
        }
    }
    else if (!strcmp(move, "add"))
    {
        if (length != addLength)
        {
            printf("Error\n");
            return;
        }
        token = strtok(NULL, ",");
        saveToken = strtok(NULL, ",");
        if ((*token >= '0' && *token < SIZE * SIZE + '0') && (*saveToken >= '0' && *saveToken < SIZE * SIZE + '0'))
        {
            i = *token - '0';
            j = *saveToken - '0';
        }
        else
        {
            printf("Error");
            return;
        }
        token = strtok(NULL, ",");
        if (*token == ' ' || *token == LINE_BREAK || (*token >= 'a' && *token <= 'a' + SIZE * SIZE - 1))
        {
            printf("Error");
            return;
        }
        else if (board[i][j] == ' ')
            board[i][j] = *token;
        else
        {
            printf("Error");
            return;
        }
    }
    else if (!strcmp(move, "delete"))
    {
        if (length != deleteLength)
        {
            printf("Error\n");
            return;
        }
        token = strtok(NULL, ",");
        saveToken = strtok(NULL, ",");
        if ((*token >= '0' && *token < SIZE * SIZE + '0') && (*saveToken >= '0' && *saveToken < SIZE * SIZE + '0'))
        {
            i = *token - '0';
            j = *saveToken - '0';
        }
        else
        {
            printf("Error\n");
            return;
        }
        if (board[i][j] != ' ')
            board[i][j] = ' ';
        else
            printf("Error\n");
    }
    else
    {
        printf("Error");
        return;
    }
}
/******************
* Function Name:
    printBoard
* Input:
    the function gets a matrix that contains the suduku board.
* Output:
    void function doesnt return a value.
* Function Operation:
    the function using two for loop to print the board and inside the loops 
    there is two conditions that say when we should print the | for the board.
******************/
void printBoard(char board[][SIZE * SIZE])
{
    int i, j;
    for (i = 0; i < SIZE * SIZE; i++)
    {
        for (j = 0; j < SIZE * SIZE; j++)
        {
            printf("%c", board[i][j]);
            if ((j + 1) % SIZE == 0 && (j + 1) < SIZE * SIZE)
                printf(" | ");
        }
        printf("\n");
        if ((i + 1) % SIZE == 0 && (i + 1) < SIZE * SIZE)
            printf("\n");
    }
    printf("\n");
}
/******************
* Function Name:
    testBoard
* Input:
    the function gets a matrix that contains the suduku board.
* Output:
    returns int- 1 if the board legal according the suduku rules
    and returns 0 if found the same value in the same row/colum/square.
* Function Operation:
    first, the function using three for loop that checks if there is a duplicates of values
    in every row/colum.
    but if there is an empty index its ok and the loop continues.
    secondly, after checking that all rows and colums are legal, the function checks 
    if there is a duplicates of values in every sqare on the suduku board, and its doing it 
    with four for loop and an array- the array go from index 1 to 9 and puts 1 in every index according the number
    for example- if the number 8 appears on the board so we put 1 in index 8 in the array, then if the loop
    see again in the same board the number 8 and the index 8 is already with 1 so its an error!
    every sqare we send the array to a function for initialize it again with zeros.
    if all the checks went ok, so the function return 1.
******************/
int testBoard(char board[][SIZE * SIZE])
{
    int i, j, k, r;
    int numArray[NUMS_SIZE];
    for (i = 0; i < SIZE * SIZE; i++)
    {
        for (j = 0; j < SIZE * SIZE; j++)
        {
            for (k = j + 1; k < SIZE * SIZE; k++)
            {
                if ((board[k][i] < '1' || board[k][i] > '9') && board[k][i] != ' ')
                    return FALSE;
                if (board[j][i] != ' ' && board[j][i] == board[k][i])
                    return FALSE;
                if (board[i][j] != ' ' && board[i][j] == board[i][k])
                    return FALSE;
            }
        }
    }
    for (i = 0; i < SIZE * SIZE; i += SIZE)
    {
        for (j = 0; j < SIZE * SIZE; j += SIZE)
        {
            zeroArray(numArray, NUMS_SIZE);
            for (r = i; r < (i + SIZE); r++)
            {
                for (k = j; k < (j + SIZE); k++)
                {
                    if (board[r][k] != ' ')
                    {
                        if (numArray[board[r][k] - '0'] == FALSE)
                            numArray[board[r][k] - '0'] = TRUE;
                        else
                            return FALSE;
                    }
                }
            }
        }
    }
    return TRUE;
}
/******************
* Function Name:
    zeroArray
* Input:
    function gets an array and its size.
* Output:
    void function doesnt return a value
* Function Operation:
    the function gets an array and initialize it with zeros.
******************/
void zeroArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = FALSE;
}
/******************
* Function Name:
    isSameBoard
* Input:
    gets two matrices that contains suduku boards.
* Output:
    returns int - 1 if the two matrices equal in every index, and 0 if even found one inequality index value.
* Function Operation:
    the function using two for loop the compare index by index of the two matrices and an if statement that
    say- if found at least 1 inequality indexes print the appropriate index and return 0
    but if the two matrices are equal, the function returns 1.
******************/
int isSameBoard(char board1[][SIZE * SIZE], char board2[][SIZE * SIZE])
{
    int indexRow, indexCol;
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        for (int j=0; j<SIZE*SIZE;j++)
            if (board1[i][j] != board2[i][j])
            {
                indexRow = i;
                indexCol = j;
                printf("Found inequality on row %d col %d.\n", indexRow, indexCol);
                return FALSE;
            }
    }
    return TRUE;
}
/******************
* Function Name:
    completeBoard
* Input:
    the function gets a matrix that contains a suduku board that almost completed.
* Output:
    void function doesnt return a value.
* Function Operation:
    first, the function send the suduku board it gets to testboard function- to check that the
    board is completable and than send it to another function that check if there are duplicates 
    of empty spots in the same row/colum/sqare.
    after we know that the board is legal
    we calculate the maximum sum of every row by a for loop and save it two variable.
    then we go inside two for loop with conditions indise them, first, we are looking
    for an empty index, if we found, we initialize the indicator variable to 1 and save the empty indexes 
    inside two variable.
    else, if the index isnt empty we calculate the sum of the same row, than, we can know
    which number is missing because we have the maximum sum and the corrent row sum.
    so, if the indicator is 1 and we arrived to the end of the row, we know that we found an empty index
    we calculte the missing number, using the ascii table to convert int to char and put the 
    missing value inside the empty index- then initialize again the sum, theTempRow sum and the indicator.
    if the row isnt empty at all, we just initialize the temp sum again with zero.
******************/
void completeBoard(char board[][SIZE * SIZE])
{   
    int i,j,sumTempRow=0,saveSum=0,sum=0,indicator=0,emptyRowIndex,emptyColIndex;
    if (!testBoard(board))
    {
        printf("Error\n");
        return;
    }
    if (!checkCompleteBoard(board))
    {
        printf("Error\n");
        return;
    }
    for (i = 1; i <= SIZE * SIZE; i++)
        sum += i;
    saveSum = sum;
    for (i = 0; i < SIZE * SIZE; i++)
    {
        for (j = 0; j < SIZE * SIZE; j++)
        { 
            if (board[i][j] == ' ')
            {
                indicator = 1;
                emptyRowIndex = i;
                emptyColIndex = j;
            }
            else
            {
                sumTempRow += board[i][j];
                sumTempRow -= '0';
            }
            if (j == SIZE * SIZE - 1 && indicator == 1)
            {
                sum -= sumTempRow;           
                sum += '0';
                board[emptyRowIndex][emptyColIndex] = sum;
                sum = saveSum;
                indicator = 0;
                sumTempRow = 0;
            }
            else if (j == SIZE * SIZE - 1 && indicator == 0)
                sumTempRow = 0;
        }
    }        
}
/******************
* Function Name:
    checkCompleteBoard
* Input:
    gets a matrix that contain the suduku board from completeBoard function. 
* Output:
    return int- 1 if all the board is legal, 0 if found duplicates of empty indexes in the same row/colum/square.
* Function Operation:
    the function checks for completeboard function if there are more than 1 empty index
    in the same row/colum/sqare.
    its doing it by 3 for loop that checks every row and colum.
    and them using four for loop to check duplicates of an empty indexes in the same square.
    if didnt find any duplicates, its return 1, else zero.
******************/
int checkCompleteBoard(char board[][SIZE * SIZE])
{
    int i, j, k, r, counter = 0;
    for (i = 0; i < SIZE * SIZE; i++)
    {
        for (j = 0; j < SIZE * SIZE; j++)
        {
            for (k = j + 1; k < SIZE * SIZE; k++)
            {
                if (board[j][i] == ' ' && board[j][i] == board[k][i])
                    return FALSE;
                if (board[i][j] == ' ' && board[i][j] == board[i][k])
                    return FALSE;
            }
        }
    }
    for (i = 0; i < SIZE * SIZE; i += SIZE)
    {
        for (j = 0; j < SIZE * SIZE; j += SIZE)
        {
            if (counter > 1)
                return FALSE;
            counter = 0;
            for (r = i; r < (i + SIZE); r++)
            {
                for (k = j; k < (j + SIZE); k++)
                {
                    if (board[r][k] == ' ')
                        counter++;
                }
            }
        }
    }
    return TRUE;
}
