#include <stdio.h>

int isPower2(int x)
{
    int res = 1;
    if (x<=0) res = 0;
    while (x>1) {
        if (x%2!=0) {
            res = 0;
            break;
        }
        x /= 2;
    }
    return res;
}

void makeArray(int *base, int n)
{
    int k = 0;
    for (int i=0; i<=n-2; ++i) {
        if (i > 0) {
            base[i] = base[k];
        } else {
            base[i] = base[++k];
        }
        base[i] = base[k];
        ++k;
    }
    base[n - 1] = 0;
}


int combinations(int *base, int m, int n, int sum)
{
    int res = 0;
    int b[n];
    for (int j = 0; j<=n-1; ++j) {
        b[j] = base[j];
    }
    if (m == 0) {
        res = isPower2(sum);
    } else if (n == m) {
        for (int j = 0; j<=n-1; ++j)
            sum += b[j];
        res = isPower2(sum);
    } else {
        while (n>0 && n>=m) {
            int h = b[0];
            makeArray(b, n);
            res += combinations(b, m - 1, n - 1, sum + h);
            --n;
        }
    }
    return res;
}

int allCombinations(int* base, int n)
{
    int res = 0;
    for (int m = 1; m<=n; ++m)
        res += combinations(base, m, n, 0);
    return res;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    printf("%d", allCombinations(a, n));
    return 0;
}
