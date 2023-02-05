#include <stdio.h>

int main()
{
    long long n, x;
    scanf("%lld %lld", &n, &x);
    long long a[n+1];
    for (long long i=0; i<n+1; ++i) {
        scanf("%lld", &a[i]);
    }
    long long res = a[0];
    long long proizv = n*a[0];
    for (long long j=1; j < n; ++j) {
        proizv = proizv*x + (n-j)*a[j];
        res = res*x + a[j];
    }
    res = (n>0) ? res*x + a[n] : res;
    printf("%lld\n", res);
    printf("%lld", proizv);
    return 0;
}