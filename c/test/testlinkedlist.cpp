#include "gtest/gtest.h"

extern "C" {
#include "linkedlist.h"
}

TEST(TestLinkedList, AppendWhenListIsNull)
{
    int val = 10;
    LinkedList_t *list = nullptr;
    ASSERT_EQ(llist_append(list, (void*)&val), ERRLL_NULL_LIST);
}

TEST(TestLinkedList, PrependWhenListIsNull)
{
    int val = 10;
    LinkedList_t *list = nullptr;
    ASSERT_EQ(llist_prepend(list, (void*)&val), ERRLL_NULL_LIST);
}

TEST(TestLinkedList, LengthWhenListIsNull)
{
    LinkedList_t *list = nullptr;
    ASSERT_EQ(llist_length(list), 0);
}

TEST(TestLinkedList, PrependSingleNode)
{
    LinkedList_t *list = llist_init();

    int val = 50;
    llist_prepend(list, (void*)&val);

    ASSERT_EQ(list->head, list->tail);
    ASSERT_EQ(*(uint32_t*)list->head->data, 50);
    ASSERT_EQ(*(uint32_t*)list->tail->data, 50);
    ASSERT_EQ(list->head->next, nullptr);
    ASSERT_EQ(list->head->previous, nullptr);
    ASSERT_EQ(list->tail->next, nullptr);
    ASSERT_EQ(list->tail->previous, nullptr);
    ASSERT_EQ(llist_length(list), 1);
}

TEST(TestLinkedList, AppendSingleNode)
{
    LinkedList_t *list = llist_init();

    int val = 50;
    llist_append(list, (void*)&val);

    ASSERT_EQ(list->head, list->tail);
    ASSERT_EQ(*(uint32_t*)list->head->data, 50);
    ASSERT_EQ(*(uint32_t*)list->tail->data, 50);
    ASSERT_EQ(list->head->next, nullptr);
    ASSERT_EQ(list->head->previous, nullptr);
    ASSERT_EQ(list->tail->next, nullptr);
    ASSERT_EQ(list->tail->previous, nullptr);
    ASSERT_EQ(llist_length(list), 1);
}

TEST(TestLinkedList, LengthTwoNodes)
{
    LinkedList_t *list = llist_init();

    int val1 = 50;
    int val2 = 100;
    llist_append(list, (void*)&val1);
    llist_prepend(list, (void*)&val2);

    ASSERT_NE(list->head, list->tail);
    ASSERT_EQ(*(uint32_t*)list->head->data, 100);
    ASSERT_EQ(*(uint32_t*)list->tail->data, 50);
    ASSERT_EQ(list->head->next, list->tail);
    ASSERT_EQ(list->head->previous, nullptr);
    ASSERT_EQ(list->tail->next, nullptr);
    ASSERT_EQ(list->tail->previous, list->head);
    ASSERT_EQ(llist_length(list), 2);
}

TEST(TestLinkedList, LengthThreeNodes)
{
    LinkedList_t *list = llist_init();

    int val1 = 50;
    int val2 = 100;
    int val3 = 150;
    llist_append(list, (void*)&val1);
    llist_append(list, (void*)&val2);
    llist_prepend(list, (void*)&val3);

    ASSERT_NE(list->head, list->tail);
    ASSERT_EQ(*(uint32_t*)list->head->data, 150);
    ASSERT_EQ(*(uint32_t*)list->tail->data, 100);
    ASSERT_EQ(list->tail->previous, list->head->next);
    ASSERT_EQ(list->head->previous, nullptr);
    ASSERT_EQ(list->tail->next, nullptr);
    ASSERT_EQ(llist_length(list), 3);
}

TEST(TestLinkedList, LengthMultipleNodes)
{
    uint32_t length = 10;
    LinkedList_t *list = llist_init();

    for(int i = 0; i < length; i++)
    {
        int *aux = (int*) malloc(sizeof(int));
        *aux = i;
        llist_append(list, (void*)aux);
    }

    ASSERT_EQ(llist_length(list), length);
    ASSERT_EQ(*(uint32_t*)list->head->data, 0);
    ASSERT_EQ(*(uint32_t*)list->tail->data, length-1);
}

TEST(TestLinkedList, PopMultipleInTheMiddleOfList)
{
    uint32_t length = 10;
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();

    for(int i = 0; i < length; i++)
    {
        int *aux = (int*) malloc(sizeof(int));
        *aux = i;
        llist_append(list, (void*)aux);
    }

    ASSERT_EQ(llist_pop(list,5,read), ERRLL_SUCCESS);
    ASSERT_EQ(*(int*)read->data, 5);
    ASSERT_EQ(llist_pop(list,3,read), ERRLL_SUCCESS);
    ASSERT_EQ(*(int*)read->data, 3);
    ASSERT_EQ(llist_length(list), length-2);
    ASSERT_EQ(*(uint32_t*)list->head->data, 0);
    ASSERT_EQ(*(uint32_t*)list->tail->data, length-1);
}

TEST(TestLinkedList, PopIndexOutOfBound)
{
    uint32_t length = 10;
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();

    for(int i = 0; i < length; i++)
    {
        int *aux = (int*) malloc(sizeof(int));
        *aux = i;
        llist_append(list, (void*)aux);
    }

    ASSERT_EQ(llist_pop(list,length+1,read), ERRLL_IDX_OOB);
}

TEST(TestLinkedList, PopEmptyList)
{
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();
    ASSERT_EQ(llist_pop(list,0,read), ERRLL_EMPTY);
}

TEST(TestLinkedList, PopHead)
{
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();

    int val = 10;
    llist_append(list, (void*)&val);
    llist_append(list, (void*)&val);

    ASSERT_EQ(llist_pop(list,0,read), ERRLL_SUCCESS);
    ASSERT_EQ(list->head, list->tail);
}

TEST(TestLinkedList, PopTail)
{
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();

    int val = 10;
    llist_append(list, (void*)&val);
    llist_append(list, (void*)&val);

    ASSERT_EQ(llist_pop(list,1,read), ERRLL_SUCCESS);
    ASSERT_EQ(list->head, list->tail);
}

TEST(TestLinkedList, PopAll)
{
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();

    int val = 10;
    llist_append(list, (void*)&val);
    llist_append(list, (void*)&val);
    llist_append(list, (void*)&val);

    ASSERT_EQ(llist_pop(list,0,read), ERRLL_SUCCESS);
    ASSERT_EQ(llist_pop(list,0,read), ERRLL_SUCCESS);
    ASSERT_EQ(llist_pop(list,0,read), ERRLL_SUCCESS);
    ASSERT_EQ(llist_pop(list,0,read), ERRLL_EMPTY);
}

TEST(TestLinkedList, SetAndGet)
{
    LinkedList_t *list = llist_init();
    LinkedListNode_t *read = llist_node_init();

    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    int val4 = 100;

    ASSERT_EQ(llist_set(list,0,(void*)&val4), ERRLL_EMPTY);
    ASSERT_EQ(llist_get(list,0,read), ERRLL_EMPTY);

    llist_append(list, (void*)&val1);
    llist_append(list, (void*)&val2);
    llist_append(list, (void*)&val3);

    ASSERT_EQ(llist_set(list,1,(void*)&val4), ERRLL_SUCCESS);
    ASSERT_EQ(llist_set(list,4,(void*)&val4), ERRLL_IDX_OOB);
    ASSERT_EQ(llist_get(list,1,read), ERRLL_SUCCESS);
    ASSERT_EQ(llist_get(list,4,read), ERRLL_IDX_OOB);
    ASSERT_EQ(*(int*)list->head->data, val1);
    ASSERT_EQ(*(int*)list->head->next->data, val4);
    ASSERT_EQ(*(int*)list->tail->data, val3);
    ASSERT_EQ(*(int*)read->data, val4);
}

TEST(TestLinkedList, Insert)
{
    LinkedList_t *list = llist_init();

    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    int vali = 100;

    ASSERT_EQ(llist_insert(list, 0, (void*)&val3), ERRLL_SUCCESS);
    ASSERT_EQ(llist_insert(list, 0, (void*)&val2), ERRLL_SUCCESS);
    ASSERT_EQ(llist_insert(list, 0, (void*)&val1), ERRLL_SUCCESS);
    ASSERT_EQ(llist_insert(list, 1, (void*)&vali), ERRLL_SUCCESS);
    ASSERT_EQ(llist_insert(list, 4, (void*)&vali), ERRLL_SUCCESS);
    ASSERT_EQ(llist_insert(list, 10, (void*)&vali), ERRLL_IDX_OOB);
    ASSERT_EQ(*(int*)list->head->data, val1);
    ASSERT_EQ(*(int*)list->head->next->data, vali);
    ASSERT_EQ(*(int*)list->head->next->next->data, val2);
    ASSERT_EQ(*(int*)list->tail->previous->data, val1);
    ASSERT_EQ(*(int*)list->tail->data, val3);
}
