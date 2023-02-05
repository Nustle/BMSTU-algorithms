#include <stdio.h>
#include <math.h>

unsigned long long makeDigit(unsigned long long num)
{
    unsigned long long d = 0;
    unsigned long long k = (unsigned long long)(log2((double)num));

    while (num)
    {
        unsigned long long s = (unsigned long long)pow(2, (double)k);
        d += (num%2) * s;
        --k;
        num /= 2;
    }

    return d;
}

int main() {
    unsigned long long a,b,m,l,res;
    scanf("%lld %lld %lld", &a, &b, &m);
    l = makeDigit(b);
    unsigned long long lZeroes = (unsigned long long)(log2((double)b)) - (unsigned long long)(log2((double)l));
    res = (a%m)*(l%2);
    l /= 2;
    for (long long i=1; l>0; ++i) {
        res = (((2*res)%m) + (l%2)*(a%m))%m;
        l /= 2;
    }
    while (lZeroes>0) {
        res = (res*2)%m;
        --lZeroes;
    }
    printf("%lld", res);
    return 0;
}
