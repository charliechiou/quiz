#include <stdio.h>
#include <stdlib.h>

#include "list.h"

#define my_assert(test, message) \
    do                           \
    {                            \
        if (!(test))             \
            return message;      \
    } while (0)
#define my_run_test(test)       \
    do                          \
    {                           \
        char *message = test(); \
        tests_run++;            \
        if (message)            \
            return message;     \
    } while (0)

#define N 10

static list_item_t items[N];
static list_t l;

// Fisher-Yates Shuffle
void shuffle_items()
{
    for (size_t i = N - 1; i > 0; i--)
    {
        size_t j = rand() % (i + 1);
        list_item_t temp = items[i];
        items[i] = items[j];
        items[j] = temp;
    }
}

static list_t *list_reset(void)
{
    for (size_t i = 0; i < N; i++)
    {
        items[i].value = i;
        items[i].next = NULL;
    }
    l.head = NULL;
    return &l;
}

static void print_list(list_t *list)
{
    list_item_t *cur = list->head;
    while (cur)
    {
        printf("%d -> ", cur->value);
        cur = cur->next;
    }
    printf("NULL\n");
}

static char *test_list(void)
{
    /* Test inserting at the beginning */
    list_reset();
    my_assert(list_size(&l) == 0, "Initial list size is expected to be zero.");
    for (size_t i = 0; i < N; i++)
        list_insert_before(&l, l.head, &items[i]);
    my_assert(list_size(&l) == N, "Final list size should be N");
    size_t k = N - 1;
    list_item_t *cur = l.head;
    while (cur)
    {
        my_assert(cur->value == k, "Unexpected list item value");
        k--;
        cur = cur->next;
    }

    /* Test inserting at the end */
    list_reset();
    my_assert(list_size(&l) == 0, "Initial list size is expected to be zero.");
    for (size_t i = 0; i < N; i++)
        list_insert_before(&l, NULL, &items[i]);
    my_assert(list_size(&l) == N, "Final list size should be N");
    k = 0;
    cur = l.head;
    while (cur)
    {
        my_assert(cur->value == k, "Unexpected list item value");
        k++;
        cur = cur->next;
    }

    /* Reset the list and insert elements in order (i.e. at the end) */
    list_reset();
    my_assert(list_size(&l) == 0, "Initial list size is expected to be zero.");
    for (size_t i = 0; i < N; i++)
        list_insert_before(&l, NULL, &items[i]);
    my_assert(list_size(&l) == N, "list size should be N");

    return NULL;
}

static char *test_list_sort(void)
{
    list_reset();

    list_t list1 = {.head = NULL};
    list_t *list = &l;

    shuffle_items();

    for (size_t i = 0; i < N; i++)
    {
        list_insert_before(list, NULL, &items[i]);
    }

    my_assert(list_size(list) == N, "Initial list size should be N");

    printf("Before sorting:\n");
    print_list(list);

    list_sort(list);

    printf("After sorting:\n");
    print_list(list);

    list_item_t *cur = list->head;
    int prev_value = -1;
    while (cur)
    {
        my_assert(prev_value <= cur->value, "List is not sorted correctly!");
        prev_value = cur->value;
        cur = cur->next;
    }

    return NULL;
}

int tests_run = 0;

static char *test_suite(void)
{
    my_run_test(test_list);
    my_run_test(test_list_sort);
    return NULL;
}

int main(void)
{
    printf("---=[ List tests\n");
    char *result = test_suite();
    if (result)
        printf("ERROR: %s\n", result);
    else
        printf("ALL TESTS PASSED\n");
    printf("Tests run: %d\n", tests_run);
    return !!result;
}