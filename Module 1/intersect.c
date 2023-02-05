#include <stdio.h>

int main() 
{
    int a_n, b_n, el;
    scanf("%d", &a_n);
    int a = 0;
    for (int i=0; i<a_n; ++i) {
        scanf("%d", &el);
        if (( (1 << el) & a) == 0) {
            a += 1 << el;
        }
    }
    int b = 0;
    scanf("%d", &b_n);
    for (int j=0; j<b_n; ++j) {
        scanf("%d", &el);
        if (( (1 << el) & b) == 0) {
            b += 1 << el;
        }
    }
    int res = a&b;
    for (int k=0; k<32; ++k) {
        if (( (1 << k) & res) != 0) {
            printf("%d ", k);
        }
    }
    return 0;
}
