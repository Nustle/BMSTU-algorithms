void bubblesort(unsigned long nel,
                int (*compare)(unsigned long i, unsigned long j),
                void (*swap)(unsigned long i, unsigned long j)) {
    unsigned long t = nel-1;
    unsigned long k = 0;
    if (nel>0) {
        while (t!=k) {
            unsigned long trait = t;
            unsigned long traitLeft = k;
            t = k;
            for (int i=0;i<trait;++i) {
                if (compare(i, i+1) > 0) {
                    swap(i, i+1);
                    t = i;
                }
            }
            for (unsigned long i=t; i>traitLeft; --i) {
                if (compare(i, i-1) < 0) {
                    swap(i, i-1);
                    k = i;
                }
            }
        }
    }
}
