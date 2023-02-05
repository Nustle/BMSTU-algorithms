#include <stdio.h>

struct Elem {
    /* «Тег», описывающий тип значения в «головe» списка */
    enum {
        INTEGER,
        FLOAT,
        LIST
    } tag;

    /* Само значение в «голове» списка */
    union {
        int i;
        float f;
        struct Elem *list;
    } value;

    /* Указатель на «хвост» списка */
    struct Elem *tail;
};

struct Elem *searchlist(struct Elem *list, int k)
{
    struct Elem* res = NULL;
    while (list != NULL || res != NULL) {
        if (list->tag == INTEGER && list->value.i == k) {
            res = list;
            break;
        } else if (list->tag == LIST) {
            res = searchlist(list->value.list, k);
        }
        list = list->tail;
    }
    return res;
}
