#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc<4) {
        printf("Usage: frame <height> <width> <text>\n");
        return 0;
    }
    int heigt = atoi(argv[1]);
    int width = atoi(argv[2]);
    char *s = argv[3];
    int len = strlen(s);
    if (len > width - 2 || heigt < 3) {
        printf("Error\n");
        return 0;
    }
    int pos_str = (heigt-1)/2;
    int pos_col = (width-len)/2;
    int pos_fix = pos_col;
    for (int i=0; i<width; ++i) {
        printf("*");
    }
    printf("\n");
    int k = 0;
    for (int i=1;i<heigt-1; ++i) {
        for (int j=0; j<width; ++j) {
            if (j%(width-1)==0) {
                printf("*");
            } else if (i == pos_str && j == pos_col && pos_col < pos_fix+len) {
                printf("%c", s[k]);
                ++k;
                ++pos_col;
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i=0; i<width; ++i) {
        printf("*");
    }
    printf("\n");
    return 0;
}
