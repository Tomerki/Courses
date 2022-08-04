/***********************
* Tomer
* 207651027
* 01
* ex6
***********************/
#ifndef _EX6_H_
#define _EX6_H_
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LENGTH 50
#define TRUE 1
#define FALSE 0
#define SPACE 3
#define COUNT 8
//enums for better understanding the menu.
enum { EXIT = 48, CREATE_FAMILY, ADD_FAMILY_MEMBER, PRINT_FAMILY_TREE,BIDUD,SUPER_SPREADER, VACCINE, PRINT_MENU };
enum{RETURN_MAIN_MENU=48,PRINT_FAMILY,PRINT_PRE_ORDER,PRINT_LEFT_ORDER,PRINT_BFS};
//the struct of the tree.
struct Trin_Ari {
	int id;
	char* name;
	struct Trin_Ari* left;
	struct Trin_Ari* middle;
	struct Trin_Ari* right;
	struct Trin_Ari* myFather;
};
typedef struct Trin_Ari Trin_Ari;
//all the functions that called from main function.
void printMenu(char* choice);
void printSelectOperation(char* choice);
Trin_Ari* createNode(Trin_Ari* root,int memberID,char* memberName);
int getNewMemberData(Trin_Ari* root,int* id, char* memberName);
int addNewMember(Trin_Ari* root, int memberID, char* memberName);
void printTreeOptions(Trin_Ari* root, void(*funP)(Trin_Ari*));
void insulationCov19(Trin_Ari* root);
void freeTree(Trin_Ari* root);
int gotVaccine(Trin_Ari* root);
void printBFS(Trin_Ari* root, void(*funP)(Trin_Ari*));
void superSpreader(Trin_Ari* root, void(*funP)(Trin_Ari*));
void printTheBFS(Trin_Ari* current);
void printBidud(Trin_Ari* current);
#endif
