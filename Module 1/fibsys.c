#include <stdio.h>

int main() 
{
    unsigned long long x, fib1, fib2, n;
    scanf("%lld", &x);
    fib1 = 1;
    fib2 = 1;
    n = 1;
    while (fib1+fib2 <= x) {
        fib2 = fib1 + fib2;
        fib1 = fib2-fib1;
        ++n;
    }
    unsigned long long a[n];
    for (unsigned long long i=0; i<n; ++i) {
        a[i] = 0;
    }
    unsigned long long k = 0;
    unsigned long long m = n;
    while (m) {
        if (x>=fib2) {
            x -= fib2;
            a[k] = 1;
        }
        fib1 = fib2-fib1;
        fib2 = fib2-fib1;
        ++k;
        --m;
    }
    for (unsigned long long i=0; i<n; ++i) {
        printf("%lld", a[i]);
    }
    return 0;
}
