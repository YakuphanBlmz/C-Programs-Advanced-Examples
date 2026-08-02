#include <stdio.h>
#include <stdlib.h>
int** createGrid(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    int** grid = (int**)malloc(rows * sizeof(int*));
    if (grid == NULL) return NULL;
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)calloc(cols, sizeof(int));
        if (grid[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return NULL;
        }
    }
    return grid;
}
void freeGrid(int*** gridPtr, int rows) {
    if (gridPtr == NULL || *gridPtr == NULL) return;
    for (int i = 0; i < rows; i++) {
        free((*gridPtr)[i]);
    }
    free(*gridPtr);
    *gridPtr = NULL;
}
void resizeGrid(int*** gridPtr, int* currentRowsPtr, int* currentColsPtr, int newRows, int newCols) {
    if (gridPtr == NULL || currentRowsPtr == NULL || currentColsPtr == NULL) return;
    int oldRows = *currentRowsPtr;
    int oldCols = *currentColsPtr;
    if (newRows <= 0 || newCols <= 0) {
        freeGrid(gridPtr, oldRows);
        *currentRowsPtr = 0;
        *currentColsPtr = 0;
        return;
    }
    int** tempGrid = (int**)realloc(*gridPtr, newRows * sizeof(int*));
    if (tempGrid == NULL) {
        return;
    }
    *gridPtr = tempGrid;
    if (newRows < oldRows) {
        for (int i = newRows; i < oldRows; i++) {
            free((*gridPtr)[i]);
        }
    } else if (newRows > oldRows) {
        for (int i = oldRows; i < newRows; i++) {
            (*gridPtr)[i] = NULL;
        }
    }
    for (int i = 0; i < newRows; i++) {
        int* tempRow = (int*)realloc((*gridPtr)[i], newCols * sizeof(int));
        if (tempRow == NULL) {
            if ((*gridPtr)[i] != NULL) {
                free((*gridPtr)[i]);
            }
            tempRow = (int*)calloc(newCols, sizeof(int));
            if (tempRow == NULL) {
                (*gridPtr)[i] = NULL;
                continue;
            }
        }
        (*gridPtr)[i] = tempRow;
        if (i < oldRows && newCols > oldCols) {
            for (int j = oldCols; j < newCols; j++) {
                (*gridPtr)[i][j] = 0;
            }
        } else if (i >= oldRows && (*gridPtr)[i] != NULL) {
            for (int j = 0; j < newCols; j++) {
                (*gridPtr)[i][j] = 0;
            }
        }
    }
    *currentRowsPtr = newRows;
    *currentColsPtr = newCols;
}
void printGrid(int** grid, int rows, int cols) {
    if (grid == NULL || rows <= 0 || cols <= 0) {
        printf("Grid is empty or invalid.\n");
        return;
    }
    printf("Grid (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main() {
    int** grid = NULL;
    int rows = 0;
    int cols = 0;
    rows = 3;
    cols = 4;
    grid = createGrid(rows, cols);
    if (grid == NULL) {
        printf("Failed to create initial grid.\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j] = i * 10 + j;
        }
    }
    printf("--- Initial Grid ---\n");
    printGrid(grid, rows, cols);
    printf("--- Resizing to 5x6 ---\n");
    resizeGrid(&grid, &rows, &cols, 5, 6);
    printGrid(grid, rows, cols);
    printf("--- Resizing to 2x3 ---\n");
    resizeGrid(&grid, &rows, &cols, 2, 3);
    printGrid(grid, rows, cols);
    printf("--- Resizing to 4x2 ---\n");
    resizeGrid(&grid, &rows, &cols, 4, 2);
    printGrid(grid, rows, cols);
    printf("--- Resizing to 1x1 ---\n");
    resizeGrid(&grid, &rows, &cols, 1, 1);
    printGrid(grid, rows, cols);
    printf("--- Resizing to 0x0 ---\n");
    resizeGrid(&grid, &rows, &cols, 0, 0);
    printGrid(grid, rows, cols);
    freeGrid(&grid, rows);
    return 0;
}