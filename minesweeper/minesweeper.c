// Minesweeper 10189

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void solve(char *input, int *out, int r, int c);

int main(void)
{
    int num_field = 0;
    int r, c;
    char mine = '*';
    char *f;
    int *out;
    int i, j;
    while (scanf("%i %i", &r, &c) == 2) {
        if (r == c && r == 0) {
            break;
        }
        getchar();
        printf("Field #%i:\n", ++num_field);
        out = (int *)malloc(sizeof(int) * r * c);
        f = (char *)malloc(sizeof(char) * r * c);
        if (f == NULL || out == NULL) {
            fprintf(stderr, "Malloc fail\n");
            break;
        }
        for (i = 0; i < r; i++) {
            for (j = 0; j < c; j++) {
                f[i * c + j] = (char)getchar();
            }
            getchar();
        }
        solve(f, out, r, c);
        for (i = 0; i < r; i++) {
            for (j = 0; j < c; j++) {
                if (out[i * c + j] == -1) {
                    printf("%c", mine);
                } else {
                    printf("%i", out[i * c + j]);
                }
            }
            printf("\n");
        }
        printf("\n");
        free(f);
        free(out);
    }
}
void solve(char *input, int *out, int r, int c)
{
    int dir[3][3] = {{-1 - c, -c, 1 - c}, {-1, 1,0}, {c - 1, c, c + 1}};
    int i, j, k, num;
    for (i = 0; i < (r * c); i++) {
        if (input[i] == '*') {
            out[i] = -1;
        } else {
            num = 0;
            for (j = 0; j < 3; j++) {
                if (j == 0) {
                    if (i / c - 1 >= -1) {
                        for (k = 0; k < 3; k++) {
                            if (((i+dir[j][k])/c==i/c-1) && (input[i+dir[j][k]]== '*')){
                                num++;
                            }
                        }
                    }
                } else if (j == 1) {
                    for (k = 0; k < 2; k++) {
                        if (((i+dir[j][k])/c==i/c) && (input[i+dir[j][k]]== '*')){
                            num++;
                        }
                    }
                } else {
                    if (i / c + 1 < r) {
                        for (k = 0; k < 3; k++) {
                            if (((i+dir[j][k])/c==i/c+1) && (input[i+dir[j][k]]== '*')){
                                num++;
                            }
                        }
                    }
                }
            }
        out[i] = num;
        }
    }
}
