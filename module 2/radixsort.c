#include <stdio.h>

union Int32 {
    int x;
    unsigned char bytes[4];
};

void countsort(union Int32 *digits, int n, int radix)
{
    int keys[256] = {0};
    for (int i=0;i<n;++i) {
        if (radix >= 3) {
            ++keys[(digits[i].bytes[radix]+128)%256];
        } else {
            ++keys[digits[i].bytes[radix]];
        }
    }
    for (int i=1; i<256; ++i) {
        keys[i] += keys[i-1];
    }
    for (int j=0; j<256; ++j) {
        --keys[j];
    }
    union Int32 helpDigits[n];
    for (int i=n-1;i>=0;--i) {
        int index;
        if (radix >= 3) {
            index = (digits[i].bytes[radix]+128)%256;
        } else {
            index = digits[i].bytes[radix];
        }
        helpDigits[keys[index]] = digits[i];
        --keys[index];
    }
    for(int j=0; j<n; ++j) {
        digits[j] = helpDigits[j];
    }
}

void radixsort(union Int32 *digits, int n)
{
    for (int i=0;i<4;++i) {
        countsort(digits, n, i);
    }
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    union Int32 digits[n];
    for (int k=0; k<n; ++k) {
        scanf("%i", &digits[k].x);
    }
    radixsort(digits, n);
    for (int i = 0; i<n; ++i)
        printf("%d ", digits[i].x);
    return 0;
}
