#include "ex5.h"
/***********************
* Tomer Hadar 
* 207651027
* 01
* ex5
***********************/
int isEmptyList(courses_t courseList[], int class);
int ifLegalData(char* studName, char* courseNumber, char* courseGrade, courses_t courseList[]);
/******************
* Function Name:
	freeAll
* Input:
	function gets array of courses
* Output:
	void function doesnt return a value
* Function Operation:
	the function go over every course and go inside the linked list, than free all the 
	alloction that we made during our program.
******************/
void freeAll(courses_t courseList[])
{
	//pointer to go over the link list
	student_t* freeStudent;
	//for loop to go over all the courses in the array
	for (int i = 0; i < MAX_COURSES; i++)
	{
		//check if there are student in the course
		if (isEmptyList(courseList, i) != FALSE)
		{
			freeStudent = courseList[i].student.head;
			//with while loop free all the nodes until freeStudent is NULL
			while (freeStudent != NULL)
			{
				courseList[i].student.head = (student_t*)freeStudent->next;
				free(freeStudent);
				freeStudent = courseList[i].student.head;
			}
		}
	}
	//exit the program after free all the memory we allocated
	exit(1);
}
/**************Exercise 1*******************/
/******************
* Function Name:
	printMenu
* Input:
	doesnt get any parameter
* Output:
	void function, doesnt return a value
* Function Operation:
	the function print the menu
******************/
void printMenu()
{
	printf("Please select an operation:\n\t0. Exit.\n\t1. Insert or update a class.\n\t2. Insert or update a student.\
\n\t3. Remove a student from classes.\n\t4. Print a class.\n\t5. Print all classes with their computed scores.\
\n\t6. Print the menu.\n");
	return;
}
/******************
* Function Name:
	printChoosing
* Input:
	the function get an adress of char variable
* Output:
	void function,doesnt return a value
* Function Operation:
	the function print a message that ask from the user to choose the next operation.
	and save the user choice inside the choice pointer that point the choice variable on the stack. 
******************/
void printChoosing(char* choice)
{
	printf("Select the next operation (insert 6 for the entire menu):\n");
	scanf(" %c", choice);
}
/******************
* Function Name:
	ifCourseExists
* Input:
	the function gets an array of structs from course struct kind, the array size is 5(max courses)
	and the function gets course serial number.
* Output:
	int function- if the course exist the function return the index in the array
	if the course doesnt exist the function return -1.
* Function Operation:
	the function useing atoi function to convert the serial course number from char to int
	then go into a for loop and check if the serial number is apear in one of the indexes in the array,
	if the function found the same serial number as the function gets, so the function return the index number
	of the course in the array,
	else the function returns -1.
******************/
int ifCourseExists(courses_t courseList[], char serialNumber[])
{
	int serialAsInt;
	serialAsInt = atoi(serialNumber);
	for (int i = 0; i < MAX_COURSES; i++)
	{
		if (courseList[i].courseNumber == serialAsInt)
			return i;
	}
	return WRONG_CHOICE;
}
/******************
* Function Name:
	initializeNull
* Input:
	gets the array that contains the list of the courses
* Output:
	void function doesnt return a value
* Function Operation:
	the function initialize the pointers inside the variable student- the head and the tail to point for NULL
	and the variable ifExist to ZERO.
******************/
void initializeNull(courses_t courseList[])
{
	for (int i = 0; i < MAX_COURSES; i++)
	{
		courseList[i].student.head = NULL;
		courseList[i].student.tail = NULL;
		courseList[i].ifExsist = 0;
	}
}
/******************
* Function Name:
	ifEmptySpot
* Input:
	the function gets the array that contains the courses
* Output:
	int function-return the index number that doesnt have a course, and if all the spots
	full, the function returns -1.
* Function Operation:
	the function checks if there is more place in the array to add another course
******************/
int ifEmptySpot(courses_t courseList[])
{
	for (int i = 0; i < MAX_COURSES; i++)
		if (courseList[i].ifExsist == 0)
			return i;
	printf("Unfortunately, there is no room for more classes.\n");
	return WRONG_CHOICE;
}
/******************
* Function Name:
	addClass
* Input:
	the function gets the class name and serial number that the user ask to add,
	the array of courses, and empty index that doesnt contain a class yet-to know in which index to add the class
* Output:
	void function doesnt return a value
* Function Operation:
	first, the function checks that the course serial number contains onlt digits.
	than the function use atoi to convert the course number to int.
	after that the function initialize the course in the correct index- according the emptyindex she gets,
	and put there the course name and serial number,puts 1 inside the variable ifExist 
	and than print out a massage that the class added .
******************/
void addClass(char className[], int emptyIndex, courses_t courseList[], char serialNumber[])
{
	int serialAsInt;
	for (unsigned int i = 0; i < strlen(serialNumber); i++)
		if (!isdigit(serialNumber[i]))
		{
			printf("Error: invalid class number or name.\n");
			return;
		}
	serialAsInt = atoi(serialNumber);
	strcpy(courseList[emptyIndex].courseName, className);
	courseList[emptyIndex].courseNumber = serialAsInt;
	courseList[emptyIndex].ifExsist = TRUE;
	printf("Class \"%05d %s\" added.\n", courseList[emptyIndex].courseNumber, courseList[emptyIndex].courseName);
	return;
}
/******************
* Function Name:
	updateClass
* Input:
	the function gets the course name that its need to update,
	the index of the course in the array.
	the array of the courses
	the serial number of the course.
* Output:
	void function, doesnt return a value.
* Function Operation:
	first, the function checks if the serial number is legal, if not so its print an error massage,
	than the function update the course name in the correct index in the array.
	after that its print a massage that the class is updated.
******************/
void updateClass(char className[], int existence, courses_t courseList[], char serialNumber[])
{
	int serialAsInt;
	for (unsigned int i = 0; i < strlen(serialNumber); i++)
		if (!isdigit(serialNumber[i]))
		{
			printf("Error: invalid class number or name.\n");
			return;
		}
	serialAsInt = atoi(serialNumber);
	strcpy(courseList[existence].courseName, className);
	courseList[existence].courseNumber = serialAsInt;
	printf("Class \"%05d %s\" updated.\n", courseList[existence].courseNumber, courseList[existence].courseName);
	return;
}
/******************
* Function Name:
	checkClassName
* Input:
	the function gets a string with the course name and serial number
	and gets the array of the courses as well.
* Output:
	void function doesnt return a value.
* Function Operation:
	the function using strtok to divide the string to the course name and the course number .
	than using strcpy and strcat functions to remove all the spaces before the class name
	and puts \0 by strcat in the end of the string.
	after we have legal string wothout spaces the function check the length of the class name
	and that all of the ingredients are legal, if something foung ilegal the function print
	an error massage. after that the function using ifCourseExist function to check if the course number that its
	get is already exist or not, according to that the function know whether to update the course 
	or to add a new one.
******************/
void checkClassName(char tempCourseName[], courses_t courseList[])
{
	char* classpartName, * classpartName1, * serialNumber;
	char className[MAX_LENGTH];
	int emptyIndex, existence;
	serialNumber = strtok(tempCourseName, " ");
	classpartName = strtok(NULL, " ");
	classpartName1 = strtok(NULL, "");
	if (classpartName == NULL)
	{
		printf("Error: invalid class number or name.\n");
		return;
	}
	strcpy(className, classpartName);
	if (classpartName1 != NULL)
		strcat(strcat(className, " "), classpartName1);
	strcat(className, "\0");
	for(unsigned int i=0;i<strlen(className);i++)
		if ((isalnum(className[i]) == FALSE && (className[i] != ' ')))
		{
			printf("Error: invalid class number or name.\n");
			return;
		}
	if (strlen(className) >= 1 && strlen(className) <= COURSE_NAME_LENGTH && strlen(serialNumber) == 5)
	{
		existence = ifCourseExists(courseList, serialNumber);
		if (existence != WRONG_CHOICE)
			updateClass(className, existence, courseList, serialNumber);
		else
		{
			emptyIndex = ifEmptySpot(courseList);
			if (emptyIndex != WRONG_CHOICE)
				addClass(className, emptyIndex, courseList, serialNumber);
		}
	}
	else
		printf("Error: invalid class number or name.\n");
}
/**************Exercise 2******************/
/******************
* Function Name:
	checkDelimiters
* Input:
	the function gets a string from the user that contains the student name,his grade and class number.
* Output:
	int function return FALSE(0) or TRUE(1).
* Function Operation:
	the function check that the string has all the delimiters that should separate between
	the student name, the course number and the student grade.
	first, the function using a temparory string and by strtok checks if all the delimiters
	are where thay suppose to be, the function check that there is only one ',' between course number
	and the student grade,if there are more or less ',' the function returns FALSE,else, return TRUE.
******************/
int checkDelimiters(char* tempName)
{
	int count = 0;
	char* check1,tempStr[MAX_LENGTH];
	strcpy(tempStr, tempName);
	strtok(tempStr, ":");
	if (!strcmp(tempStr, tempName))
		return FALSE;
	check1 = strtok(NULL, ";");
	//while loop until check1==NULL
	while (check1)
	{
		for (unsigned int i = 0; i < strlen(check1); i++)
			if (check1[i] == ',')
			//the counter count how match ',' is apear.
				count++;
		//check if there is 1 ',' , if there is more or less, return FALSE.
		if (count != TRUE)
			return FALSE;
		count = FALSE;
		check1 = strtok(NULL, ";");
	}
	return TRUE;
}
/******************
* Function Name:
	checkString
* Input:
	the function gets the adress of pointers- pointer to student name
	pointer to course number, pointer to course grade.(because we need to change the value inside)
	the function gets as well the string that contain the student we want to add\update.
	and the array of courses.
* Output:
	int function return FALSE(0) or TRUE(0)
* Function Operation:
	first the function check by checkDelimiters function that all the delimiters in the correct place,
	after that using strtok to sperate the student name, the course number and the student grade.
	than the function check by ifLegalData function if the student name, the course number and the grade
	are all legals,if one of those is ilegal, the function returns FALSE.
******************/
int checkString(char** studentName, char** courseNumber, char** courseGrade, char tempName[], courses_t courseList[])
{
	int length;
	length = strlen(tempName);
	char checkTempName[MAX_LENGTH];
	if (!checkDelimiters(tempName))
		return FALSE;
	strcpy(checkTempName, tempName);
	if (tempName[length - 1] != ';')
		return FALSE;
	*studentName = strtok(checkTempName, ":");
	*courseNumber = strtok(NULL, "' ' ,");
	*courseGrade = strtok(NULL, "' ' ;");
	//while loop until the pointer inside courseGrade is NULL
	while (*courseGrade != NULL)
	{
		if (*courseNumber == NULL || *courseGrade == NULL || *studentName == NULL)
			return FALSE;
		//check the data in the string with ifLegalData function
		if (!ifLegalData(*studentName, *courseNumber, *courseGrade, courseList))
			return FALSE;
		*courseNumber = strtok(NULL, "' ' ,");
		*courseGrade = strtok(NULL, "' ' ;");
	}
	//change the value of all the variables if all legal
	*studentName = strtok(tempName, ":");
	*courseNumber = strtok(NULL, "' ' ,");
	*courseGrade = strtok(NULL, "' ' ;");
	return TRUE;
}
/******************
* Function Name:
	isEmptyList
* Input:
	function gets array of courses and the index that the course apear at.
* Output:
	int function returns FALSE(0) or TRUE(0)
* Function Operation:
	the function check if there are students in the course, if there are no students
	returns FALSE else return TRUE.
******************/
int isEmptyList(courses_t courseList[], int class)
{
	if (courseList[class].student.head == NULL)
		return FALSE;
	return TRUE;
}
/******************
* Function Name:
	ifStudentExists
* Input:
	the function gets student name, the array of courses and the index of the class
	that we need to check if the student register to.
* Output:
	function return a pointer to the place of the student in the link list
	and if the student doesnt exist in the course the function returns NULL.
* Function Operation:
	the function go over all the link list by a pointer that point to the head of the list
	and start to go over the list until the tail,the function doing that by a while loop.
******************/
student_t* ifStudentExists(char studentName[], courses_t courseList[], int class)
{
	student_t* studentP;
	if (!isEmptyList(courseList, class))
		return NULL;
	studentP = courseList[class].student.head;
	//while loop until studentP=NULL
	while (studentP)
	{
		if (strcmp(studentName, studentP->studName) == 0)
			//returns the pointer to the student we want to update
			return studentP;
		studentP = (student_t*)studentP->next;
	}
	//if return NULL we know that the student doesnt exist and we need to add him.
	return NULL;
}
/******************
* Function Name:
	updateStudent
* Input:
	function gets the array of courses, student name, the index in the array that the course there,
	the stusent grade and the pointer that point the correct student in the list.
* Output:
	void function, doesnt return a value.
* Function Operation:
	the function puts the student the new grade and print out a massage 
	that says that the student updated on the class.
******************/
void updateStudent(courses_t courseList[], char studentName[], int class, int gradeStud, student_t* p)
{
	p->grade = gradeStud;
	printf("Student \"%s\" updated on class \"%05d %s\" with grade %d.\n",
		p->studName, courseList[class].courseNumber, courseList[class].courseName, p->grade);
}
/******************
* Function Name:
	addStudent
* Input:
	function gets the array of courses, student name,the index of the class the we need to add
	the student there and the student grade.
* Output:
	void function doesnt return a value
* Function Operation:
	first, the function using malloc function to create a new node in the list and save 
	the adress that malloc returns in a pointer to student struct.
	if the malloc faild, its free all the mallocs until now and exit the program.
	after that its initialize the new node with the student name and grade,
	if the student is first on the list so we initialize the head and tail pointer to point
	to this node, else, if the student isnt the first so we only changed the tail pointer.
	after that its print out a massage that the student added.
******************/
void addStudent(courses_t courseList[], char studentName[], int class, int gradeStud)
{
	student_t* newStudent = (student_t*)malloc(sizeof(student_t));
	if (newStudent == NULL)
	{
		freeAll(courseList);
		exit(1);
	}
	//intialize all the field in the new student node
	newStudent->grade = gradeStud;
	strcpy(newStudent->studName, studentName);
	newStudent->next = NULL;
	//check if the new student is the first in this class
	if (!isEmptyList(courseList, class))
	{
		courseList[class].student.head = newStudent;
		courseList[class].student.tail = newStudent;
	}
	else
	{
		courseList[class].student.tail->next = (struct student*)newStudent;
		courseList[class].student.tail = newStudent;
	}
	printf("Student \"%s\" added to class \"%05d %s\" with grade %d.\n",
		newStudent->studName, courseList[class].courseNumber, courseList[class].courseName, newStudent->grade);
}
/******************
* Function Name:
	ifLegalData
* Input:
	function gets the student name and grade, course number and the array of courses.
* Output:
	int function, returns FALSE(0) or TRUE(1)
* Function Operation:
	the function checks that all the data from the user are legal.
	first, checks the student name-the length and the ingrediants(only letters and spaces).
	than the function checks if the course number its gets exist and the ingrediants of the grade(only numbers between 0-100)
	if all the checks are goes well the function returns TRUE,else return FALSE.
******************/
int ifLegalData(char* studName, char* courseNumber, char* courseGrade, courses_t courseList[])
{
	int numAsInt;
	//checks the name length
	if (strlen(studName) >= 1 && strlen(studName) <= STUDENT_NAME_LENGTH)
		for (unsigned int i = 0; i < strlen(studName); i++)
		{
			if ((studName[i] == ' ') || (studName[i] >= 'a' && studName[i] <= 'z') || (studName[i] >= 'A' && studName[i] <= 'Z'))
				continue;
			else
				return FALSE;
		}
	else
		return FALSE;
	//checks if the course exist in the system
	if (ifCourseExists(courseList, courseNumber) == WRONG_CHOICE)
		return FALSE;
	for (unsigned int i = 0; i < strlen(courseGrade); i++)
		//checks that the grade legal
		if (!(isdigit(courseGrade[i])))
			return FALSE;
	numAsInt = atoi(courseGrade);
	if (!(numAsInt >= 0 && numAsInt <= 100))
		return FALSE;
	return TRUE;
}
/******************
* Function Name:
	checkStudent
* Input:
	function gets string from the user and the array of courses.
* Output:
	void function, doesnt return a value.
* Function Operation:
	the function gets the string from the user and by using all the function above 
	the function gets data that indicate if the student is new in the course and need to add him
	or that the student is already exist and just need to update his grade.
	first, using checkString function and if its return TRUE we go to a while loop
	that check all the courses numbers and the student grade, and every iteration
	repeat it self and check again if need to add the student or only update his grade.
******************/
void checkStudent(char tempName[], courses_t courseList[])
{
	char* studentName = NULL, * courseNumber = NULL, * courseGrade = NULL;
	int gradeAsInt, class;
	student_t* pointer;
	//if the function returns FLASE we print error massage
	if (checkString(&studentName, &courseNumber, &courseGrade, tempName, courseList))
	{
		//checks every course sparatly if need to update or add the student
		while (courseGrade != NULL && courseNumber != NULL)
		{
			gradeAsInt = atoi(courseGrade);
			class = ifCourseExists(courseList, courseNumber);
			if (class == WRONG_CHOICE)
			{
				printf("Error: invalid name, class number or grade.\n");
				return;
			}
			pointer = ifStudentExists(studentName, courseList, class);
			if (pointer != NULL)
				updateStudent(courseList, studentName, class, gradeAsInt, pointer);
			else
				addStudent(courseList, studentName, class, gradeAsInt);
			courseNumber = strtok(NULL, "' ' ,");
			courseGrade = strtok(NULL, "' ' ;");
		}
	}
	else
		printf("Error: invalid name, class number or grade.\n");
}
/**************Exercise 3******************/
/******************
* Function Name:
	ifStudentInTheSystem
* Input:
	function gets the student name and the array of courses
* Output:
	int function return TRUE(1) or FALSE (0)
* Function Operation:
	the function going over the indexes in the array of courses with for loop
	and in every course go over all the students and check if the student that she gets his name
	is exist at least in 1 course.
******************/
int ifStudentInTheSystem(char* studentName, courses_t* courseList)
{
	student_t* studentP;
	//for loop that go over all the indexes in the array
	for (int i = 0; i < MAX_COURSES; i++)
	{
		//pointer that help us to go over all the students in the list.
		studentP = courseList[i].student.head;
		//while loop until studentP = NULL or until we found our student :).
		while (studentP)
		{
			if (!strcmp(studentP->studName, studentName))
				return TRUE;
			studentP = (student_t*)studentP->next;
		}
	}
	//if the function get here so we know that the student doesnt exist.
	printf("Error: invalid name or class number.\n");
	return FALSE;
}
/******************
* Function Name:
	ifLastOnList
* Input:
	function gets the array of courses the student name,course number and counter
* Output:
	int function,returns TRUE(1)(if last on list) or FALSE(0)
* Function Operation:
	the function deal the case when the student we want to remove from the course is the last on the list.
******************/
int ifLastOnList(courses_t* courseList, int courseNumber, char studentName[], int counter)
{
	student_t* current, * perv;
	int j, i;
	//two for loop - the first loop is the number of courses that the student want to removed
	for (j = 0; j < counter; j++)
		//the second loop go over all the courses and checks if the course number is the one that the student want to remove from.
		for (i = 0; i < MAX_COURSES; i++)
		{
			if (courseList[i].courseNumber == courseNumber)
				if (!strcmp(courseList[i].student.tail->studName, studentName))
				{
					perv = courseList[i].student.head;
					current = (student_t*)perv->next;
					//while loop with current pointer and perv pointer
					while (current != NULL)
					{
						//we need two pointers that can linked between the nodes after we removed one.
						if (current == courseList[i].student.tail)
						{
							courseList[i].student.tail = perv;
							perv->next = NULL;
							free(current);
							printf("Student \"%s\" removed from class \"%05d %s\".\n",
								studentName, courseList[i].courseNumber, courseList[i].courseName);
							return TRUE;
						}
						perv = current;
						current = (student_t*)current->next;
					}
				}
		}
	//if the student wasnt last on the list we return FALSE
	return FALSE;
}
/******************
* Function Name:
	ifFirstOnList
* Input:
	function gets the array of courses the student name,course number and counter
* Output:
	int function,returns TRUE(1)(if first on list) or FALSE(0)
* Function Operation:
	the function deal the case when the student we want to remove from the course is the first on the list.
	so we check two option- if this student is the first and the single one
	and second case if the student first but not the only one.
******************/
int ifFirstOnList(courses_t* courseList, int courseNumber, char studentName[], int counter)
{
	student_t* current;
	int j, i;
	for (j = 0; j < counter; j++)
	{
		for (i = 0; i < MAX_COURSES; i++)
		{
			if (courseList[i].courseNumber == courseNumber)
			{
				//if the first student is the only one on the list
				if (courseList[i].student.head->next == NULL)
				{
					free(courseList[i].student.head);
					courseList[i].student.head = NULL;
					printf("Student \"%s\" removed from class \"%05d %s\".\n",
						studentName, courseList[i].courseNumber, courseList[i].courseName);
					return TRUE;
				}
				//if the first student ist the only one on the list
				else if (!strcmp(courseList[i].student.head->studName, studentName))
				{
					current = courseList[i].student.head;
					courseList[i].student.head = (student_t*)current->next;
					free(current);
					printf("Student \"%s\" removed from class \"%05d %s\".\n",
						studentName, courseList[i].courseNumber, courseList[i].courseName);
					return TRUE;
				}
			}
		}
	}
	//return FALSE if the student wasnt the first on the list
	return FALSE;
}
/******************
* Function Name:
	removeStudent
* Input:
	function gets the array of courses an array of pointers that contains the courses numbers
	that the student want to removed him self from them, the student name and counter
	that says to how many courses the student want to remove him self from.
* Output:
	void function doesnt return a value
* Function Operation:
	first, the function checks if the student is first or last on the list.
	if he isnt so the function just go over the list according the courses number in the array
	and removed the student fron the courses.
******************/
void removeStudent(courses_t courseList[], char** coursesNumbers, char studentName[], int counter)
{
	student_t* currentP, * beforeCurrentP;
	int numAsInt;
	for (int j = 0; j < counter; j++)
	{
		for (int i = 0; i < MAX_COURSES; i++)
		{
			numAsInt = atoi(coursesNumbers[j]);
			if (courseList[i].courseNumber == numAsInt)
			{
				//checks if the student first or last on the list
				if (ifFirstOnList(courseList, numAsInt, studentName, counter))
					continue;
				else if (ifLastOnList(courseList, numAsInt, studentName, counter))
					continue;
				beforeCurrentP = courseList[i].student.head;
				currentP = (student_t*)beforeCurrentP->next;
				//the pointer current help us go over all the list and search for the student we want to remove.
				while (currentP != NULL)
				{
					//if we found the student we go inside the if statment and free the student node.
					if (!strcmp(currentP->studName, studentName))
					{
						beforeCurrentP->next = currentP->next;
						free(currentP);
						printf("Student \"%s\" removed from class \"%05d %s\".\n",
							studentName, courseList[i].courseNumber, courseList[i].courseName);
						break;
					}
					beforeCurrentP = currentP;
					currentP = (student_t*)currentP->next;
				}
			}
		}
	}
}
/******************
* Function Name:
	ifCanBeRemoved
* Input:
	function gets array of pointer with courses numbers, the array of courses, student name and counter
* Output:
	int function return TRUE(1)(if the student can be removed) or FLASE(0)
* Function Operation:
	the function count to how many courses the student register, and check
	if there is at least 1 course that the student register to but dont want to remove 
	him self from there.
	then, if the number of courses he want to removed from is equal or bigger then the 
	number of courses that hes registerd to, the function returns FALSE.
******************/
int ifCanBeRemoved(char* coursesNumbers[], courses_t courseList[], char studentName[], int countCourses)
{
	int counter = 0;
	student_t* studentP;
	//go over all the courses
	for (int i = 0; i < MAX_COURSES; i++)
	{
		studentP = courseList[i].student.head;
		//every course that we find the student at we add 1 to the counter.
		while (studentP)
		{
			if (!strcmp(studentP->studName, studentName))
			{
				counter++;
				break;
			}
			studentP = (student_t*)studentP->next;
		}
	}
	//checks which counter is bigger
	if (counter > countCourses)
		return TRUE;
	return FALSE;
}
/******************
* Function Name:
	checkIfLegal
* Input:
	the function gets string from the user and the array of courses 
* Output:
	void function doesnt return a value.
* Function Operation:
	the function checks if the string we get from the user is legal according the rules.
	so with strtok the function divide the string and check evert details there(course number student name...)
	the function uses help functions that helps her to check all the data, if all the checks
	went right we send the details(after we know that all legal) to remove function.
******************/
void checkIfLegal(char tempString[], courses_t courseList[])
{
	char* studentName, * coursesNumbers[MAX_COURSES];
	int j, i, counter = 0, firstIndex = 0,length;
	length = strlen(tempString);
	//checks if the last char is ','
	if (tempString[length - 1] != ',')
	{
		printf("Error: invalid name or class number.\n");
		return;
	}
	studentName = strtok(tempString, ":");
	if (!ifStudentInTheSystem(studentName,courseList))
		return;
	//initialize all the pointers with NULL .
	for (j = 0; j < MAX_COURSES; j++)
		coursesNumbers[j] = NULL;
	for (i = 0; i < MAX_COURSES; i++)
	{
		//puts the courses number inside the array of pointers
		coursesNumbers[i] = strtok(NULL, "' ' ,");
		//if the index isnt NULL its mean that we have there a course number, so add 1 to the counter.
		if (coursesNumbers[i] != NULL)
		{
			counter++;
			j = ifCourseExists(courseList, *(coursesNumbers + i));
			//if the course or the student doesnt in the system or the student doesnt in the course.
			if (j == WRONG_CHOICE || studentName == NULL)
			{
				printf("Error: invalid name or class number.\n");
				return;
			}
			if (ifStudentExists(studentName, courseList, j) == NULL)
			{
				printf("Error: student is not a member of class \"%05d %s\".\n",
					courseList[j].courseNumber, courseList[j].courseName);
				return;
			}
		}
		if (coursesNumbers[firstIndex] == NULL)
		{
			printf("Error: invalid name or class number.\n");
			return;
		}
	}
	//if all the data are legal ew remove the student.
	if (ifCanBeRemoved(coursesNumbers, courseList, studentName, counter))
		removeStudent(courseList, coursesNumbers, studentName, counter);
	else
		printf("Error: student cannot be removed from all classes.\n");
}
/**************Exercise 4******************/
/******************
* Function Name:
	swapStudentDetails
* Input:
	the function gets two pointers that point to two diffrent students.
* Output:
	void function doesnt return a value.
* Function Operation:
	the function replace between the student data.
******************/
void swapStudentDetails(student_t* prevStudent, student_t* currentStudent)
{
	int tempGrade;
	char tempName[STUDENT_NAME_LENGTH];
	//replace the names
	strcpy(tempName, currentStudent->studName);
	strcpy(currentStudent->studName, prevStudent->studName);
	strcpy(prevStudent->studName, tempName);
	//replace the grades
	tempGrade = currentStudent->grade;
	currentStudent->grade = prevStudent->grade;
	prevStudent->grade = tempGrade;
}
/******************
* Function Name:
	sortFunction
* Input:
	function gets course index in the array of courses and the array of courses
* Output:
	void function doesnt return a value.
* Function Operation:
	the function arranges the student by the names and according to the ascii table.
	and then print out all the student in the class with there grades.
******************/
void sortFunction(int courseIndex, courses_t* courseList)
{
	student_t* currentStudent, * prevStudent;
	prevStudent = courseList[courseIndex].student.head;
	while (prevStudent != NULL)
	{
		currentStudent = (student_t*)prevStudent->next;
		while (currentStudent != NULL)
		{
			if (strcmp(prevStudent->studName, currentStudent->studName) > 0)
			{
				swapStudentDetails(prevStudent, currentStudent);
			}
			currentStudent = (student_t*)currentStudent->next;
		}
		prevStudent = (student_t*)prevStudent->next;
	}
	currentStudent = courseList[courseIndex].student.head;
	printf("Class \"%05d %s\" students:\n", courseList[courseIndex].courseNumber, courseList[courseIndex].courseName);
	while (currentStudent)
	{
		printf("%s, %d\n", currentStudent->studName, currentStudent->grade);
		currentStudent = (student_t*)currentStudent->next;
	}
}
/******************
* Function Name:
	checkCourseNumber
* Input:
	function gets stirng with one course number and the array of courses
* Output:
	void function doesnt return a value
* Function Operation:
	the function checks if the course number is exist and 
	if he is so the function check if there is one student on the list or more.
	as well the function check that the string from the user is legal.
******************/
void checkCourseNumber(char tempString[], courses_t* courseList)
{
	int courseIndex = ifCourseExists(courseList, tempString);
	student_t* studentP = courseList[courseIndex].student.head;
	studentP = courseList[courseIndex].student.head;
	//checks if the course exist
	if (courseIndex == WRONG_CHOICE)
	{
		printf("Error: invalid class number.\n");
		return;
	}
	//checks if there are students in the course
	if (!isEmptyList(courseList, courseIndex))
	{
		printf("Class \"%05d %s\" has no students.\n", 
			courseList[courseIndex].courseNumber, courseList[courseIndex].courseName);
		return;
	}
	if (studentP->next == NULL)
	{
		printf("Class \"%05d %s\" students:\n%s, %d\n",
			courseList[courseIndex].courseNumber, courseList[courseIndex].courseName,
			studentP->studName, studentP->grade);
		return;
	}
	//if all the checks go well we go to sort function
	sortFunction(courseIndex, courseList);
}
/**************Exercise 5******************/
/******************
* Function Name:
	countNumOfStudents
* Input:
	function gets array of courses
* Output:
	void function doesnt return a value.
* Function Operation:
	the function checks how many student there are in the course
	and print out a massage.
	if there are no student the function print another massage.
******************/
void countNumOfStudents(courses_t* courseList)
{
	student_t* studentP;
	int numOfStud = 0, i;
	for (i = 0; i < MAX_COURSES && courseList[i].ifExsist == TRUE; i++)
	{
		studentP = courseList[i].student.head;
		if (studentP == NULL)
		{
			printf("Class \"%05d %s\" has no students.\n", courseList[i].courseNumber, courseList[i].courseName);
			continue;
		}
		while (studentP)
		{
			numOfStud++;
			studentP = (student_t*)studentP->next;
		}
		printf("%05d %s, %d\n", courseList[i].courseNumber, courseList[i].courseName, numOfStud);
		numOfStud = 0;
	}
}
/******************
* Function Name:
	calculateGradeSum
* Input:
	function gets the array of courses
* Output:
	void function doesnt return a value
* Function Operation:
	the function sum all the students grades in the class and print out the sum.
	if the class is empty so print a massage
******************/
void calculateGradeSum(courses_t* courseList)
{
	student_t* studentP;
	int i, gradeSum = 0, studTempGrade = 0;
	for (i = 0; i < MAX_COURSES && courseList[i].ifExsist == TRUE; i++)
	{
		studentP = courseList[i].student.head;
		//check if the class is empty
		if (studentP == NULL)
		{
			printf("Class \"%05d %s\" has no students.\n", courseList[i].courseNumber, courseList[i].courseName);
			continue;
		}
		//sum all the students grades
		while (studentP)
		{
			studTempGrade = studentP->grade;
			gradeSum += studTempGrade;
			studentP = (student_t*)studentP->next;
		}
		printf("%05d %s, %d\n", courseList[i].courseNumber, courseList[i].courseName, gradeSum);
		gradeSum = 0;
	}
}
/******************
* Function Name:
	minimalGrade
* Input:
	function gets an array of courses
* Output:
	void function, doesnt return a value.
* Function Operation:
	the function checks in every course what is the minimal grade in the class.
	if there are no student in the class, we print a massage.
******************/
void minimalGrade(courses_t* courseList)
{
	student_t* studentP;
	int i, minGrade;
	for (i = 0; i < MAX_COURSES; i++)
	{
		//check if there is a course in the index
		if (courseList[i].ifExsist == FALSE)
			continue;
		studentP = courseList[i].student.head;
		//checks is at least 1 student in the course
		if (studentP == NULL)
		{
			printf("Class \"%05d %s\" has no students.\n", courseList[i].courseNumber, courseList[i].courseName);
			continue;
		}
		minGrade = studentP->grade;
		//checking which grade is the lowest
		while (studentP)
		{
			if (studentP->grade < minGrade)
				minGrade = studentP->grade;
			studentP = (student_t*)studentP->next;
		}
		printf("%05d %s, %d\n", courseList[i].courseNumber, courseList[i].courseName, minGrade);
	}
}
/******************
* Function Name:
	maximalGrade
* Input:
	functon gets the array of courses
* Output:
	void function doesnt return a value.
* Function Operation:
	the function checks in every course what is the maximum grade in the class.
	if there are no student in the class, we print a massage.
******************/
void maximalGrade(courses_t* courseList)
{
	student_t* studentP;
	int i, maxGrade;
	for (i = 0; i < MAX_COURSES; i++)
	{
		//check if there is a class in the index
		if (courseList[i].ifExsist == FALSE)
			continue;
		studentP = courseList[i].student.head;
		//if class is empty
		if (studentP == NULL)
		{
			printf("Class \"%05d %s\" has no students.\n", courseList[i].courseNumber, courseList[i].courseName);
			continue;
		}
		maxGrade = studentP->grade;
		//check what the max grade
		while (studentP)
		{
			if (studentP->grade > maxGrade)
				maxGrade = studentP->grade;
			studentP = (student_t*)studentP->next;
		}
		printf("%05d %s, %d\n", courseList[i].courseNumber, courseList[i].courseName, maxGrade);
	}
}
/******************
* Function Name:
	ifNoCourses
* Input:
	function gets the array of courses
* Output:
	int function, return TRUE or FALSE
* Function Operation:
	the function go over the array of courses and check if there is
	at least one course in the array.
******************/
int ifNoCourses(courses_t* courseList)
{
	int counter = 0, i;
	for (i = 0; i < MAX_COURSES; i++)
		if (courseList[i].ifExsist == FALSE)
			counter++;
	//if all the indexes without a course, print error and return FALSE.
	if (counter == MAX_COURSES)
	{
		printf("Error: there are no classes.\n");
		return FALSE;
	}
	return TRUE;
}
/******************
* Function Name:
	averageCalculation
* Input:
	function gets array ot courses
* Output:
	void function doesnt return a value
* Function Operation:
	the function check if there are students in the course
	and if there are so with loop while and a pointer we go over all 
	the students in the list and calculate the avrage grade.
	then print it out.
******************/
void averageCalculation(courses_t* courseList)
{
	student_t* studentP;
	int i, sum = 0, counter = 0;
	for (i = 0; i < MAX_COURSES; i++)
	{
		if (courseList[i].ifExsist == FALSE)
			continue;
		studentP = courseList[i].student.head;
		//checks if there are students in the course 
		if (studentP == NULL)
		{
			printf("Class \"%05d %s\" has no students.\n", courseList[i].courseNumber, courseList[i].courseName);
			continue;
		}
		//loop while that help us to go over the list 
		while (studentP != NULL)
		{
			//calculate the sum of students and how mutch student.
			sum += studentP->grade;
			counter++;
			studentP = (student_t*)studentP->next;
		}
		//print a massage with the avrage grade.
		printf("%05d %s, %d\n", courseList[i].courseNumber, courseList[i].courseName, sum / counter);
		sum = 0;
		counter = 0;
	}
}
/******************
* Function Name:
	printCalculationMenu
* Input:
	function gets the array with the courses
* Output:
	void function doesnt return a value.
* Function Operation:
	the function print a menu of opertions 
	and than send the choice of the user with a switch case.
******************/
void printCalculationMenu(courses_t* courseList)
{
	char choice;
	if (!ifNoCourses(courseList))
		return;
	printf("Please select the aggregation method:\n\ta. Average Grade.\n\tb. Maximal Grade.\
\n\tc. Minimal Grade.\n\td. Sum.\n\te. Count.\n\t0. Return to the main menu.\n");
	scanf(" %c", &choice);
	switch (choice)
	{
	case 'a':
		averageCalculation(courseList);
		break;
	case 'b':
		maximalGrade(courseList);
		break;
	case 'c':
		minimalGrade(courseList);
		break;
	case 'd':
		calculateGradeSum(courseList);
		break;
	case 'e':
		countNumOfStudents(courseList);
	default:
		return;
	}
}
/******************************************/
