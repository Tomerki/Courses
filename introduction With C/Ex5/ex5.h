#ifndef EX5_EX5_H
#define EX5_EX5_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define COURSE_NAME_LENGTH 30
#define STUDENT_NAME_LENGTH 20
#define MAX_COURSES 5
#define WRONG_CHOICE -1
#define MAX_LENGTH 200
#define FALSE 0
#define TRUE 1 
/***********************
*Tomer Hadar
* 207651027
* 01
* ex5
***********************/
//struct for student- with grade his name and pointer to the next student
struct Student
{
	int grade;
	char studName[STUDENT_NAME_LENGTH];
	struct student* next;
};
typedef struct Student student_t;
/*
struct with two pointers head the point the first node in the list
and the tail pointer that point the last node in the list
*/
typedef struct
{
	student_t* head, *tail;
}LIST;
/**************
struct that have course serial number course name and variable
from LIST type that help us access to the linked list of the students
if Exist- indicate us if there is a course in the node or not.
***************/
struct courses
{
	int courseNumber, ifExsist;
	char courseName[COURSE_NAME_LENGTH];
	LIST student;
};
typedef struct courses courses_t;
void initializeNull(courses_t* courseList);
void printMenu();
void checkClassName(char tempCourseName[], courses_t* courseList);
void printChoosing(char* choice);
void checkStudent(char tempName[], courses_t* courseList);
void checkIfLegal(char tempString[], courses_t* courseList);
void checkCourseNumber(char tempString[], courses_t* courseList);
void printCalculationMenu(courses_t* courseList);
void freeAll(courses_t* courseList);
#endif // !EX5_EX5_H

