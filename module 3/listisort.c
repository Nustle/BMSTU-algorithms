#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STARTVALUE INT_MIN

typedef struct Elem Elem;
struct Elem {
    struct Elem *prev, *next;
    int v;
};

typedef struct DoubleLinkedList DoubleLinkedList;
struct DoubleLinkedList {
    struct Elem *prev, *next;
    int v;
};

void InsertBefore(Elem *first, Elem *second)
{
    Elem *temp = second->prev;
    first->next = second;
    second->prev = first;
    first->prev = temp;
    temp->next = first;
}


void InsertStep(DoubleLinkedList *list, int value)
{
    Elem *curr;
    Elem *elem = (Elem *)malloc(sizeof(Elem));
    elem->v = value;
    for (curr = list->next; !((curr->v >= value) || (curr == (Elem *)list)); curr = curr->next);
    InsertBefore(elem, curr);
}

void InitDoubleLinkedList(DoubleLinkedList *list)
{
    list->v = STARTVALUE;
    list->next = (Elem *)list;
    list->prev = (Elem *)list;
}

int Delete(Elem *elem) {
    Elem *first = elem->prev;
    Elem *second = elem->next;
    first->next = second;
    second->prev = first;
    int value = elem->v;
    free(elem);
    return value;
}

int main() 
{
    int n;
    DoubleLinkedList list;
    InitDoubleLinkedList(&list);
    scanf("%d,", &n);
    int step = 0;
    int elem;
    while (step<n) {
        scanf("%d", &elem);
        InsertStep(&list, elem);
        ++step;
    }
    for (int j=0; j<n; ++j) {
        printf("%d ", Delete(list.next));
    }
    return 0;
}
