#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
    int *vect;
    int top, len;
};

void InitStack(struct Stack *s, int n)
{
    s->vect = (int *)malloc(n*sizeof(int));
    s->top = 0;
    s->len = 1;
}

void Push(struct Stack *s, int c){
    s->vect[s->top] = c;
    ++s->top;
}

int Pop(struct Stack *s){
    return s->vect[--s->top];
}

void StackRealloc(struct Stack *s, int k)
{
    s->vect = realloc(s->vect, k*sizeof(int));
}

int main()
{
    struct Stack s;
    char b[5];
    InitStack(&s, 1);
    scanf("%s", b);
    while (strcmp(b, "END") != 0) {
        if (strcmp(b, "CONST") == 0) {
            int x;
            scanf(" %d", &x);
            Push(&s, x);
            StackRealloc(&s, ++s.len);
        } else if (strcmp(b, "ADD") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            StackRealloc(&s, --s.len);
            Push(&s, first+second);
        } else if (strcmp(b, "SUB") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            StackRealloc(&s, --s.len);
            Push(&s, first-second);
        } else if (strcmp(b, "MUL") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            StackRealloc(&s, --s.len);
            Push(&s, first*second);
        } else if (strcmp(b, "DIV") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            StackRealloc(&s, --s.len);
            Push(&s, first/second);
        } else if (strcmp(b, "MAX") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            int max = (first>second) ? first : second;
            StackRealloc(&s, --s.len);
            Push(&s, max);
        } else if (strcmp(b, "MIN") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            int min = (first<second) ? first : second;
            StackRealloc(&s, --s.len);
            Push(&s, min);
        } else if (strcmp(b, "NEG") == 0) {
            int x = -1*Pop(&s);
            Push(&s, x);
        } else if (strcmp(b, "DUP") == 0) {
            int x = Pop(&s);
            ++s.top;
            Push(&s, x);
            StackRealloc(&s, ++s.len);
        } else if (strcmp(b, "SWAP") == 0) {
            int first = Pop(&s);
            int second = Pop(&s);
            Push(&s, first);
            Push(&s, second);
        }
        scanf("%s", b);
    }
    printf("%d", Pop(&s));
    free(s.vect);
    return 0;
}
