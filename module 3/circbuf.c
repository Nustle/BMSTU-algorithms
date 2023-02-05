#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STARTLEN 4

struct Queue {
    int *vect;
    int len, head, tail;
};

void InitQueue (struct Queue *q)
{
    q->vect = (int *) malloc(STARTLEN*sizeof(int));
    q->len = STARTLEN;
    q->head = -1;
    q->tail = -1;
}

int QueueEmpty (const struct Queue *q)
{
    int isEmpty = (q->head==-1) ? 1 : 0;
    return isEmpty;
}

int isFull(const struct Queue *q) {
    int full = 0;
    if ((q->head == q->tail + 1) || (q->head == 0 && q->tail == q->len - 1)) {
        full = 1;
    }
    return full;
}

void Enqueue (struct Queue *q, int elem)
{
    if (isFull(q)) {
        int old = q->len;
        q->len *= 2;
        int *temp = (int *)malloc(q->len*sizeof(int));
        for (int i=0;i<old;++i) {
            temp[i] = q->vect[(i+q->head)%old];
        }
        free(q->vect);
        q->vect = temp;
        q->head = -1;
        q->tail = old-1;
    }
    if (q->head == -1) q->head = 0;
    q->tail = (q->tail+1)%(q->len);
    q->vect[q->tail] = elem;
}

int Dequeue (struct Queue *q)
{
    int x = q->vect[q->head];
    if (q->head == q->tail) {
        q->head = -1;
        q->tail = -1;
    } else {
        q->head = (q->head+1)%(q->len);
    }
    return x;
}

int main()
{
    struct Queue q;
    char b[5];
    InitQueue(&q);
    scanf("%s", b);
    while (strcmp(b, "END") != 0) {
        int elem;
        if (strcmp(b, "ENQ") == 0) {
            scanf(" %d", &elem);
            Enqueue(&q, elem);
        } else if (strcmp(b, "DEQ") == 0) {
            elem = Dequeue(&q);
            printf("%d", elem);
        } else if (strcmp(b, "EMPTY") == 0) {
            if (QueueEmpty(&q)) {
                printf("true");
            } else {
                printf("false");
            }
        }
        if (strcmp(b, "DEQ") == 0 || strcmp(b, "EMPTY") == 0) {
            printf("\n");
        }
        scanf("%s", b);
    }
    free(q.vect);
    return 0;
}
