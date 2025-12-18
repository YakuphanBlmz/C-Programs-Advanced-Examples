#include <stdio.h>
#include <stdlib.h>
#define D1_INITIAL 3
#define D2_INITIAL 4
#define D3_INITIAL 5
#define D1_NEW (D1_INITIAL + 2)
int main() {
    int ***cube;
    int i, j, k;
    cube = (int ***)malloc(D1_INITIAL * sizeof(int **));
    if (cube == NULL) {
        return EXIT_FAILURE;
    }
    for (i = 0; i < D1_INITIAL; i++) {
        cube[i] = (int **)malloc(D2_INITIAL * sizeof(int *));
        if (cube[i] == NULL) {
            for (int cleanup_i = 0; cleanup_i < i; cleanup_i++) {
                for (int cleanup_j = 0; cleanup_j < D2_INITIAL; cleanup_j++) {
                    free(cube[cleanup_i][cleanup_j]);
                }
                free(cube[cleanup_i]);
            }
            free(cube);
            return EXIT_FAILURE;
        }
        for (j = 0; j < D2_INITIAL; j++) {
            cube[i][j] = (int *)malloc(D3_INITIAL * sizeof(int));
            if (cube[i][j] == NULL) {
                for (int cleanup_j = 0; cleanup_j < j; cleanup_j++) {
                    free(cube[i][cleanup_j]);
                }
                free(cube[i]);
                for (int cleanup_i = 0; cleanup_i < i; cleanup_i++) {
                    for (int cleanup_j = 0; cleanup_j < D2_INITIAL; cleanup_j++) {
                        free(cube[cleanup_i][cleanup_j]);
                    }
                    free(cube[cleanup_i]);
                }
                free(cube);
                return EXIT_FAILURE;
            }
        }
    }
    printf("Initial Cube Elements (%dx%dx%d):\n", D1_INITIAL, D2_INITIAL, D3_INITIAL);
    for (i = 0; i < D1_INITIAL; i++) {
        for (j = 0; j < D2_INITIAL; j++) {
            for (k = 0; k < D3_INITIAL; k++) {
                cube[i][j][k] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
                printf("%4d ", cube[i][j][k]);
            }
            printf("\n");
        }
        printf("--------------------\n");
    }
    int ***temp_cube = (int ***)realloc(cube, D1_NEW * sizeof(int **));
    if (temp_cube == NULL) {
        for (i = 0; i < D1_INITIAL; i++) {
            for (j = 0; j < D2_INITIAL; j++) {
                free(cube[i][j]);
            }
            free(cube[i]);
        }
        free(cube);
        return EXIT_FAILURE;
    }
    cube = temp_cube;
    for (i = D1_INITIAL; i < D1_NEW; i++) {
        cube[i] = (int **)malloc(D2_INITIAL * sizeof(int *));
        if (cube[i] == NULL) {
            for (int cleanup_i_new = D1_INITIAL; cleanup_i_new < i; cleanup_i_new++) {
                for (int cleanup_j = 0; cleanup_j < D2_INITIAL; cleanup_j++) {
                    free(cube[cleanup_i_new][cleanup_j]);
                }
                free(cube[cleanup_i_new]);
            }
            for (int cleanup_i_orig = 0; cleanup_i_orig < D1_INITIAL; cleanup_i_orig++) {
                for (int cleanup_j = 0; cleanup_j < D2_INITIAL; cleanup_j++) {
                    free(cube[cleanup_i_orig][cleanup_j]);
                }
                free(cube[cleanup_i_orig]);
            }
            free(cube);
            return EXIT_FAILURE;
        }
        for (j = 0; j < D2_INITIAL; j++) {
            cube[i][j] = (int *)malloc(D3_INITIAL * sizeof(int));
            if (cube[i][j] == NULL) {
                for (int cleanup_j_current = 0; cleanup_j_current < j; cleanup_j_current++) {
                    free(cube[i][cleanup_j_current]);
                }
                free(cube[i]);
                for (int cleanup_i_new = D1_INITIAL; cleanup_i_new < i; cleanup_i_new++) {
                    for (int cleanup_j = 0; cleanup_j < D2_INITIAL; cleanup_j++) {
                        free(cube[cleanup_i_new][cleanup_j]);
                    }
                    free(cube[cleanup_i_new]);
                }
                for (int cleanup_i_orig = 0; cleanup_i_orig < D1_INITIAL; cleanup_i_orig++) {
                    for (int cleanup_j = 0; cleanup_j < D2_INITIAL; cleanup_j++) {
                        free(cube[cleanup_i_orig][cleanup_j]);
                    }
                    free(cube[cleanup_i_orig]);
                }
                free(cube);
                return EXIT_FAILURE;
            }
            for (k = 0; k < D3_INITIAL; k++) {
                cube[i][j][k] = (i + 1) * 1000 + (j + 1) * 100 + (k + 1); 
            }
        }
    }
    printf("\nResized Cube Elements (%dx%dx%d):\n", D1_NEW, D2_INITIAL, D3_INITIAL);
    for (i = 0; i < D1_NEW; i++) {
        for (j = 0; j < D2_INITIAL; j++) {
            for (k = 0; k < D3_INITIAL; k++) {
                printf("%4d ", cube[i][j][k]);
            }
            printf("\n");
        }
        printf("--------------------\n");
    }
    for (i = 0; i < D1_NEW; i++) {
        for (j = 0; j < D2_INITIAL; j++) {
            free(cube[i][j]);
        }
        free(cube[i]);
    }
    free(cube);
    return EXIT_SUCCESS;
}