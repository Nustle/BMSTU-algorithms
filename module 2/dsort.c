#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dsort(char *s)
{
    int a[26] = {0};
    int n=(int)strlen(s);
    char *res = malloc(n+1);
    for (int i=0;i<n;++i) {
        ++a[s[i]-'a'];
    }
    int c=0;
    for (int i=0;i<26;++i) {
        while (a[i] > 0) {
            char x = (char)(i+97);
            res[c++] = x;
            --a[i];
        }
    }
    res[n] = '\0';
    return res;
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
    char *s;
    s = get_fstr();
    char *r = dsort(s);
    printf("%s\n", r);
    free(s);
    free(r);
    return 0;
}
