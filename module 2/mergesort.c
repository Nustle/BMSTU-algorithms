#include <stdio.h>
#include <stdlib.h>

int *d;

int compare(int i, int j)
{
    int a, b;
    a = d[i];
    b = d[j];
    if (d[i] < 0) a *= -1;
    if (d[j] < 0) b *= -1;
    if (a == b) return 0;
    return (a > b) ? 1 : -1;
}

void merge(int left, int mid, int right, int (*compare)(int i, int j))
{
    int *res = (int*)malloc((right-left+1)*sizeof(int));
    int i = left;
    int j = mid+1;
    int h, k,len;
    for (h=0; i<(mid+1) && j<(right+1); ++h) {
        if (compare(i, j)>0) {
            res[h] = d[j];
            ++j;
        } else {
            res[h] = d[i];
            ++i;
        }
    }
    if (i==mid+1) {
        k = j;
        len = right+1-j;
    } else {
        k = i;
        len = mid+1-i;
    }
    for (int z=0;z<len;++z) {
        res[h] = d[k];
        ++k;
        ++h;
    }
    for (int t=left;t<right+1; ++t) {
        d[t] = res[t-left];
    }
    free(res);
}

void insertSort(int left, int right, int (*compare)(int i, int j))
{
    int i, j;
    for (i=left;i<right+1;++i) {
        int elem = i;
        for (j=i-1; (j>=left)&&(compare(j, elem) > 0); --j) {
            int m = d[j+1];
            d[j+1] = d[j];
            d[j] = m;
            elem=j;
        }
    }
}

void mergeSortRec(int left, int right, int (*compare)(int i, int j))
{
    if (right-left>3) {
        int mid = (left+right)/2;
        mergeSortRec(left, mid, compare);
        mergeSortRec(mid+1, right, compare);
        merge(left, mid, right, compare);
    } else {
        insertSort(left, right, compare);
    }
}

void mergeSort(int n, int (*compare)(int i, int j))
{
    mergeSortRec(0, n-1, compare);
}


int main()
{
    int i, nel;
    scanf("%d", &nel);
    d = (int*) malloc(nel*sizeof(int));
    for (i=0;i<nel;++i) {
        scanf("%d", &d[i]);
    }
    mergeSort(nel, compare);
    for (i=0;i<nel;++i) {
        printf("%d ", d[i]);
    }
    free(d);
    return 0;
}
