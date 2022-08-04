#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
tomer hadar
207651027
01
ex2/ass2
*/



int main()
{
	char option = 1;
	do
	{
		printf("Choose an option:\n1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n\
4. Pow2\n5. Different bits\n6. Add\n7. Multiply\n0. Exit\n"); //print the menu
		scanf(" %c", &option); //save the user input in the variable adress
		
		option -= 48; //because we use char we need to act according the ascii table
		if (option > 0 && option <= 7)// condition for the switch
		{
			switch (option)
			{
			case 1:;
				int Rsize, i, j;
				printf("Enter the sides length:\n");
				scanf("%d", &Rsize);

				for (i = 1; i <= Rsize; i++)  //loops that print the first half rhombus
				{
					for (j = 1; j <= Rsize - i; j++)
						printf(" ");
					printf("/");

					for (j = 1; j < i; j++)
						printf(" ");
					printf("*");

					for (j = 1; j < i; j++)
						printf(" ");
					printf("\\\n");
				}
				printf("|");  //print the middle of the rhombus
				for (i = 1; i < Rsize; i++)
					printf(" ");
				printf("+");
				for (i = 1; i < Rsize; i++)
					printf(" ");
				printf("|\n");
				for (i = 1; i <= Rsize; i++) // Loops that print the second half rhombus
				{
					for (j = 1; j < i; j++)
						printf(" ");
					printf("\\");
					for (j = 1; j <= Rsize - i; j++)
						printf(" ");
					printf("*");
					for (j = 1; j <= Rsize - i; j++)
						printf(" ");
					printf("/\n");
				}
				break;
			case 2:;
				char base20;
				long int result, power;
				int indicator;
				indicator = 1;
				i = 0;
				result = 0, power = 1;
				printf("Enter a reversed number in base 20:\n");
				scanf(" %c",&base20);
				while (base20 != '\n')
				{
					if (base20 >= 'A' && base20 <= 'J')   //every if take care of extreme case
					{
						base20 -= 55;
						result += base20 * power;
						power *= 20;
					}
					else if (base20 >= 'a' && base20 <= 'j')
					{
						base20 -= 87;
						result += base20 * power;
						power *= 20;
					}
					else if (base20 >= '0' && base20 <= '9')
					{
						base20 -= 48;
						result += base20 * power;
						power *= 20;
					}
					else
					{
						printf("Error! %c is not a valid digit in base 20\n", base20); //if enter the else, indicator=0 and prevent 
						indicator = 0;                                                 // indicator prevent printing the result
					}
					scanf("%c", &base20);
					if (indicator && base20 == '\n')// if the input ends and indicator still true print the result
					{
						printf("%d\n", result);
						break;
					}
				}
				break;
			case 3:;
				int base;
				char num;
				result = 0;
				i = 1;
				indicator = 1;
				
				//asking input from the user
				printf("Enter a base (2-10):\n");
				scanf("%d", &base);
				printf("Enter a reversed number in base %d:\n", base);
				scanf(" %c", &num);
				while (num != '\n')
				{
					num -= 48; //num become a number (0)
					if (num >= 0 && num < base)
					{
						result += num * i; //num*exponent acorrding the index (i represent the index)
						i *= base;
					}
					else
					{
						num += 48;
						printf("Error! %c is not a vaild digit in base %d\n", num, base);// if the input isnt what we asking
						indicator = 0; 
					}
					scanf("%c", &num);
				}
				if (indicator)
					printf("%d\n", result);
				break;
			case 4:;
				int num1, temp;
				printf("Enter a number:\n");
				scanf("%d", &num1);
				temp = num1 & (num1 - 1); //save the & bitwise action inside temp
				if ((temp == 0) && num1 != 0) //checking if the number is power of 2
					printf("%d is a power of 2\n", num1);
				else
					printf("%d is not a power of 2\n", num1);
				break;
			case 5:;
				int num2, num3, counter;
				unsigned int check, counter1, temp1; //unsigned for checking negative numbers
				counter = 0;
				counter1 = 0;
				printf("Enter two numbers:\n");
				scanf("%d%d", &num2, &num3);
				temp1 = num2 ^ num3;
				while (temp1 != 0)// checking how much bits the number has
				{
					temp1 /= 2;
					counter++;
				}
				temp1 = num2 ^ num3;
				for (i = 0; i < counter; i++)// checking how much time the number 1 apears
				{
					check = temp1 % 2;
					temp1 /= 2;
					if (check == 1)
						counter1++;
				}
				printf("There are %d different bits\n", counter1);
				break;
			case 6:;
				i = 0;
				printf("Enter two numbers:\n");
				scanf("%d%d", &num2, &num3);
				if (num2 < 0)//whats happen while num2<0
				{
					for (i; i > num2; i--)
						num3--;
					printf("%d\n", num3);
				}
				else if (num3 < 0)//whats happen while num3<0
				{
					for (i; i > num3; i--)
						num2--;
					printf("%d\n", num2);
				}
				else//if both numbers positive/negative
				{
					for (i; i < num2; i++)
						num3++;
					printf("%d\n", num3);
				}
				break;
			case 7:;
				result = 0;
				printf("Enter two numbers:\n");
				scanf("%d%d", &num2, &num3);
				//checking extreme case whats happning in all the possible combinitions
				if ((num2 < 0) && (num3 > 0))
				{
					for (i = 0; i < num3; i++)
						result += num2;
					printf("%d\n", result);
				}
				else if ((num3 < 0) && (num2 > 0))
				{
					for (i = 0; i < num2; i++)
						result += num3;
					printf("%d\n", result);
				}
				else if ((num3 < 0) && (num2 < 0))
				{
					num2 = ~num2;
					num2 += 1;
					for (i = 0; i > num3; i--)
						result += num2;
					printf("%d\n", result);
				}
				else
				{
					for (i = 0; i < num2; i++)
						result += num3;
					printf("%d\n", result);
				}
			}
		}
		else if (option != 0)//if  0<the user input>=7 its print Wrong option
			printf("Wrong option!\n");
	}while (option);// do while loop, the condition is while option is true,or not 0..
return 0;//return for int main function
}
