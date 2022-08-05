/***********************
* Tomer
* ex6
***********************/
#include "ex6.h"
#include "Utils.h"
#include "queue.h"
/******************
* Function Name:
    printSelectOperation
* Input:
    function gets the adress of the variable that save the user choice
* Output:
    void function doesnt return a value.
* Function Operation:
    the function checks if the user choice is available
    and ask the user to choose an operation.
******************/
void printSelectOperation(char* choice)
{
    if(*choice < EXIT || *choice > PRINT_MENU)
        printf("Error: unrecognized operation.\n");
    printf("Select the next operation (insert 7 for the entire menu):\n");
    scanf(" %c", choice);
}
/******************
* Function Name:
    printMenu
* Input:
    function gets the adress of the variable that save the user choice.
* Output:
    void function doesnt return a value.
* Function Operation:
    the function prints the main menu and get the user choice.
******************/
void printMenu(char* choice)
{
    printf("Please select an operation:\n\t0. Exit.\n\t1. Create family.\n\t2. Add family member.\
\n\t3. Print Family-Tree.\n\t4. Bidud.\n\t5. Superspreader.\n\t6. Vaccine.\n\t7. Print the menu.\n");
    scanf(" %c", choice);
}
/******************
* Function Name:
    ifThereIsFamily
* Input:
    the function get the tree root.
* Output:
    the function return FALSE is there is no root
    and TRUE if the root exist.
* Function Operation:
    the function checks if the root is NULL,
    if it is its print a massage ang return FALSE, else return TRUE.
******************/
int ifThereIsFamily(Trin_Ari* root)
{
    if (root == NULL)
    {
        printf("Please create the family first\n");
        return FALSE;
    }
    return TRUE;
}
/******************
* Function Name:
    ifIdExist
* Input:
    the function gets an id member and the tree root
* Output:
    function returns a pointer to node or NULL 
* Function Operation:
    the function check by recursion calls if the member with the id exist,
    if the function found the member its return a pointer to this member
    else,returning NULL.
******************/
Trin_Ari* ifIdExist(Trin_Ari* root,int searchID)
{
    Trin_Ari* theMember;
    if (root->id == searchID)
        return root;
    if(root->left)
        if ((theMember = ifIdExist(root->left, searchID)) != NULL)
            return theMember;
    if (root->middle)
        if ((theMember = ifIdExist(root->middle, searchID)) != NULL)
            return theMember;
    if (root->right)
        return ifIdExist(root->right, searchID);
    return NULL;
}
/******************
* Function Name:
    getNewMemberData
* Input:
    function gets the tree root, and adress of variable the 
    save the member id and name.
* Output:
    int function, returning FALSE if the id is already exist 
    and TRUE if the id doesnt exist.
* Function Operation:
    the function first get the user id and name,
    than check if the id is already exist.
******************/
int getNewMemberData(Trin_Ari* root,int* id, char* memberName)
{
    printf("enter name\n");
    scanf(" %[^\n]",memberName);
    printf("enter ID\n");
    scanf("%d",id);
    //if there is no root so no need to check.
    if (root != NULL)
    {
        //checks if the id exist
        Trin_Ari* newMember=ifIdExist(root, *id);
        if (newMember != NULL)
        {
            //if the id is already exist
            printf("ID %d belongs to %s\n", newMember->id, newMember->name);
            return FALSE;
        }
    }
    return TRUE;
}
/******************
* Function Name:
    initializeNull
* Input:
    function get tree Node.
* Output:
    void function doesnt return a value.
* Function Operation:
    the function intialize all the node pointers to NULL.
******************/
void initializeNull(Trin_Ari* nodeP)
{
    nodeP->name = NULL;
    nodeP->left = NULL;
    nodeP->middle = NULL;
    nodeP->right = NULL;
    nodeP->myFather = NULL;
}
/******************
* Function Name:
    mallocFailed
* Input:
    gets the tree root
* Output:
    exit the program.
* Function Operation:
    the function print that the malloc failed free all the allocated memory
    and exit the program.
******************/
void mallocFailed(Trin_Ari* root)
{
    printf("Malloc Failed!\n");
    freeTree(root);
    exit(1);
}
/******************
* Function Name:
    createNode
* Input:
     function gets the tree root, and string the 
    save the member name,and variable of the member ID
* Output:
    return pointer to node in the tree.
* Function Operation:
    the function allocate memory for new family member and for his name.
    then initialize the id and the name with the input that the function gets.
******************/
Trin_Ari* createNode(Trin_Ari* root,int memberID,char* memberName)
{ 
    Trin_Ari* newMember = (Trin_Ari*)malloc(sizeof(Trin_Ari));
   //check if malloc failed
    if (!newMember)
        mallocFailed(root);
    initializeNull(newMember);
    //allocate memory for the name.
    newMember->name = (char*)malloc(sizeof(char) * MAX_NAME_LENGTH);
    if (!(newMember->name))
    {
        free(newMember);
        mallocFailed(root);
    }
    strcpy(newMember->name,memberName);
    newMember->id = memberID;
    printf("Hello %s, ID: %d\n", memberName, memberID);                        
    if (root != NULL)
    {
        //link the new member to the correct place in the family tree.
        if (root->left == NULL)
        {
            root->left = newMember;
            newMember->myFather = root;
        }
        else if (root->middle == NULL)
        {
            root->middle = newMember;
            newMember->myFather = root;
        }
        else if (root->right == NULL)
        {
            root->right = newMember;
            newMember->myFather = root;
        }
    }
    return newMember;
}
/******************
* Function Name:
    addNewMember
* Input:
    function gets the tree root, and string the 
    save the member name,and variable of the member ID
* Output:
    int function return FALSE if there is no root.
* Function Operation:
    the function gets data about the new family member
    and checks if the new id is already exist,
    than checks if hte father has already 3 children.
    if the id already exist, we keep on asking for new data
    until the user enter some legal id.
******************/
int addNewMember(Trin_Ari* root,int memberID,char* memberName)
{
   //checks if there is a root.
    if (!ifThereIsFamily(root))
        return FALSE;
    int theMemberID;
    Trin_Ari* theFather = NULL;
    //ask the user to whom he want to add a son.
    printf("Enter the ID of the person who wants to make an appointment?\n");
    scanf("%d", &theMemberID);
    //checks if the id is already exist
    theFather = ifIdExist(root, theMemberID);
    if (!theFather)
    {
         printf("There is no ID %d\n", theMemberID);
         return FALSE;
    }
    //checks if the father already got 3 sons
    if ((theFather->right != NULL) && (theFather->middle != NULL) && (theFather->right != NULL))
    {
         printf("%s ID: %d can't meet more than 3 members!\n", theFather->name, theFather->id);
         return FALSE;
    }
    //ask data until the id is legal.
    while (!getNewMemberData(root, &memberID, memberName));
    //create the new node of the new member after the id is legal.
    createNode(theFather, memberID, memberName);
    return TRUE;
}
/******************
* Function Name:
    printsPrintMenu
* Input:
    gets the adress of choice variable
* Output:
    void function doesnt return a value.
* Function Operation:
    print the prints menu and gets the user choice.
******************/
void printsPrintMenu(char* choice)
{
    printf("Please select an operation:\n\t0. Return to the main menu.\n\t1. Print Trin-Ari family.\
\n\t2. Print Pre-order.\n\t3. Print Left-order.\n\t4. Print BFS.\n");
    scanf(" %c", choice);
}
/******************
* Function Name:
    printTreeOptions
* Input:
    function gets the tree root and pointer to function.
* Output:
    void function
* Function Operation:
    the function have switch case that manage the prints menu
******************/
void printTreeOptions(Trin_Ari* root,void(*funP)(Trin_Ari*))
{
    char printChoice;
    int indicator = TRUE;
    printsPrintMenu(&printChoice);
    //if indicator is TRUE we ask the user to choose again an operation.
    while (indicator)
    {
        switch (printChoice)
        {
        case RETURN_MAIN_MENU:
            indicator = FALSE;
            return;
            break;
        case PRINT_FAMILY:
            if (!root)
                return;
            print2DUtil(root, SPACE);
            indicator = FALSE;
            break;
        case PRINT_PRE_ORDER:
            if (!root)
                return;
            indicator = FALSE;
            printPreOrder(root);
            break;
        case PRINT_LEFT_ORDER:
            if (!root)
                return;
            indicator = FALSE;
            printLeftOrder(root);
            break;
        case PRINT_BFS:
            if (!root)
                return;
            indicator = FALSE;
            //using the pointer function for the right print.
            printBFS(root, funP);
            break;
       //if the user choose an ilegal option.
        default:
            printf("Error: unrecognized operation.\n");
            printsPrintMenu(&printChoice);
        }
    }
    return;
}
/******************
* Function Name:
    insulationCov19
* Input:
    function gets the tree root
* Output:
    void function
* Function Operation:
    the function prints who need to go over for insulation.
******************/
void insulationCov19(Trin_Ari* root)
{
    if (!ifThereIsFamily(root))
        return;
    int suspecteID;
    Trin_Ari* theSuspecte;
    printf("Enter the ID of the suspected member\n");
    scanf("%d", &suspecteID);
    //checks if the id of the suspecte exist.
    theSuspecte = ifIdExist(root, suspecteID);
    if (!theSuspecte)
    {
        printf("ID %d does not exist\n", suspecteID);
        return;
    }
    //checks if the father and the sons of the suspecte exist, and print them if they are.
    if(theSuspecte != root)
        printf("#StayHome! %s %d\n", theSuspecte->myFather->name, theSuspecte->myFather->id);
    printf("#StayHome! %s %d\n", theSuspecte->name, theSuspecte->id);
    if(theSuspecte->left)
        printf("#StayHome! %s %d\n", theSuspecte->left->name, theSuspecte->left->id);
    if (theSuspecte->middle)
        printf("#StayHome! %s %d\n", theSuspecte->middle->name, theSuspecte->middle->id);
    if (theSuspecte->right)
        printf("#StayHome! %s %d\n", theSuspecte->right->name, theSuspecte->right->id);
}
/******************
* Function Name:
    superSpreader
* Input:
    gets the tree root, and pointer to a function.
* Output:
    void function
* Function Operation:
    the function print the screen the members that need to go over for insulation.
******************/
void superSpreader(Trin_Ari* root,void(*funP)(Trin_Ari*))
{
    if (!ifThereIsFamily(root))
        return;
    int spreaderID = FALSE;
    Trin_Ari* theSuspecte = NULL;
    printf("Enter the ID of the suspected Superspreader\n");
    scanf("%d", &spreaderID);
    //checks if the ID exist
    if (!(theSuspecte=ifIdExist(root, spreaderID)))
    {
        printf("ID %d does not exist\n", spreaderID);
        return;
    }
    //print with bfs algorithem all the members that need an insulation.
    if(theSuspecte!=root)
        printf("#StayHome! %s %d\n", theSuspecte->myFather->name, theSuspecte->myFather->id);
    //using the function pointer to get the right print.
    printBFS(theSuspecte,funP);
}
/******************
* Function Name:
    freeTree
* Input:
    gets the tree root
* Output:
    void function
* Function Operation:
    the function free the allocted memory from the root its get and down.
    print a massage that the member survived.
******************/
void freeTree(Trin_Ari* root)
{
    //stop condition fot the recursion calls.
    if (root == NULL)
        return;
    if (root->left != NULL)
        freeTree(root->left);
    if (root->middle != NULL)
        freeTree(root->middle);
    if ((root)->right != NULL)
        freeTree(root->right);
    printf("%s ID: %d Survived!\n", root->name, root->id);
    //free the allocated memory
    free(root->name);
    free(root);
}
/******************
* Function Name:
    gotVaccine
* Input:
    gets the tree root.
* Output:
    return TRUE if the tree root got the vaccine, else return FALSE.
* Function Operation:
    the function free all the sub tree of the member the got the vaccine.
******************/
int gotVaccine(Trin_Ari* root)
{
    if (!ifThereIsFamily(root))
        return FALSE;
    int gotVaccine;
    Trin_Ari* theMemberWithVaccine;
    printf("Who got vaccinated (ID)?\n");
    scanf("%d", &gotVaccine);
    //checks if the member exist
    theMemberWithVaccine = ifIdExist(root, gotVaccine);
    if (!theMemberWithVaccine)
    {
        printf("There is no ID %d\n", gotVaccine);
        return FALSE;
    }
    //checks if the vaccined member is the tree root
    if (theMemberWithVaccine->id == root->id)
    {
        freeTree(theMemberWithVaccine);
        return TRUE;
    }
    //initialize the pointer to the vaccined member to NULL.
    if (theMemberWithVaccine->myFather->left == theMemberWithVaccine)
        theMemberWithVaccine->myFather->left = NULL;
    else if (theMemberWithVaccine->myFather->middle == theMemberWithVaccine)
        theMemberWithVaccine->myFather->middle = NULL;
    else
        theMemberWithVaccine->myFather->right = NULL;
    //free the vaccined member and all his sub tree.
    freeTree(theMemberWithVaccine);
    return FALSE;
}
/******************
* Function Name:
    printBidud
* Input:
    gets node in the tree
* Output:
    void function
* Function Operation:
    print massage to the screen
******************/
void printBidud(Trin_Ari* current)
{
    printf("#StayHome! %s %d\n", current->name, current->id);
}
/******************
* Function Name:
    printTheBFS
* Input:
    gets node in the tree
* Output:
    void function
* Function Operation:
    print massage to the screen.
******************/
void printTheBFS(Trin_Ari* current)
{
    printf("%s %d\n", current->name, current->id);
}
/******************
* Function Name:
    printBFS
* Input:
    function gets the tree root and pointer to a function.
* Output:
    void function
* Function Operation:
    the function manage the calls for the functions that 
    responsible about the queue.
******************/
void printBFS(Trin_Ari* root,void(*funP)(Trin_Ari*))
{
    Trin_Ari* current = root;
    //create the queue
    Queue* listP = createQueue(&listP);
    if (!listP)
        mallocFailed(root);
    //checks if the main root has sons
    if (current->left)
        if (!enQueue(listP, current->left))
            mallocFailed(root);
    if (current->middle)
        if (!enQueue(listP, current->middle))
            mallocFailed(root);
    if (current->right)
        if (!enQueue(listP, current->right))
            mallocFailed(root);
    funP(current);
    //while linked list (the queue) isnt empty.
    while (!isEmpty(listP))
    {
        //initialize the current to point for the first node in the queue.
        current = listP->front->key;
        //using the function pointer to print the correct massage.
        funP(current);
        //free the first node 
        deQueue(listP); 
        if (current->left)
            if (!enQueue(listP, current->left))
                mallocFailed(root);
        if (current->middle)
            if (!enQueue(listP, current->middle))
                mallocFailed(root);
        if (current->right)
            if (!enQueue(listP, current->right))
                mallocFailed(root);
    }
    //after the queue empty we free the queue .
    destroyQueue(listP);
}
