#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *concat(char **s, int n)
{
    int k = 0;
    for (int i=0;i<n;++i) {
        k += strlen(s[i]);
    }
    char *dest = malloc(k+1);
    int c = 0;
    for (int j=0; j<n; ++j)
    {
        int l = strlen(s[j]);
        memcpy(c+dest, s[j], l);
        c += l;
    }
    dest[k] = '\0';
    return dest;
}

int main()
{
    int n;
    scanf("%d", &n);
    char **s = malloc (sizeof (char*) * n);
    for (int i = 0; i < n; ++i) {
        s[i] = malloc(1001 * sizeof(char));
        scanf("%s", s[i]);
    }
    char *concat_s = concat(s, n);
    printf("%s", concat_s);
    free(concat_s);
    for(int i = 0; i < n; ++i) {
        free(s[i]);
    }
    free(s);
    return 0;
}
