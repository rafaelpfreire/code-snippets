#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#define ERRLL_SUCCESS      0 // Success
#define ERRLL_NULL_LIST    1 // List is nullptr
#define ERRLL_IDX_OOB      2 // Index out of bound
#define ERRLL_EMPTY        3 // Empty list

typedef struct LinkedListNode_t
{
    void *data;
    struct LinkedListNode_t *previous;
    struct LinkedListNode_t *next;
}LinkedListNode_t;

typedef struct LinkedList_t
{
    LinkedListNode_t *head;
    LinkedListNode_t *tail;
}LinkedList_t;

LinkedList_t* llist_init();
LinkedListNode_t* llist_node_init();
uint32_t llist_length(LinkedList_t *list);
uint32_t llist_get(LinkedList_t *list, uint32_t index, LinkedListNode_t *node);
uint32_t llist_set(LinkedList_t *list, uint32_t index, void *data);
uint32_t llist_insert(LinkedList_t *list, uint32_t index, void *data);
uint32_t llist_pop(LinkedList_t *list, uint32_t index, LinkedListNode_t *ret);
uint32_t llist_append(LinkedList_t *list, void *data);
uint32_t llist_prepend(LinkedList_t *list, void *data);
char* llist_error_str(int32_t errorcode);

#endif //_LINKEDLIST_H_
