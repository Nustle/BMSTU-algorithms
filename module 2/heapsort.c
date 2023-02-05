#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int i, int l, void* base, size_t width)
{
    char *a = base;
    for (int k = 0; k < width; ++k) {
        char z = a[width*l+k];
        a[width * l + k] = a[width * i + k];
        a[width * i + k] = z;
    }
}

int countInStr(char *a)
{
    int res = 0;
    for (int i=0;i<strlen(a);++i) {
        if (a[i] == 'a') ++res;
    }
    return res;
}

int compare(const void *a, const void *b)
{
    char **a_type = (char**)a;
    char **b_type = (char**)b;
    return countInStr(*a_type) - countInStr(*b_type);
}

void heapify(void *base, int i, size_t nel, size_t width,
             int (*compare)(const void *a, const void *b))
{
    int l, r, largest;
    l = 2*i+1;
    r = 2*i+2;
    largest = i;
    if (l < nel && compare((char *)base + l * width, (char *)base + i * width) > 0) {
        largest = l;
    }
    if (r < nel && compare((char *)base + r * width, (char *)base + largest * width) > 0) {
        largest = r;
    }
    if (i != largest) {
        swap(i, largest, base, width);
        heapify((char *)base, largest, nel, width, compare);
    }
}

void build_heap(void *base, size_t nel, size_t width,
                int (*compare)(const void *a, const void *b))
{
    for (int i=(int)nel/2-1; i>=0; --i) {
        heapify(base, i, nel, width, compare);
    }
}


void hsort(void *base, size_t nel, size_t width,
           int (*compare)(const void *a, const void *b))
{
    build_heap(base, nel, width, compare);
    for (int i=(int)nel-1; i>=1; --i) {
        swap(0, i, base, width);
        heapify(base, 0, i, width, compare);
    }
}

void make_str_arr(char ***s, int n)
{
    char **a = NULL;
    for(int j = 0; j < n; ++j) {
        int k = 0;
        int cap = 1;
        char *str = (char *)malloc(1);
        char b = (char)getchar();
        while (b == ' ') {
            b = (char)getchar();
        }
        for (int i=0; b != '\n'; ++i) {
            if (k>0) {
                if (str[k-1] == ' ' && b == ' ') {
                    b = (char)getchar();
                    continue;
                }
            }
            str[k++] = b;
            if (k > cap - 1) {
                cap *= 2;
                str = realloc(str, cap);
            }
            b = (char)getchar();
        }
        if (str[k-1] == ' ') {
            str[k-1] = '\0';
        } else {
            str[k] = '\0';
        }
        a = realloc(a, sizeof(char*)*(j+1));
        a[j] = str;
    }
    *s = a;
}

int main()
{
    int n;
    scanf("%d\n", &n);
    char **s;
    make_str_arr(&s, n);
    hsort(s, n, sizeof(char*), compare);
    for(int i = 0; i < n-1; i++)
    {
        printf("%s\n", s[i]);
        free(s[i]);
    }
    printf("%s", s[n-1]);
    free(s[n-1]);
    free(s);
    return 0;
}
