/* FILE: linkedlist.c
AUTHOR: Michael Durkan
PURPOSE: Linked list creation and alteration functions.
LAST MOD: May 19 2024 */

#include <stdlib.h>
#include "linkedlist.h"

/*
NAME: createLinkedList
PURPOSE: Allocate the memory for the linkedlist and set its head and tail to 
         null and count to 0.
IMPORTS: none.
EXPORTS: none.
*/
LinkedList* createLinkedList( void )
{
    LinkedList* list;
    
    /* Create the linkedList in memory */
    list = ( LinkedList* )malloc(sizeof(LinkedList));
    
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

/*
NAME: insertStart
PURPOSE: Insert data into the first entry of the linkedlist.
IMPORTS: list and entry - Linked list and the data to be entered.
EXPORTS: none.
*/
void insertStart( LinkedList* list, void* entry )
{
    /* Create a new node */
    LinkedListNode* newNode;
    newNode = ( LinkedListNode* )malloc(sizeof(LinkedListNode));

    /* Data of new node points to value to be inserted */
    newNode->data = entry;
    newNode->next = NULL;
    
    /* Check if list is empty*/
    if ( list->tail == NULL )
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        /* "Next" must point to the existing first node */
        newNode->next = list->head;
        /* Head points to the new node */
        list->head = newNode;
        
    }

    ( list->count )++;
}

/*
NAME: removeStart
PURPOSE: remove/free the first entry in the linkedlist and free its dynamically
         allocated data.
IMPORTS: list - Linked list.
EXPORTS: none.
*/
void removeStart( LinkedList* list )
{
    if ( ( list->head != NULL ) && ( list->head != list->tail ) )
    {
        /* Store the original first entry */
        LinkedListNode* origFirst;
        origFirst = list->head;
        
        /* Make the list head point at the second value */
        list->head = list->head->next;
        
        /* Handle a single entry list */
        if ( list->head == NULL )
        {
            list->tail = NULL;
        }
        
        /* Free the data and node */
        free(origFirst->data);
        free(origFirst);
        origFirst = NULL;

        (list->count)--;
    }

}

/*
NAME: freeLinkedList
PURPOSE: Free the memory of the linkedlist including its dynamically allocated
         data.
IMPORTS: list - Linked list
EXPORTS: none.
*/
void freeLinkedList(LinkedList* list)
{
    LinkedListNode* curr;
    LinkedListNode* temp;
    
    /* Set current node to first entry in list  */
    curr = list->head;
    temp = NULL;

    while ( curr != NULL )
    {
        /* Set temp node to the next entry  */
        temp = curr->next;

        /* Free the data of the current node and the node itself  */
        free(curr->data);
        free(curr);

        /* Set current node to temp node (next node) */
        curr = temp;
    }
    /* Set count to zero, head and tail to null, and free the list */
    list->count = 0;
    list->head = NULL;
    list->tail = NULL;
    free(list);
}
