#include "ex5.h"
/***********************
* Tomer Hadar
* 207651027
* 01
* ex5
* **********************/
/******************
in the main i define array of courses that im going to save there
all the courses in the system, inside every course i have varible from struct LIST type
that through this variable we can acsses to the head pointer or the tail that point to the
first node and the last one in the list.
and we ask for the user to pick his operation, than by a while loop and switch case
we nevigate the program to the right functions.
******************/
int main()
{
	char choice, tempString[MAX_LENGTH];
	courses_t courseList[MAX_LENGTH];
	initializeNull(courseList);
	//print the menu
	printMenu();
	//get the user first operation in choice variable.
	scanf(" %c", &choice);
	while (1)
	{
		//in every switch case we using scanf to save the user string.
		switch (choice)
		{
		case '1':
			scanf(" %[^\n]", tempString);
			checkClassName(tempString, courseList);
			printChoosing(&choice);
			break;
		case '2':
			scanf(" %[^\n]", tempString);
			checkStudent(tempString, courseList);
			printChoosing(&choice);
			break;
		case '3':
			scanf(" %[^\n]", tempString);
			checkIfLegal(tempString, courseList);
			printChoosing(&choice);
			break;
		case '4':
			scanf(" %[^\n]", tempString);
			checkCourseNumber(tempString, courseList);
			printChoosing(&choice);
			break;
		//here we have a menu inside the case, so we print it out and than inside the function do scanf.
		case '5':
			printCalculationMenu(courseList);
			printChoosing(&choice);
			break;
		case '6':
			printMenu();
			scanf(" %c", &choice);
			break;
		//if choosing 0 we free all the mallocs and than exit the program.
		case '0':
			freeAll(courseList);
		//if the user choose an option that doesnt appear in the menu.
		default:
			printf("Error: unrecognized operation.\n");
			printChoosing(&choice);
		}
	}
	return 0;
}
