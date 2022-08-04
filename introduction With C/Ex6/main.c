/***********************
* Tomer
* 207651027
* 01
* ex6
***********************/
#include "ex6.h"
/******************
on the main we have switch case that manage the menu.
while loop that last until the user choose 0.
******************/
int main()
{
    Trin_Ari* root=NULL;
    void (*funP)(Trin_Ari*) = NULL;
    char choice = FALSE,memberName[MAX_NAME_LENGTH];
    int memberID = FALSE;
    printMenu(&choice);
    //infinity loop until the user choose 0-for exit.
    while (1)
    {
        switch (choice)
        {
        case EXIT:
            freeTree(root);
            exit(1);
        case CREATE_FAMILY:
            if (root == NULL)
            {
                getNewMemberData(root, &memberID, memberName);
                root = createNode(root, memberID, memberName);
            }
            else
                printf("The family has already been created\n");
            printSelectOperation(&choice);
            break;
        case ADD_FAMILY_MEMBER:
            addNewMember(root, memberID, memberName);
            printSelectOperation(&choice);
            break;
        case PRINT_FAMILY_TREE:
            printTreeOptions(root,&printTheBFS);
            printMenu(&choice);
            break;
        case BIDUD:
            insulationCov19(root);
            printSelectOperation(&choice);
            break;
        case SUPER_SPREADER:
            superSpreader(root,&printBidud);
            printSelectOperation(&choice);
            break;
        case VACCINE:
            if (gotVaccine(root) == TRUE)
                root = NULL;
            printSelectOperation(&choice);
            break;
        case PRINT_MENU:
            printMenu(&choice);
            break;
        default:
            printSelectOperation(&choice);
        }           
    }
    return 0;
}