#include <stdio.h>
#include <stdlib.h>

#define STACKLEN 1024

struct Task {
    int low, high;
};

struct Stack {
    struct Task *vect;
    int top;
};

void InitStack(struct Stack *s)
{
    s->vect = (struct Task*)malloc(STACKLEN*sizeof(struct Task));
    s->top = 0;
}

int StackEmpty(const struct Stack *s){
    int isEmpty = (s->top == 0) ? 1 : 0;
    return isEmpty;
}

void Push(struct Stack *s, struct Task t){
    s->vect[s->top] = t;
    ++s->top;
}

struct Task Pop(struct Stack *s){
    return s->vect[--s->top];
}

void swap(int *a, int i, int j)
{
    int m = a[i];
    a[i] = a[j];
    a[j] = m;
}

int compare(const int *a, int i, int j)
{
    if (a[i] == a[j]) return 0;
    return (a[i] > a[j]) ? 1 : -1;
}

int partition(int *a, int low, int high, void (*swap)(int *a, int i, int j),
              int (*compare)(const int *a, int i, int j)){
    int i=low;
    for (int j=low;j<high;++j) {
        if (compare(a, high, j)>0) {
            swap(a, i,j);
            ++i;
        }
    }
    swap(a, i, high);
    return i;
}

void quicksort(int *a, int n, void (*swap)(int *a, int i, int j),
               int (*compare)(const int *a, int i, int j))
{
    struct Stack s;
    struct Task t;
    t.low = 0;
    t.high = n-1;
    InitStack(&s);
    Push(&s, t);
    while(StackEmpty(&s)==0) {
        t = Pop(&s);
        if (t.low <= t.high) {
            int elem = partition(a, t.low, t.high, swap, compare);
            struct Task first;
            struct Task second;
            first.low = t.low;
            first.high = elem - 1;
            second.low = elem + 1;
            second.high = t.high;
            if (((t.high + 1) >> 1) < elem) {
                Push(&s, first);
                Push(&s, second);
            } else {
                Push(&s, second);
                Push(&s, first);
            }
        }
    }
    free(s.vect);
}

int main()
{
    int n;
    scanf("%d", &n);
    int *a = (int *) malloc(n*sizeof(int));
    for (int i=0;i<n;++i) {
        scanf("%d", &a[i]);
    }
    quicksort(a,n, swap, compare);
    for (int i=0;i<n;++i) {
        printf("%d ", a[i]);
    }
    free(a);
    return 0;
}
