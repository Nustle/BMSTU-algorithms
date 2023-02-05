#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long n, m, sqr;
    scanf("%lld", &n);
    if (n < 0) {
        n *= -1;
    }
    sqr = 1;
    while (sqr*sqr<n)
        ++sqr;
    ++sqr;
    long long (*a) = (long long(*))malloc((sqr) * sizeof(*a));
    for (long long z=0;z<sqr;++z) {
        a[z] = z;
    }
    for (long long i=2; i*i<sqr; ++i) {
        if (a[i] != 0) {
            for (long long j = i * i; j < sqr; j += i) {
                a[j] = 0;
            }
        }
    }
    m = 1;
    for (long long f = 2; f < sqr; ++f) {
        if (a[f] != 0) {
            while (n%f==0) {
                m = f;
                n /= f;
            }
        }
    }
    if (n>m) {
        m = n;
    }
    printf("%lld", m);
    free(a);
    return 0;
}
