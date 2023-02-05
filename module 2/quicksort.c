#include <stdio.h>
#include <stdlib.h>

int *b;

void swap(int i, int j)
{
    int m = b[i];
    b[i] = b[j];
    b[j] = m;
}

int compare(int i, int j)
{
    if (b[i] == b[j]) return 0;
    return (b[i] > b[j]) ? 1 : -1;
}


void selectsort(int low, int high, void (*swap)(int i, int j),
                int (*compare)(int i, int j))
{
    int min;
    for(int i=low; i<=high-1; ++i)
    {
        min = i;
        for(int j=i+1; j<=high; ++j) {
            if (compare(j, min)<0) {
                min = j;
            }
        }
        swap(i, min);
    }
}

int partition(int low, int high, void (*swap)(int i, int j), int (*compare)(int i, int j))
{
    int i=low;
    for (int j=low;j<high;++j) {
        if (compare(high, j)>0) {
            swap(i,j);
            ++i;
        }
    }
    swap(i, high);
    return i;
}

void quicksortRec(int low, int high, int m, void (*swap)(int i, int j),
                  int (*compare)(int i, int j))
{
    int q;
    while (high-low+2>m) {
        q = partition(low, high, swap, compare);
        if (q>=(high+low)/2) {
            quicksortRec(low, q-1, m, swap, compare);
            low = q+1;
        } else {
            quicksortRec(q+1, high, m, swap, compare);
            high = q - 1;
        }
    }
    selectsort(low, high, swap, compare);
}

void quicksort(int n, int m, void (*swap)(int i, int j),
               int (*compare)(int i, int j))
{
    quicksortRec(0, n-1, m, swap, compare);
}

int main()
{
    int i, nel, m;
    scanf("%d", &nel);
    scanf("%d", &m);
    b = (int*) malloc(nel*sizeof(int));
    for (i=0;i<nel;++i) {
        scanf("%d", &b[i]);
    }
    quicksort(nel, m, swap, compare);
    for (i=0;i<nel;++i) {
        printf("%d ", b[i]);
    }
    free(b);
    return 0;
}
