#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_power2(int n)
{
    int r;
    for (r=1; r<n; r <<= 1);
    return r;
}

int build(int *t, char *a, int n, int l, int r)
{
    int bound, m;
    int unit = 0;
    if (n>r) {
        bound = r;
    } else {
        bound = n;
    }
    for (int i=l; i<bound; i=m+1) {
        m = (i + r) >> 1;
        unit ^= build(t, a, n, i, m);
    }
    if (n>r) {
        unit ^= (1<<(a[r]-'a'));
        t[r] = unit;
    }
    return unit;
}

int query(int *t, int i)
{
    int v = 0;
    for (int j=i; j>=0; j=(j & (j + 1))-1) v ^= t[j];
    return v;
}

void update_Fenwick(int *t, int n, int ind, int value)
{
    for (int j=ind; j<n; j|=(j+1)) {
        t[j] ^= value;
    }
}

void build_Fenwick(int *t, char *a, int n)
{
    int r = min_power2(n);
    build(t, a, n, 0, r - 1);
}

int query_Fenwick(int *t, int l, int r)
{
    return query(t, r) ^ query(t, l - 1);
}

char *get_fstr()
{
    int len = 0;
    int cap = 1;
    char *s = (char*) malloc(sizeof(char)+1);
    char c = (char)getchar();
    while (c == ' ') {
        c = (char)getchar();
    }
    while (c != '\n') {
        if (len>0) {
            if (s[len-1] == ' ' && c == ' ') {
                c = (char)getchar();
                continue;
            }
        }
        s[len++] = c;
        if (len > cap - 1) {
            cap *= 2;
            s = (char *)realloc(s, cap * sizeof(char));
        }

        c = (char)getchar();
    }
    if (s[len-1] == ' ') {
        s[len-1] = '\0';
    } else {
        s[len] = '\0';
    }
    return s;
}

int main()
{
    int m;
    char *s = get_fstr();
    int n = (int)strlen(s);
    int *t = (int *) malloc(n*sizeof(int));
    char *res = malloc(sizeof(char));
    build_Fenwick(t, s, n);
    scanf("%d", &m);
    char b[3];
    scanf("%s", b);
    int c=0;
    while (strcmp(b, "END") != 0) {
        int first;
        if (strcmp(b, "HD") == 0) {
            int second;
            scanf(" %d %d", &first, &second);
            int q = query_Fenwick(t, first, second);
            char help = !(q & (q - 1)) ? 'Y' : 'N';
            res[c++] = help;
            res = realloc(res, (c+1)* sizeof(char));
        } else {
            scanf("%d ", &first);
            char d = (char)getchar();
            int x = 0;
            while (d != ' ' && d != '\n') {
                update_Fenwick(t, n, first+x, (1<<(d-'a'))^(1<<(s[first+x]-'a')));
                s[first+x] = d;
                d = (char)getchar();
                ++x;
            }
        }
        scanf("%s", b);
    }
    for (int i=0;i<c;++i) {
        if (res[i] == 'Y') {
            printf("YES");
        } else {
            printf("NO");
        }
        if (i<c-1) {
            printf("\n");
        }
    }
    free(s);
    free(t);
    free(res);
    return 0;
}
