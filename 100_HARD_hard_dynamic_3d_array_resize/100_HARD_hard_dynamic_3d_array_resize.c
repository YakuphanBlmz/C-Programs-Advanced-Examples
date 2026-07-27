#include <stdio.h>
#include <stdlib.h>
int*** allocate_and_init_cube(int d1, int d2, int d3, int initial_value) {
    int ***cube = (int ***)malloc(d1 * sizeof(int **));
    for (int i = 0; i < d1; i++) {
        cube[i] = (int **)malloc(d2 * sizeof(int *));
        for (int j = 0; j < d2; j++) {
            cube[i][j] = (int *)malloc(d3 * sizeof(int));
            for (int k = 0; k < d3; k++) {
                cube[i][j][k] = initial_value;
            }
        }
    }
    return cube;
}
void print_cube(int ***cube, int d1, int d2, int d3) {
    printf("Cube (Dimensions: %dx%dx%d):\n", d1, d2, d3);
    for (int i = 0; i < d1; i++) {
        printf("  Slice %d:\n", i);
        for (int j = 0; j < d2; j++) {
            printf("    Row %d: ", j);
            for (int k = 0; k < d3; k++) {
                printf("%3d ", cube[i][j][k]);
            }
            printf("\n");
        }
    }
    printf("\n");
}
int*** add_depth_slice(int ***cube, int *d1_ptr, int d2, int d3, int new_slice_value) {
    int old_d1 = *d1_ptr;
    int new_d1 = old_d1 + 1;
    int ***new_cube = (int ***)realloc(cube, new_d1 * sizeof(int **));
    if (new_cube == NULL) {
        return cube;
    }
    new_cube[old_d1] = (int **)malloc(d2 * sizeof(int *));
    if (new_cube[old_d1] == NULL) {
        return new_cube;
    }
    for (int j = 0; j < d2; j++) {
        new_cube[old_d1][j] = (int *)malloc(d3 * sizeof(int));
        if (new_cube[old_d1][j] == NULL) {
             return new_cube;
        }
        for (int k = 0; k < d3; k++) {
            new_cube[old_d1][j][k] = new_slice_value;
        }
    }
    *d1_ptr = new_d1;
    return new_cube;
}
void free_cube(int ***cube, int d1, int d2) {
    for (int i = 0; i < d1; i++) {
        for (int j = 0; j < d2; j++) {
            free(cube[i][j]);
        }
        free(cube[i]);
    }
    free(cube);
}
int main() {
    int d1 = 2, d2 = 3, d3 = 4;
    int initial_value = 100;
    int ***cube = allocate_and_init_cube(d1, d2, d3, initial_value);
    print_cube(cube, d1, d2, d3);
    printf("Adding a new depth slice with value 200...\n");
    cube = add_depth_slice(cube, &d1, d2, d3, 200);
    print_cube(cube, d1, d2, d3);
    printf("Adding another new depth slice with value 300...\n");
    cube = add_depth_slice(cube, &d1, d2, d3, 300);
    print_cube(cube, d1, d2, d3);
    free_cube(cube, d1, d2);
    return 0;
}