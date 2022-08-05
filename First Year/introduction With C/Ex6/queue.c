/***********************
* Tomer
* ex6
***********************/
#include "queue.h"
#include "ex6.h"
/******************
* Function Name:
    createQueue
* Input:
    gets an adress of a pointer.
* Output:
    return pointer for the queue
* Function Operation:
    function allocate a struct that help us manage the queue.
******************/
Queue* createQueue(Queue** listP)
{
    //alocated memory for the struct that point the queue
    (*listP) = (Queue*)malloc(sizeof(Queue));
    if (!(*listP))
        return(*listP);
    (*listP)->front = NULL;
    (*listP)->rear = NULL;
    return (*listP);
}
/******************
* Function Name:
    enQueue
* Input:
    gets a pointer to the queue and generic pointer
* Output:
    int function- returning FALSE if malloc failed.
* Function Operation:
    the function allocate memory for a new node and add him
    to the end of the list. and linked the new node with the list
******************/
int enQueue(Queue* q, void* k)
{
    QNode* node = (QNode*)malloc(sizeof(QNode));
    //checks if malloc failed.
    if (!node)
    {
        destroyQueue(q);
        return FALSE;
    }
    node->next = NULL;
    node->perv = NULL;
    node->key = k;
    //if the node is the first in the queue
    if (!q->front)
    {
        q->front = node;
        q->rear = node;
        return TRUE;
    }
    //linked the new node to the list.
    node->next = q->rear;
    q->rear->perv = node;
    q->rear = node;
    return TRUE;
}
/******************
* Function Name:
    deQueue
* Input:
    gets pointer for the queue
* Output:
    void function
* Function Operation:
    function free the first node in the queue and
    initialize the front pointer to point the second node that 
    becoming the first.
******************/
void deQueue(Queue* q)
{
    //using temp to save the acces for the list.
    QNode* temp = q->front->perv;
    free(q->front);
    q->front = temp;
}
/******************
* Function Name:
    isEmpty
* Input:
    gets pointer for the queue
* Output:
    return TRUE if the queue empty, else FALSE.
* Function Operation:
    check if the queue is empty
******************/
int isEmpty(Queue* q)
{
    if (!q->front)
        return TRUE;
    return FALSE;
}
/******************
* Function Name:
    destroyQueue
* Input:
    gets pointer to the queue
* Output:
    void function
* Function Operation:
    free all the nodes in the queue and the the queue it self.
******************/
void destroyQueue(Queue* q)
{
    QNode* temp;
   //while loop until the queue empty
    while (q->front)
    {
        temp = q->rear->next;
        free(q->rear);
        q->rear = temp;
    }
   //free the pointer for the queue.
    free(q);
}
