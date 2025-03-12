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