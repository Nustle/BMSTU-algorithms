#include <stdio.h>
#include <stdlib.h>

#define ll long long int

typedef struct pair pair;
struct pair {
    ll t1,t2;
};

typedef struct PriorityQueue Queue;
struct PriorityQueue {
    ll *heap;
    ll len, count;
};

void InitPriorityQueue(Queue *q, ll n)
{
    q->heap = (ll *)malloc((n+1)*sizeof(ll));
    q->len = n;
    q->count = 0;
}

void swap(Queue *q, ll i, ll j)
{
    ll t;
    t = q->heap[j];
    q->heap[j] = q->heap[i];
    q->heap[i] = t;
}

void InsertPriorityQueue(Queue *q, ll time)
{
    q->heap[q->count++] = time;
    for (ll i=q->count-1; i>0 && (q->heap[(i-1)/2] > q->heap[i]); i=(i-1)/2) {
        swap(q, (i-1)/2, i);
    }
}

void Heapify(struct PriorityQueue *q, ll i) {
    ll l, r;
    ll n = q->count;
    for (ll j=-1; i!=j; swap(q,i,j)) {
        l = 2*i+1;
        r = 2*i+2;
        j = i;
        if (l < n && (q->heap[l] < q->heap[i])) {
            i = l;
        }
        if (r < n && (q->heap[r] < q->heap[i])) {
            i=r;
        }
    }
}

ll Extract(struct PriorityQueue *q)
{
    ll elem = q->heap[0];
    --q->count;
    if (q->count != 0) {
        q->heap[0] = q->heap[q->count];
        Heapify(q, 0);
    }
    return elem;
}

int main() {
    Queue q;
    ll n, m, res;
    scanf("%lli", &n);
    scanf("%lli", &m);
    pair *Cluster = (pair*) malloc((m+1)*sizeof(pair));
    InitPriorityQueue(&q, n);
    for (ll i=0; i<m; ++i) {
        scanf("%lli %lli", &Cluster[i].t1, &Cluster[i].t2);
        if (i<n) {
            ll time = Cluster[i].t1 + Cluster[i].t2;
            InsertPriorityQueue(&q, time);
        }
    }
    for (ll i = m; i < n; ++i) {
        InsertPriorityQueue(&q, Cluster[i].t1 + Cluster[i].t2);
    }
    for (ll i=n; q.count>0; ++i) {
        res=Extract(&q);
        if (i < m && Cluster[i].t1>res) {
            ll time = Cluster[i].t1 + Cluster[i].t2;
            InsertPriorityQueue(&q, time);
        } else if (i<m) {
            ll time = res + Cluster[i].t2;
            InsertPriorityQueue(&q, time);
        } else {
            ll time=q.heap[0];
            for (ll z=1; q.count!=0; ++z,--q.count) {
                if (q.heap[z]>time) {
                    time=q.heap[z];
                }
            }
            res = time;
        }
    }
    printf("%lli", res);
    free(q.heap);
    free(Cluster);
    return 0;
}
