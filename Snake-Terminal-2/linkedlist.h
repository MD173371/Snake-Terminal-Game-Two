/*FILE: linkedlist.h
AUTHOR: Michael Durkan
PURPOSE: Provide linked list function prototypes and struct typedefs
LAST MOD: May 18 2024  */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
} LinkedListNode;

typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int count;
} LinkedList;

LinkedList* createLinkedList(void);
void insertStart(LinkedList* list, void* entry);
void removeStart(LinkedList* list);
void freeLinkedList(LinkedList* list);

#endif
