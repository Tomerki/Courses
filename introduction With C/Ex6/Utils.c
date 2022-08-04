/***********************
* Tomer
* 207651027
* 01
* ex6
***********************/
#include "ex6.h"
// Function to print Trinary tree in 2D 
// It does reverse inorder traversal 
void print2DUtil(Trin_Ari* root, int space)
{
	// Base case 
	if (root == NULL)
		return;
	// Increase distance between levels 
	space += COUNT;
	// Process right child first 
	print2DUtil(root->right, space);
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%s %d\n", root->name, root->id);
	// Process middle child 
	print2DUtil(root->middle, space);
	printf("\n");
	// Process left child 
	print2DUtil(root->left, space);
}
/******************
* Function Name:
	printPreOrder
* Input:
	gets the root of the tree
* Output:
	void function doesnt return a value
* Function Operation:
	the function print the data in the nodes tree.
	the function using recursion calls
	first print the father and than his children.
******************/
void printPreOrder(Trin_Ari* root)
{
	if (root == NULL)
		return;
	printf("%s ID: %d\n", root->name, root->id);	
	printPreOrder(root->left);
	printPreOrder(root->middle);
	printPreOrder(root->right);
}
/******************
* Function Name:
	printLeftOrder
* Input:
	gets the root of the tree
* Output:
	void function doesnt return a value
* Function Operation:
	the function print the data in the nodes tree.
	the function using recursion calls
	first print the left child and than the father and than the other children.
******************/
void printLeftOrder(Trin_Ari* root)
{
	if (root == NULL)
		return;
	printLeftOrder(root->left);
	printf("%s ID: %d\n", root->name, root->id);	
	printLeftOrder(root->middle);
	printLeftOrder(root->right);
}
