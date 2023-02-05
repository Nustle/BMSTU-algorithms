#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_count_and_words(char *s, char ***a)
{
    char **words = NULL;
    char *word = NULL;
    char c = 1;
    int wcount = 0;
    int chcount = 0;
    while (c != '\0') {
        c = *(s);
        ++s;
        if (c != '\0' && c != ' ') {
            if (chcount == 0) {
                word = malloc(2);
            } else {
                word = realloc(word, chcount + 1);
            }
            *(chcount+word) = c;
            ++chcount;
        } else if (chcount) {
            word = realloc(word, chcount+1);
            word[chcount] = '\0';
            chcount = 0;
            words = realloc(words, sizeof(char *) * (wcount+1));
            *(wcount+words) = word;
            ++wcount;
        }
    }
    *a = words;
    return wcount;
}

void csort(char *src, char *dest)
{
    char **a;
    int len = get_count_and_words(src, &a);
    unsigned long m=0;
    for (int i=0;i<len;++i) {
        unsigned long z = strlen(a[i]);
        if (z>m) m = z;
    }
    int *c = malloc((m+1)*sizeof(int));
    for (int i=0;i<=m;++i) {
        c[i] = 0;
    }
    for (int j=0;j<len;++j) {
        ++c[strlen(a[j])];
    }
    for (int i=1;i<=m;++i) {
        c[i] += c[i-1];
    }
    for (int j=1;j<=m;++j) {
        --c[j];
    }

    char **b = malloc(sizeof(char *)*len);
    for (int j=len-1; j>=0; --j) {
        int ind = c[strlen(a[j])];
        b[ind] = malloc(strlen(a[j])+1);
        memcpy(b[ind], a[j], strlen(a[j])+1);
        --c[strlen(a[j])];
    }
    unsigned long idx = 0;
    for (int i=0; i<len-1; ++i) {
        unsigned temp = strlen(b[i]);
        memcpy(dest+idx, b[i], temp);
        idx += temp+1;
        dest[idx-1] = ' ';
    }
    if (len > 0) {
        unsigned long temp = strlen(b[len-1]);
        memcpy(dest+idx, b[len-1], temp);
        idx += temp;
    }
    dest[idx] = '\0';
    for (int i=0;i<len;++i) {
        free(a[i]);
        free(b[i]);
    }
    free(a);
    free(b);
    free(c);
}

char *get_fstr()
{
    int len = 0;
    int cap = 1;
    char *s = (char*) malloc(sizeof(char)+1);
    char c = (char)getchar();
    while (c == ' ') {
        c = (char)getchar();
    }
    while (c != '\n') {
        if (len>0) {
            if (s[len-1] == ' ' && c == ' ') {
                c = (char)getchar();
                continue;
            }
        }
        s[len++] = c;
        if (len > cap - 1) {
            cap *= 2;
            s = (char *)realloc(s, cap * sizeof(char));
        }

        c = (char)getchar();
    }
    if (s[len-1] == ' ') {
        s[len-1] = '\0';
    } else {
        s[len] = '\0';
    }
    return s;
}

int main() 
{
    char *src = get_fstr();
    char *dest = malloc((strlen(src) + 1) * sizeof(char));
    csort(src, dest);
    printf("%s", dest);
    free(src);
    free(dest);
    return 0;
}
