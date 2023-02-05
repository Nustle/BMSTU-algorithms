#include <stdio.h>
#include <stdlib.h>

struct Date {
    int Day, Month, Year;
};

int keys[3] = {31, 12, 61};

int get_ind(struct Date date, int type)
{
    int res;
    if (type == 0) {
        res = date.Day-1;
    } else if (type == 1) {
        res = date.Month-1;
    } else {
        res = date.Year-1970;
    }
    return res;
}

void datesort(struct Date *dates, int n, int type)
{
    int key = keys[type];
    int *a = (int *) malloc((key+1)*sizeof(int));
    for (int i=0; i<key; ++i) {
        a[i] = 0;
    }
    for (int j=0; j<n; ++j) {
        int ind = get_ind(dates[j], type);
        ++a[ind];
    }
    for (int i=1; i<key; ++i) {
        a[i] += a[i-1];
    }
    for (int j=0; j<key; ++j) {
        --a[j];
    }
    struct Date helpDate[n];
    for (int i=n-1; i>=0; --i) {
        int ind = get_ind(dates[i], type);
        helpDate[a[ind]] = dates[i];
        --a[ind];
    }
    for(int j=0; j<n; ++j) {
        dates[j] = helpDate[j];
    }
    free(a);
}

int main()
{
    int n;
    scanf("%d", &n);
    struct Date dates[n];
    for (int i=0;i<n;++i) {
        scanf("%d %d %d", &dates[i].Year, &dates[i].Month, &dates[i].Day);
    }
    for (int i=0;i<3;++i) {
        datesort(dates, n, i);
    }

    for (int i=0;i<n-1;++i) {
        printf("%04d %02d %02d", dates[i].Year, dates[i].Month, dates[i].Day);
        printf("\n");
    }
    printf("%04d %02d %02d", dates[n-1].Year, dates[n-1].Month, dates[n-1].Day);
    return 0;
}
