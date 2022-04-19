#include "linkedlist.h"
#include <string.h>
#include <stdio.h>

LinkedListNode_t* llist_node_init()
{
    LinkedListNode_t *node = (LinkedListNode_t*) malloc(sizeof(LinkedListNode_t));

    node->next = NULL;
    node->previous = NULL;

    return node;
}

LinkedList_t* llist_init()
{
    LinkedList_t *list = (LinkedList_t*) malloc(sizeof(LinkedList_t));

    list->head = NULL;
    list->tail = NULL;

    return list;
}

uint32_t llist_length(LinkedList_t *list)
{
    uint32_t length = 1;

    if(NULL == list)
    {
        return 0;
    }
    else if(NULL == list->head)
    {
        return 0;
    }

    LinkedListNode_t *node = list->head;

    while(node != list->tail)
    {
        length++;
        node = node->next;
    }

    return length;
}

uint32_t llist_get(LinkedList_t *list, uint32_t index, LinkedListNode_t *ret)
{
    if(NULL == list)
    {
        return ERRLL_NULL_LIST;
    }
    else if(NULL == list->head)
    {
        return ERRLL_EMPTY;
    }

    int i = 0;
    LinkedListNode_t *aux = list->head;

    while((aux != list->tail) && (i < index))
    {
        i++;
        aux = aux->next;
    }

    if(i < index)
    {
        return ERRLL_IDX_OOB;
    }

    memcpy(ret, aux, sizeof(LinkedListNode_t));

    return ERRLL_SUCCESS;
}

uint32_t llist_set(LinkedList_t *list, uint32_t index, void *data)
{
    if(NULL == list)
    {
        return ERRLL_NULL_LIST;
    }
    else if(NULL == list->head)
    {
        return ERRLL_EMPTY;
    }

    int i = 0;
    LinkedListNode_t *aux = list->head;

    while((aux != list->tail) && (i < index))
    {
        i++;
        aux = aux->next;
    }

    if(i < index)
    {
        return ERRLL_IDX_OOB;
    }

    aux->data = data;

    return ERRLL_SUCCESS;
}

uint32_t llist_insert(LinkedList_t *list, uint32_t index, void *data)
{
    if(NULL == list)
    {
        return ERRLL_NULL_LIST;
    }

    int i = 0;
    LinkedListNode_t *aux = list->head;

    LinkedListNode_t *node = llist_node_init();
    node->data = data;

    if(NULL == list->head)
    {
        list->head = node;
        list->tail = node;

        return ERRLL_SUCCESS;
    }
    else if(list->head == list->tail)
    {
        list->head = node;
        list->tail->previous = node;
        node->next = list->tail;

        return ERRLL_SUCCESS;
    }

    while((aux != list->tail) && (i < index))
    {
        i++;
        aux = aux->next;
    }

    if(i < index)
    {
        return ERRLL_IDX_OOB;
    }

    if(aux == list->head)
    {
        node->next = aux;
        aux->previous = node;
        list->head = node;
    }
    else if(aux == list->tail)
    {
        node->next = aux;
        aux->previous = node;
        list->tail = node;
    }
    else
    {
        node->previous = aux->previous;
        node->next = aux;
        aux->previous->next = node;
        aux->previous = node;
    }

    return ERRLL_SUCCESS;
}

uint32_t llist_pop(LinkedList_t *list, uint32_t index, LinkedListNode_t *ret)
{
    if(NULL == list)
    {
        return ERRLL_NULL_LIST;
    }
    else if(NULL == list->head)
    {
        return ERRLL_EMPTY;
    }

    int i = 0;
    LinkedListNode_t *aux = list->head;

    while((aux != list->tail) && (i < index))
    {
        i++;
        aux = aux->next;
    }

    if(i < index)
    {
        return ERRLL_IDX_OOB;
    }

    if(list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else if(aux == list->head)
    {
        aux->next->previous = NULL;
        list->head = aux->next;
    }
    else if(aux == list->tail)
    {
        aux->previous->next = NULL;
        list->tail = aux->previous;
    }
    else
    {
        aux->previous->next = aux->next;
        aux->next->previous = aux->previous;
    }

    aux->next = NULL;
    aux->previous = NULL;
    memcpy(ret, aux, sizeof(LinkedListNode_t));
    free(aux);

    return ERRLL_SUCCESS;
}

uint32_t llist_append(LinkedList_t *list, void *data)
{
    if(NULL == list)
    {
        return ERRLL_NULL_LIST;
    }

    LinkedListNode_t *node = llist_node_init();
    node->data = data;

    if(NULL == list->head)
    {
        list->head = node;
    }
    else if(NULL == list->head->next)
    {
        node->previous = list->head;
        list->head->next = node;
    }
    else
    {
        node->previous = list->tail;
        list->tail->next = node;
    }

    list->tail = node;

    return ERRLL_SUCCESS;
}

uint32_t llist_prepend(LinkedList_t *list, void *data)
{
    if(NULL == list)
    {
        return ERRLL_NULL_LIST;
    }

    LinkedListNode_t *node = llist_node_init();
    node->data = data;

    if(NULL == list->head)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = list->head;
        list->head->previous = node;
        list->head = node;
    }

    return ERRLL_SUCCESS;
}
