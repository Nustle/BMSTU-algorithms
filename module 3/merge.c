#include <stdio.h>
#include <stdlib.h>

typedef struct pair
{
    int key,value;
} pair;

typedef struct PriorityQueue
{
    pair *heap;
    int count, len;
} PriorityQueue;

void InitPriorityQueue(PriorityQueue *q, int nel)
{
    q->heap = (pair *) malloc(sizeof(pair)*nel);
    q->count = 0;
    q->len = nel;
}

void init_pair (pair *p, int x, int k)
{
    p->value = k;
    p->key = x;
}

void swap(PriorityQueue *q, int i, int j)
{
    pair temp = q->heap[j];
    q->heap[j] = q->heap[i];
    q->heap[i] = temp;
}

void Heapify(PriorityQueue *q, int i, int nel)
{
    int l, r;
    for (int j=-1; i!=j; swap(q,i,j)) {
        j = i;
        l = (i<<1)+1;
        r = (i<<1)+2;
        j = i;
        if ((l < nel) && (q->heap[l].key < q->heap[i].key)) {
            i = l;
        }
        if ((r < nel) && (q->heap[r].key < q->heap[i].key)) {
            i = r;
        }
    }
}

pair Extract(PriorityQueue *q)
{
    pair elem = q->heap[0];
    q->heap[0] = q->heap[--q->count];
    Heapify(q, 0, q->count);
    return elem;
}

void Insert(PriorityQueue *q, int x, int k)
{
    pair p;
    init_pair(&p, x, k);
    int c = q->count;
    q->heap[c] = p;
    ++q->count;
    for (int z=0; (c > 0) && (q->heap[(c - 1)>>1].key > q->heap[c].key); z++) {
        int j = (c - 1)>>1;
        swap(q, c, j);
        c = j;
    }
}

void inserts_with_extract(PriorityQueue *q, int **matrix, int *ulist, const int *sizes, int nel) {
    for (int i = 0; i < nel; ++i) {
        if (ulist[i] < sizes[i]) {
            Insert(q, matrix[i][ulist[i]], i);
        }
    }
    for (int z=0; q->count; z++) {
        pair current = Extract(q);
        printf("%d ", current.key);
        ulist[current.value]++;
        if (ulist[current.value] < sizes[current.value]) {
            Insert(q, matrix[current.value][ulist[current.value]], current.value);
        }
            
    }
}

int main()
{
    int nel;
    scanf("%d", &nel);
    PriorityQueue q;
    InitPriorityQueue(&q, nel);
    int sizes[nel];
    int ulist[nel];
    int **matrix = (int **) malloc(sizeof(int *)*nel);
    for (int i = 0; i < nel; ++i) {
        scanf("%d", &sizes[i]);
    }
    for (int i = 0; i < nel; ++i) {
        ulist[i] = 0;
    }
    for (int i = 0; i < nel; ++i) {
        matrix[i] = malloc(sizeof(int) * sizes[i]);
        for (int j = 0; j < sizes[i]; ++j) {
            scanf("%d", &(matrix[i][j]));
        }
    }
    inserts_with_extract(&q, matrix, ulist, sizes, nel);
    for (int i = 0; i < nel; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(q.heap);
}
