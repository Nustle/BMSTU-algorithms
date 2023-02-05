#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int *a;

void build(int *t, int v, int tl, int tr)
{
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl+tr)>>1;
        build(t, (v<<1)+2, tl, tm);
        build(t, (v<<1)+1, tm+1, tr);
        t[v] = (t[(v<<1)+2]>t[(v<<1)+1]) ? (t[(v<<1)+2]) : t[(v<<1)+1];
    }
}

void update(int *t, int v, int tl, int tr, int pos, int val)
{
    if (tl == tr) t[v] = val;
    else {
        int tm = (tl+tr)>>1;
        if (pos<=tm) {
            update(t, (v<<1)+2, tl, tm, pos, val);
        } else {
            update(t, (v<<1)+1, tm+1, tr, pos, val);
        }
        t[v] = (t[(v<<1)+2]>t[(v<<1)+1]) ? (t[(v<<1)+2]) : t[(v<<1)+1];
    }
}

int max(int *t, int v, int tl, int tr, int l, int r)
{
    if (l > r)
        return INT_MIN;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr)>>1;
    int x = (r<tm) ? r : tm;
    int y = l>(tm+1) ? l : (tm+1);
    int max_1 = max(t, (v<<1)+2, tl, tm, l, x);
    int max_2 = max(t, (v<<1)+1, tm+1, tr, y, r);
    return (max_1 > max_2) ? max_1 : max_2;
}

int compare(const char *s, const char *mustStr)
{
    int res = 0;
    for (int i=0;i<3;++i) {
        if (s[i]!=mustStr[i]) {
            res = -1;
            break;
        }
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    a = (int *) malloc(n*sizeof(int));
    for (int i=0;i<n;++i) {
        scanf("%d", &a[i]);
    }
    int *t = (int *) malloc(4*n*sizeof(int));
    build(t, 0, 0, n-1);
    int *res = (int *) malloc(sizeof(int));
    int c = 0;
    char b[4];
    scanf("%s", b);
    while (compare(b, "END") != 0) {
        int first, second;
        scanf(" %d %d", &first, &second);
        if (compare(b, "MAX") == 0) {
            res[c] = max(t, 0, 0, n-1, first, second);
            ++c;
            res = (int *)realloc(res, (c+1)*sizeof(int));
        } else {
            update(t, 0, 0, n-1, first, second);
        }
        scanf("%s", b);
    }
    for (int i=0;i<c;++i) {
        printf("%d", res[i]);
        if (i<c-1) {
            printf("\n");
        }
    }
    free(a);
    free(t);
    free(res);
    return 0;
}
