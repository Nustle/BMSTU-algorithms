#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a[8], b[8], c[8];
    bool isEqual = true;
    for (int z=0; z<8; ++z) {
        scanf("%d", &a[z]);
        c[z] = 0;
    }
    for (int w=0; w<8; ++w) {
        scanf("%d", &b[w]);
    }
    for (int i=0; i<8; ++i) {
        int eq = 0;
        for (int j=0; j<8; ++j) {
            if (a[i] == b[j] && c[j]==0) {
                ++eq;
                c[j] = 1;
                break;
            }
        }
        if (eq == 0) {
            isEqual = false;
            break;
        }
    }
    if (isEqual) {
        printf("yes");
    } else {
        printf("no");
    }
    return 0;
}
