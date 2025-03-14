#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void list_insert_before(list_t *l,
                        list_item_t *before,
                        list_item_t *item)
{
    list_item_t **p;
    for (p = &l->head; *p != before; p = &(*p)->next)
        ;
    *p = item;
    item->next = before;
}

size_t list_size(const list_t *l)
{
    size_t count = 0;
    list_item_t *cur = l->head;
    while (cur)
    {
        count++;
        cur = cur->next;
    }
    return count;
}

static list_item_t *merge_list(list_item_t *first, list_item_t *second)
{
    list_item_t dummy = {0, NULL};
    list_item_t **tail = &dummy.next;

    list_item_t **first_ptr = &first;
    list_item_t **second_ptr = &second;

    while ((*first_ptr) != NULL && (*second_ptr) != NULL)
    {
        list_item_t **small = (*first_ptr)->value < (*second_ptr)->value ? first_ptr : second_ptr;
        *tail = *small;
        tail = &(*tail)->next;
        *small = (*small)->next;
    }

    *tail = (*first_ptr != NULL) ? *first_ptr : *second_ptr;
    return dummy.next;
}

static list_item_t *list_find_mid(list_item_t *head)
{
    list_item_t *fast = head->next;
    list_item_t *mid = head;

    while (fast != NULL && (fast)->next != NULL)
    {
        fast = fast->next->next;
        mid = mid->next;
    }
    return mid;
}

void list_sort(list_t *head)
{
    list_item_t *first = head->head;
    list_item_t *mid = list_find_mid(head->head);
    if (mid == NULL || mid->next == NULL)
    {
        return;
    }
    list_item_t *second = mid->next;
    mid->next = NULL;

    list_t left_list;
    left_list.head = first;
    list_t right_list;
    right_list.head = second;

    list_sort(&left_list);
    list_sort(&right_list);
    head->head = merge_list(left_list.head, right_list.head);
}