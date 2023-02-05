#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ll long long

typedef struct Elem Elem;
struct Elem {
    struct Elem *next;
    char *word;
};

void InitSingleLinkedList(Elem **List)
{
    (*List) = NULL;
}

Elem *InsertBefore(Elem *Next, char *word)
{
    Elem *temp = (Elem *)malloc(sizeof(Elem));
    temp->word = word;
    temp->next = Next;
    return temp;
}

void swap(Elem *first, Elem *second) {
    char *temp = first->word;
    first->word = second->word;
    second->word = temp;
}

Elem* bsort(Elem *list)
{
    Elem* bound = NULL;
    while (bound != list) {
        Elem *i = list;
        while (i->next != bound) {
            if (strlen(i->next->word) < strlen(i->word)) {
                swap(i->next, i);
            }
            i = i->next;
        }
        bound = i;
    }
    return list;
}

int get_count_and_words(char *s, char ***a)
{
    char **words = NULL;
    char *word = NULL;
    char c = 1;
    int wcount = 0;
    int chcount = 0;
    while (c != '\0') {
        c = *(s);
        ++s;
        if (c != '\0' && c != ' ') {
            if (chcount == 0) {
                word = malloc(2);
            } else {
                word = realloc(word, chcount + 1);
            }
            *(chcount+word) = c;
            ++chcount;
        } else if (chcount) {
            word = realloc(word, chcount+1);
            word[chcount] = '\0';
            chcount = 0;
            words = realloc(words, sizeof(char *) * (wcount+1));
            *(wcount+words) = word;
            ++wcount;
        }
    }
    *a = words;
    return wcount;
}


char *get_fstr()
{
    int len = 0;
    int cap = 1;
    char *s = (char*) malloc(sizeof(char)+1);
    char c = (char)getchar();
    while (c == ' ') {
        c = (char)getchar();
    }
    while (c != '\n') {
        if (len>0) {
            if (s[len-1] == ' ' && c == ' ') {
                c = (char)getchar();
                continue;
            }
        }
        s[len++] = c;
        if (len > cap - 1) {
            cap *= 2;
            s = (char *)realloc(s, cap * sizeof(char));
        }

        c = (char)getchar();
    }
    if (s[len-1] == ' ') {
        s[len-1] = '\0';
    } else {
        s[len] = '\0';
    }
    return s;
}

int main() 
{
    char *src = get_fstr();
    char **words;
    ll n = get_count_and_words(src, &words);
    Elem *list;
    InitSingleLinkedList(&list);
    for (ll i=n-1;i>=0;--i) {
        list = InsertBefore(list, words[i]);
    }
    list = bsort(list);
    Elem *X = list;
    for (; X != NULL;) {
        printf("%s ", X->word);
        X = X->next;
    }
    for (; list != NULL; ) {
        Elem *Next = list->next;
        free(list->word);
        free(list);
        list = Next;
    }

    free(src);
    free(words);
    return 0;
}
