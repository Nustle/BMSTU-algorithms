#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKLEN 1000000

struct Elem {
    int value, maxim;
};

struct Stack {
    struct Elem *vect;
    int len;
    int top1, top2;
};

int max(int a, int b)
{
    return (a>=b) ? a : b;
}

void InitStack(struct Stack *s)
{
    s->vect = (struct Elem*)malloc(STACKLEN*sizeof(struct Elem));
    s->len = STACKLEN;
    s->top1 = 0;
    s->top2 = STACKLEN-1;
}

void InitQueue(struct Stack *s)
{
    InitStack(s);
}

int StackEmpty1(struct Stack *s)
{
    int isEmpty = (s->top1 == 0) ? 1 : 0;
    return isEmpty;
}

int StackEmpty2(struct Stack *s)
{
    int isEmpty = (s->top2 == s->len-1) ? 1 : 0;
    return isEmpty;
}

int QueueEmpty(struct Stack *s)
{
    return StackEmpty1(s)*StackEmpty2(s);
}

void Push1(struct Stack *s, int elem)
{
    s->vect[s->top1].value = elem;
    s->vect[s->top1].maxim = !StackEmpty1(s) ? max(s->vect[s->top1-1].maxim, elem) : elem;
    ++s->top1;
}

void Push2(struct Stack *s, int elem)
{
    s->vect[s->top2].value = elem;
    s->vect[s->top2].maxim = !StackEmpty2(s) ? max(s->vect[s->top2+1].maxim, elem) : elem;
    --s->top2;
}

int Pop1(struct Stack *s)
{
    return s->vect[--s->top1].value;
}

int Pop2(struct Stack *s)
{
    return s->vect[++s->top2].value;
}

void Enqueue(struct Stack *s, int elem)
{
    Push1(s, elem);
}

int Dequeue(struct Stack *s)
{
    if (StackEmpty2(s) == 1) {
        while (StackEmpty1(s) == 0) {
            Push2(s, Pop1(s));
        }
    }
    return Pop2(s);
}

int Max(struct Stack *s)
{
    int m;
    if (StackEmpty1(s) == 1) {
        m =  s->vect[s->top2+1].maxim;
    } else if (StackEmpty2(s) == 1) {
        m = s->vect[s->top1-1].maxim;
    } else {
        m = max(s->vect[s->top2+1].maxim, s->vect[s->top1-1].maxim);
    }
    return m;
}

int main()
{
    struct Stack s;
    char b[5];
    InitQueue(&s);
    scanf("%s", b);
    while (strcmp(b, "END") != 0) {
        int elem;
        if (strcmp(b, "ENQ") == 0) {
            scanf(" %d", &elem);
            Enqueue(&s, elem);
        } else if (strcmp(b, "DEQ") == 0) {
            elem = Dequeue(&s);
            printf("%d", elem);
        } else if (strcmp(b, "MAX") == 0) {
            int m  = Max(&s);
            printf("%d", m);

        } else if (strcmp(b, "EMPTY") == 0) {
            if (QueueEmpty(&s)) {
                printf("true");
            } else {
                printf("false");
            }
        }
        if (strcmp(b, "DEQ") == 0 || strcmp(b, "EMPTY") == 0 || strcmp(b, "MAX") == 0) {
            printf("\n");
        }
        scanf("%s", b);
    }
    free(s.vect);
    return 0;
}
