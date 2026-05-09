#include <stdio.h>
#include <stdlib.h>
void insertRow(int*** matrixPtr, int* currentRowsPtr, int** rowLengthsPtr, int newRowIndex, int newRowLength, int fillValue) {
    if (newRowIndex < 0 || newRowIndex > *currentRowsPtr) {
        fprintf(stderr, "Hata: Geçersiz satır indeksi %d. (Mevcut satır sayısı: %d)\n", newRowIndex, *currentRowsPtr);
        return;
    }
    int** matrix = *matrixPtr;
    int* currentRows = currentRowsPtr;
    int* rowLengths = *rowLengthsPtr;
    int** newMatrix = (int**)realloc(matrix, (*currentRows + 1) * sizeof(int*));
    if (newMatrix == NULL) {
        fprintf(stderr, "Hata: matrix için bellek yeniden tahsisi başarısız.\n");
        return;
    }
    *matrixPtr = newMatrix;
    matrix = newMatrix;
    int* newRowLengths = (int*)realloc(rowLengths, (*currentRows + 1) * sizeof(int));
    if (newRowLengths == NULL) {
        fprintf(stderr, "Hata: rowLengths için bellek yeniden tahsisi başarısız.\n");
        return;
    }
    *rowLengthsPtr = newRowLengths;
    rowLengths = newRowLengths;
    for (int i = *currentRows; i > newRowIndex; i--) {
        matrix[i] = matrix[i-1];
        rowLengths[i] = rowLengths[i-1];
    }
    int* newRow = (int*)malloc(newRowLength * sizeof(int));
    if (newRow == NULL) {
        fprintf(stderr, "Hata: Yeni satır için bellek tahsisi başarısız.\n");
        return;
    }
    for (int j = 0; j < newRowLength; j++) {
        newRow[j] = fillValue;
    }
    matrix[newRowIndex] = newRow;
    rowLengths[newRowIndex] = newRowLength;
    (*currentRows)++;
}
void printMatrixRobust(int** matrix, int* rowLengths, int rows) {
    if (matrix == NULL || rows == 0) {
        printf("Matris boş.\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        printf("[%d]: ", i);
        if (matrix[i] == NULL || rowLengths == NULL || i >= rows) {
            printf("NULL veya geçersiz satır uzunluğu bilgisi.\n");
            continue;
        }
        for (int j = 0; j < rowLengths[i]; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf(" (Uzunluk: %d)\n", rowLengths[i]);
    }
}
void freeMatrix(int*** matrixPtr, int** rowLengthsPtr, int* rowsPtr) {
    int** matrix = *matrixPtr;
    int* rowLengths = *rowLengthsPtr;
    int rows = *rowsPtr;
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
                matrix[i] = NULL;
            }
        }
        free(matrix);
        *matrixPtr = NULL;
    }
    if (rowLengths != NULL) {
        free(rowLengths);
        *rowLengthsPtr = NULL;
    }
    *rowsPtr = 0;
}
int main() {
    int** matrix = NULL;
    int rows = 0;
    int* rowLengths = NULL;
    printf("Başlangıçta boş matris.\n");
    printMatrixRobust(matrix, rowLengths, rows);
    printf("\nİlk satırı ekle (Index 0, Uzunluk 3, Değer 10):\n");
    insertRow(&matrix, &rows, &rowLengths, 0, 3, 10);
    printMatrixRobust(matrix, rowLengths, rows);
    printf("\nİkinci satırı ekle (Index 1, Uzunluk 4, Değer 20):\n");
    insertRow(&matrix, &rows, &rowLengths, 1, 4, 20);
    printMatrixRobust(matrix, rowLengths, rows);
    printf("\nBaşlangıca yeni satır ekle (Index 0, Uzunluk 2, Değer 5):\n");
    insertRow(&matrix, &rows, &rowLengths, 0, 2, 5);
    printMatrixRobust(matrix, rowLengths, rows);
    printf("\nOrtaya yeni satır ekle (Index 2, Uzunluk 5, Değer 30):\n");
    insertRow(&matrix, &rows, &rowLengths, 2, 5, 30);
    printMatrixRobust(matrix, rowLengths, rows);
    printf("\nSonuna yeni satır ekle (Index 4, Uzunluk 1, Değer 40):\n");
    insertRow(&matrix, &rows, &rowLengths, 4, 1, 40);
    printMatrixRobust(matrix, rowLengths, rows);
    printf("\nBelleği serbest bırakılıyor...\n");
    freeMatrix(&matrix, &rowLengths, &rows);
    printMatrixRobust(matrix, rowLengths, rows);
    return 0;
}