#include <stdio.h>
#include <stdlib.h>

int *a;

int gcd(int x, int y)
{
    if (x<y) {
        int t = x;
        x = y;
        y = t;
    }
    while (y!=0) {
        x %= y;
        int t = x;
        x = y;
        y = t;
    }
    return abs(x);
}

void build(int *t, int v, int tl, int tr)
{
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl+tr)>>1;
        build(t, (v<<1)+2, tl, tm);
        build(t, (v<<1)+1, tm+1, tr);
        t[v] = gcd(t[(v<<1)+2], t[(v<<1)+1]);
    }
}

int gcd_tree(int *t, int v, int tl, int tr, int l, int r)
{
    if (l>r) {
        return 0;
    }
    if (l == tl && r == tr) {
        return t[v];
    }

    int tm = (tl + tr)>>1;
    int x = (r<tm) ? r : tm;
    int y = l>(tm+1) ? l : (tm+1);
    int gcd_1 = gcd_tree(t, (v<<1)+2, tl, tm, l, x);
    int gcd_2 = gcd_tree(t, (v<<1)+1, tm+1, tr, y, r);
    return gcd(gcd_1, gcd_2);
}


int main()
{
    int n, m;
    scanf("%d", &n);
    a = (int *) malloc(n*sizeof(int));
    for (int i=0;i<n;++i) {
        scanf("%d", &a[i]);
    }
    int *t = (int *) malloc(4*n*sizeof(int));
    build(t, 0, 0, n-1);
    scanf("%d", &m);
    int *res = (int *) malloc(m*sizeof(int));
    for (int i=0;i<m;++i) {
        int first, second;
        scanf("%d %d", &first, &second);
        res[i] = gcd_tree(t, 0, 0, n-1, first, second);
    }
    for (int i=0;i<m;++i) {
        printf("%d", res[i]);
        if (i<m-1) {
            printf("\n");
        }
    }
    free(a);
    free(t);
    free(res);
    return 0;
}
