#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

double *a;

void maxprod(int n)
{
    double ans = a[0];
    int l = 0, r = 0;
    double sum = 0, min_sum = 0;
    int min_pos = -1;
    for (int i=0;i<n;++i) {
        sum += a[i];
        double curr = sum-min_sum;
        if (curr>ans) {
            ans = curr;
            l = min_pos+1;
            r = i;
        }
        if (sum<min_sum) {
            min_sum = sum;
            min_pos = i;
        }
    }
    printf("%d %d", l, r);
}

int main()
{
    int n,first,second;
    scanf("%lld", &n);
    a = (double *)malloc(n*sizeof(double));
    for(int i = 0; i < n; ++i) {
        scanf("%d/%d", &first, &second);
        if (first == 0) {
            a[i] = INT_MIN;
        } else {
            a[i] = log(first) - log(second);
        }
    }
    maxprod(n);
    free(a);
    return 0;
}
