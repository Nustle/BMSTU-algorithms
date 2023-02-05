#include <stdio.h>

int main()
{
    long long n, k;
    scanf("%lld", &n);
    long long a[n];
    long long s = 0;
    for (long long z=0; z<n; ++z) {
        scanf("%lld", &a[z]);
    }
    scanf("%lld", &k);
    for (long long j=0; j<n; ++j) {
        if (j<k) {
            s += a[j];
        }
    }
    long long ms = s;
    for (long long i = 0; i < n-k; ++i) {
        s -= (a[i]-a[k+i]);
        if (s > ms) {
            ms = s;
        }
    }
    printf("%lld", ms);
    return 0;
}
