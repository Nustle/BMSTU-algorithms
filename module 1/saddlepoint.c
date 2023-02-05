#include <stdio.h>

int main()
{
    int haveSaddle = 0;
    int m,n;
    scanf("%d %d", &m, &n);
    int a[m][n];
    int max[m];
    int min[n];
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            scanf("%d", &a[i][j]);
            min[j] = 0;
        }
        max[i] = 0;
    }
    for (int i=0; i<m; ++i) {
        for (int j=0; j<n; ++j) {
            if (a[i][j]>a[i][max[i]]) {
                max[i] = j;
            }
            if (a[i][j]<a[min[j]][j]) {
                min[j] = i;
            }
        }
    }
    for (int i=0; i<n; ++i) {
        if (max[min[i]] == i) {
            haveSaddle = 1;
            printf("%d %d", min[i], i);
            break;
        }
    }
    if (!haveSaddle) {
        printf("%s", "none");
    }
    return 0;
}
