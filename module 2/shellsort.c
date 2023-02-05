int fibNear(unsigned long n)
{
    unsigned long first = 0;
    unsigned long second = 1;
    while (second < n) {
        second = first+second;
        first = second-first;
    }
    return (int)first;
}

void shellsort(unsigned long nel,
               int (*compare)(unsigned long i, unsigned long j),
               void (*swap)(unsigned long i, unsigned long j))
{
    int d=fibNear(nel);
    while (d>0) {
        int i;
        for (i=d;i<nel;++i) {
            int j;
            for (j=i-d; (j>=0)&&(compare((unsigned long)j, ((unsigned long)j+(unsigned long)d)) > 0); j-=d) {
                swap((unsigned long)j + (unsigned long)d, (unsigned long)j);
            }
        }
        d = fibNear(d);
    }
}
