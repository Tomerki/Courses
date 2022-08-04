#include <stdio.h>
#define BONUS
int indexG;

/******
Name: Tomer Hadar
ID: 207651027
Group 01
ass3
******/

/*************************************************
* Function Name: towerOfHanoi
* Input:
	number of disks and 3 parameter that represent the rods
* Output:
	void function doesnt have a return value.
* Function Operation:
	the function print on the screen the steps 
	that you need to take for solving this problem in a condition for the disks numbers
**************************************************/
void towerOfHanoi(int numDisks, char fromRod, char toRod, char auxRod)
{
	//stop condition - while numDisks not zero continue.
	if (numDisks == 0)
		return;
	//first recrusive call
	towerOfHanoi(numDisks - 1, fromRod, auxRod, toRod);
	printf("Move disk %d from rod %c to rod %c.\n", numDisks, fromRod, toRod);
	//second recrucive call but here every variable gets a diffrent value.
	towerOfHanoi(numDisks - 1, auxRod, toRod, fromRod);
}
/******************
* Function Name:helpPalindrome
* Input: 
	the function gets a string is length and the first index(0)
* Output:
	the function return int value return 1 if the word is palindrome, else return 0.
* Function Operation:
	the function compare the value of the counter indexs, if the value
	isnt the same shes stop and return 0 that indicate the original function for what to print.
******************/
int helpPalindrome(char str[], int len, int index) //1.isPalind done :)
{
	//2 stop conditions,1.if the number of letters odd 2. if even 
	if (len == index || len < index)
		return 1;
	if (str[len - 1] != str[index])
		return 0;
	//every recrusive call we promote the indexes from both sides.
	return helpPalindrome(str, len - 1, index + 1);
}
/******************
* Function Name:isPalindrome
* Input:
	gets a string and his length
* Output:
	void function,doesnt return a value.
* Function Operation:
    this function calls another function that help her.
	the function also printing on the screen according the return value of 
	the help function.
******************/
void isPalindrome(char str[], int len)//done :)
{
	int i;
	//enter the return value to a variable
	i = helpPalindrome(str, len, 0);
	//print the result according the return value of the help function
	if (i == 1)
		printf("The reverse of %s is also %s.\n", str, str);
	else
		printf("The reverse of %s is not %s.\n", str, str);
}
/******************
* Function Name:checkAllCombinations
* Input:
	 gets a string consist numbers from 0-2 and the char (?)
	 the length of the string and index 0 to check all the string from his first index 
* Output:
	 void function doesnt return a value
* Function Operation:
	 the function gets the string and where ever there is (?)
	 the function replace it by number and shes doing it from the smallest number to the biggest
	 then the function print out all the combinations that she found.
	 using a global variable that counting how much times the function print the screen
	 and every print indicate that we have another option
	 so this varible help us to print how much combinations we have.
******************/
void checkAllCombinations(char pattern[], int len, int index)
{
	//stop condition id index=len its says that we checked all indexes
	if (index == len)
	{
		printf("%s\n", pattern);
		indexG++;
		return;
	}
	/*****
	on that block we check every index
	if the undex value is (?) we replace it in 0 then in 1 and after that in 2
	and thats how we actully find all the possible combinations.
	*****/
	if (pattern[index] == '?')
	{
		pattern[index] = '0';
		checkAllCombinations(pattern, len, index);
		pattern[index] = '1';
		checkAllCombinations(pattern, len, index);
		pattern[index] = '2';
		checkAllCombinations(pattern, len, index);
		pattern[index] = '?';
	}
	else
		checkAllCombinations(pattern, len, index + 1);
}
/******************
* Function Name: printAllCombinations
* Input:
	gets a string that consist numbers from 0 to 2 and the char (?) and the string length.
* Output:
	void function doesnt return a value
* Function Operation:the function prints to the screen the number of possible combinations
	accordingly the value of the global variable.
******************/
void printAllCombinations(char pattern[], int len)
{
	//calling for help function
	checkAllCombinations(pattern, len, 0);
	printf("Number of combinations is: %d\n", indexG);
	//using a global variable for counting all combinitions.
	indexG = 0;
}
/******************
* Function Name:calculatePower
* Input:
	gets 2 number the first for the base and the second one for the exponent
* Output:
	the function return a double value for bases with negative exponent.
* Function Operation:
	the function multiply the base number in recrusive way, 
	while the exponent is 0 we return 1 and then start to multiply in the base.
	after that return that value to the original function that print it out.
******************/
double calculatePower(long double baseNum, long double powerNum) //1.powRec
{
	if (powerNum == 0)
		return 1;
	else
		return baseNum * calculatePower(baseNum, powerNum - 1);
}
/******************
* Function Name: powRec
* Input:
	the functiongets two numbers
* Output:
	void function doesnt return a value
* Function Operation:
	the function calls a help function and print out the result of the 
	first number to the power of the second number according the result that the help function return.
******************/
void powRec(long int firsrtNum, long int secondNum)
{
	//this condition take care when the exponent is negative number
	if (secondNum >= 0)
	{
		printf("The result is %f.\n", calculatePower(firsrtNum, secondNum));
		return;
	}
	else
	{
		printf("The result is %f.\n", calculatePower((double)1 / firsrtNum, -secondNum));
		return;
	}
}
/******************
* Function Name:checkIfDivisibleBy3
* Input:
	the same number as the original function gets and another varible 
	that check the remainder that left every 2 consecutive numbers .
* Output:
	the function return an int value, actully the functions return 
	the value of the variable that checks the reminder.
* Function Operation:
    the function checks every digit reminder while divided by 3 
	and save the result in the check variable, then, according his value in the end
	the original function knows which message she should print.
******************/
int checkIfDivisibleBy3(long long n, int check1)
{
	if (n == 0)
		return check1;
	if (n % 10 == 1)
	{
		if (check1 == 0)
			check1 = 1;
		else if (check1 == 1)
			check1 = 2;
		else
			check1 = 0;
	}
	else if (n % 10 == 2)
	{
		if (check1 == 0)
			check1 = 2;
		else if (check1 == 1)
			check1 = 0;
		else
			check1 = 1;
	}
	else
		check1 = check1;
	return checkIfDivisibleBy3(n / 10, check1);
}
/******************
* Function Name:isDivisibleBy3
* Input:
	gets a number that consist the digits 1,2,3.
* Output:
	void function doesnt return a value
* Function Operation:
	the function print out whether the number is divisible by 3
	according the return value of the help function.
******************/
void isDivisibleBy3(long long n)
{
	int check1 = 0;
	if (checkIfDivisibleBy3(n, check1) == 0)
		printf("The number %lld is divisible by 3.\n", n);
	else
		printf("The number %lld is not divisible by 3.\n", n);
}
/******************
* Function Name:calculateGcd
* Input:
	gets 2 number
* Output:
	return a int value- actully return the GCD.
* Function Operation:
	the function calculate the GCD between 2 numbers 
	and print out the way she did it.
******************/
int calculateGcd(long int n1, long int n2)
{
	if (!n2)
		return n1;
	printf("%ld*%ld+%ld=%ld(a=%ld,b=%ld)\n", n2, n1 / n2, n1 % n2, n1, n1, n2);
	return calculateGcd(n2, n1 % n2);
}
/******************
* Function Name:gcd
* Input:
	gets 2 numbers
* Output:
	void function doesnt return a value.
* Function Operation:
	the function checks the retun value of the help function
	and take care the case that the GCD is negative.
	then the function print out the GCD .
******************/
void gcd(long int n1, long int n2)
{
	int i;
	long int temp;
	if (n1 < n2)
	{
		temp = n2;
		n2 = n1;
		n1 = temp;
	}
	i = calculateGcd(n1, n2);
	if (i < 0)
		printf("GCD=%d\n", -i);
	else
		printf("GCD=%d\n", i);
}
/******************
* Function Name:checkNumber
* Input:
	the function gets a number a digit and a counter 
* Output:
	int function return how much times the digit apear in the number
* Function Operation:
	the function check every digit in the number compared the 
	digit we asked about to check. doing it by %10 and sparate every time 1 digit from the big number.
******************/
int checkNumber(long long n, int numapear, int counter)// done :)
{
	if (n == 0)
		return counter;
	if (n % 10 == numapear)
		counter++;
	return checkNumber(n / 10, numapear, counter);
}
/******************
* Function Name:countDigit
* Input:
	gets a number and a digit 
* Output:
	void function doesnt return a value.
* Function Operation:
	the function print the screen how much time the digit appear in the number
	accordingly the return value of the help function.
******************/
void countDigit(long long n, int d) //done :)
{
	printf("%lld has %d times %d.\n", n, checkNumber(n, d, 0), d);
}
/******************
* Function Name:isPalindromeIter
* Input:
	gets a string and is length
* Output:
	void function doesnt return a value
* Function Operation:
	the function checks with for loop and compare between
	the last index-last letter to the first index-first letter.
	if they diffrent the function print out that the word isnt a palindrome
	else if every letter equel to the correct letter in the counter index 
	so she print that the word is polindrome.
******************/
void isPalindromeIter(char str1[], int len)
{
	int i,j,check=0;
	//compare the letters on counter indexes
	for (i = 0,j=len-1; i<len-1; i++,j--)
	{
		if (str1[i] != str1[j])
		{
			printf("The reverse of %s is not %s.\n", str1, str1);
			check = 1;
			break;
		}
	}
	if (check == 0)
		printf("The reverse of %s is also %s.\n", str1, str1);
	return;
}
/******************
* Function Name:IsDividedBy3Iter
* Input:
	gets a number
* Output:
	void function doesnt return a value
* Function Operation:
	first, the function check if the number is negative or positive
	then inside the while loop the function checks every digit-if the digit divisible by 3 
	shes countinue else, shes add it to sum- and the varible sum is responsible to save the reminder 
	value that indicate eventually if the number divisble by 3 without a reminder.
******************/
void IsDividedBy3Iter(long long num)
{
	long long int tempNum;
	int sum = 0, checkSum,nega=0;
	if (num > 0)
		tempNum = num;
	else
	{
		tempNum = -num;
		nega = 1;
	}
	//while loop that countinue while tempNum!=0.
	while (tempNum)
	{
		if (tempNum % 10 == 3 || tempNum % 10 == 6 || tempNum % 10 == 9)
			sum += 0;
		else
			sum += tempNum % 10;
		tempNum /= 10;
		/*
		when ever the sum of 2 digits in the number is more then 9
		we check the reminder by divide in 3 and puts the reminder inside sum.
		*/
		if(sum >= 10)
		{
			if (sum == 12 || sum == 15 || sum == 18)
				sum = 0;
			else
			{
				checkSum = sum % 10;
				sum /= 10;
				if (sum + checkSum == 2 || sum + checkSum == 5 || sum + checkSum == 8)
					sum = 2;
				else
					sum = 1;
			}
		}
	}
	//take care the case that number is negative.
	if ((sum == 0||sum==3||sum==6||sum==9)&&nega==0)
		printf("The number %lld is divisible by 3.\n", num);
	else if(nega==0)
		printf("The number %lld is not divisible by 3.\n", num);
	else if((sum == 0 || sum == 3 || sum == 6 || sum == 9) && nega == 1)
		printf("The number %lld is divisible by 3.\n", num);
	else
		printf("The number %lld is not divisible by 3.\n", num);
}
