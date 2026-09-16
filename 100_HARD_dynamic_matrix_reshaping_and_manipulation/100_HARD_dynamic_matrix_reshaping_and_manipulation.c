#include <stdio.h>
#include <stdlib.h>
int** create_matrix(int r, int c) {
    int** mat = (int**)malloc(r * sizeof(int*));
    if (mat == NULL) return NULL;
    for (int i = 0; i < r; i++) {
        mat[i] = (int*)malloc(c * sizeof(int));
        if (mat[i] == NULL) {
            for (int j = 0; j < i; j++) free(mat[j]);
            free(mat);
            return NULL;
        }
        for (int j = 0; j < c; j++) {
            mat[i][j] = i * c + j + 1;
        }
    }
    return mat;
}
void print_matrix(int** matrix, int r, int c) {
    if (matrix == NULL || r == 0 || c == 0) {
        printf("Matrix is NULL or empty.\n");
        return;
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int** insert_row(int** matrix, int *r, int c, int index, int value) {
    if (index < 0 || index > *r) return NULL;
    int new_r = *r + 1;
    int** new_matrix = (int**)realloc(matrix, new_r * sizeof(int*));
    if (new_matrix == NULL) return NULL;
    for (int i = new_r - 1; i > index; i--) {
        new_matrix[i] = new_matrix[i - 1];
    }
    new_matrix[index] = (int*)malloc(c * sizeof(int));
    if (new_matrix[index] == NULL) {
        return NULL;
    }
    for (int j = 0; j < c; j++) {
        new_matrix[index][j] = value;
    }
    *r = new_r;
    return new_matrix;
}
int** delete_row(int** matrix, int *r, int c, int index) {
    if (matrix == NULL || index < 0 || index >= *r || *r == 0) return NULL;
    free(matrix[index]);
    for (int i = index; i < *r - 1; i++) {
        matrix[i] = matrix[i + 1];
    }
    int new_r = *r - 1;
    if (new_r == 0) {
        free(matrix);
        *r = 0;
        return NULL;
    }
    int** new_matrix = (int**)realloc(matrix, new_r * sizeof(int*));
    if (new_matrix == NULL) {
        return NULL;
    }
    *r = new_r;
    return new_matrix;
}
int** insert_column(int** matrix, int r, int *c, int index, int value) {
    if (matrix == NULL || index < 0 || index > *c) return NULL;
    int new_c = *c + 1;
    for (int i = 0; i < r; i++) {
        int* new_row = (int*)realloc(matrix[i], new_c * sizeof(int));
        if (new_row == NULL) {
            return NULL;
        }
        for (int j = new_c - 1; j > index; j--) {
            new_row[j] = new_row[j - 1];
        }
        new_row[index] = value;
        matrix[i] = new_row;
    }
    *c = new_c;
    return matrix;
}
int** delete_column(int** matrix, int r, int *c, int index) {
    if (matrix == NULL || index < 0 || index >= *c || *c == 0) return NULL;
    int new_c = *c - 1;
    if (new_c == 0) {
        for (int i = 0; i < r; i++) free(matrix[i]);
        free(matrix);
        *c = 0;
        return NULL;
    }
    for (int i = 0; i < r; i++) {
        for (int j = index; j < *c - 1; j++) {
            matrix[i][j] = matrix[i][j + 1];
        }
        int* new_row = (int*)realloc(matrix[i], new_c * sizeof(int));
        if (new_row == NULL) {
            return NULL;
        }
        matrix[i] = new_row;
    }
    *c = new_c;
    return matrix;
}
void free_matrix(int** matrix, int r) {
    if (matrix == NULL) return;
    for (int i = 0; i < r; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
int main() {
    int rows = 3;
    int cols = 4;
    int **matrix = create_matrix(rows, cols);
    if (matrix == NULL) {
        printf("Matrix creation failed.\n");
        return 1;
    }
    printf("Initial Matrix (%dx%d):\n", rows, cols);
    print_matrix(matrix, rows, cols);
    matrix = insert_row(matrix, &rows, cols, 1, 99);
    if (matrix == NULL) {
        printf("Row insertion failed.\n");
        free_matrix(matrix, rows);
        return 1;
    }
    printf("After inserting row at index 1 (value 99) (%dx%d):\n", rows, cols);
    print_matrix(matrix, rows, cols);
    matrix = insert_column(matrix, rows, &cols, 2, 88);
    if (matrix == NULL) {
        printf("Column insertion failed.\n");
        free_matrix(matrix, rows);
        return 1;
    }
    printf("After inserting column at index 2 (value 88) (%dx%d):\n", rows, cols);
    print_matrix(matrix, rows, cols);
    matrix = delete_row(matrix, &rows, cols, 0);
    if (matrix == NULL && rows > 0) {
        printf("Row deletion failed or matrix became empty (rows > 0 indicates error).\n");
        free_matrix(matrix, rows);
        return 1;
    } else if (matrix == NULL && rows == 0) {
        printf("After deleting row at index 0, matrix is empty.\n");
    }
    if (matrix != NULL) {
        printf("After deleting row at index 0 (%dx%d):\n", rows, cols);
        print_matrix(matrix, rows, cols);
    }
    matrix = delete_column(matrix, rows, &cols, 1);
    if (matrix == NULL && cols > 0) {
        printf("Column deletion failed or matrix became empty (cols > 0 indicates error).\n");
        free_matrix(matrix, rows);
        return 1;
    } else if (matrix == NULL && cols == 0) {
        printf("After deleting column at index 1, matrix is empty.\n");
    }
    if (matrix != NULL) {
        printf("After deleting column at index 1 (%dx%d):\n", rows, cols);
        print_matrix(matrix, rows, cols);
    }
    free_matrix(matrix, rows);
    printf("All memory freed.\n");
    return 0;
}