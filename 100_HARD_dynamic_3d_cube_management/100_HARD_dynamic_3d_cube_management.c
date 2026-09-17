#include <stdio.h>
#include <stdlib.h>
int main() {
    int DEPTH = 3;
    int ROWS = 4;
    int COLUMNS = 5;
    int ***cube;
    int d, r, c;
    cube = (int ***)malloc(DEPTH * sizeof(int **));
    if (cube == NULL) {
        return 1;
    }
    for (d = 0; d < DEPTH; d++) {
        cube[d] = (int **)malloc(ROWS * sizeof(int *));
        if (cube[d] == NULL) {
            for (int i = 0; i < d; i++) {
                free(cube[i]);
            }
            free(cube);
            return 1;
        }
        for (r = 0; r < ROWS; r++) {
            cube[d][r] = (int *)malloc(COLUMNS * sizeof(int));
            if (cube[d][r] == NULL) {
                for (int i = 0; i < r; i++) {
                    free(cube[d][i]);
                }
                for (int i = 0; i < d; i++) {
                    for (int j = 0; j < ROWS; j++) {
                        free(cube[i][j]);
                    }
                    free(cube[i]);
                }
                free(cube[d]);
                free(cube);
                return 1;
            }
        }
    }
    for (d = 0; d < DEPTH; d++) {
        for (r = 0; r < ROWS; r++) {
            for (c = 0; c < COLUMNS; c++) {
                cube[d][r][c] = (d + 1) * 1000 + (r + 1) * 100 + (c + 1);
            }
        }
    }
    for (d = 0; d < DEPTH; d++) {
        long long sum_slice = 0;
        for (r = 0; r < ROWS; r++) {
            for (c = 0; c < COLUMNS; c++) {
                sum_slice += cube[d][r][c];
            }
        }
        printf("Sum for Depth %d: %lld\n", d, sum_slice);
    }
    for (d = 0; d < DEPTH; d++) {
        for (r = 0; r < ROWS; r++) {
            free(cube[d][r]);
        }
        free(cube[d]);
    }
    free(cube);
    return 0;
}