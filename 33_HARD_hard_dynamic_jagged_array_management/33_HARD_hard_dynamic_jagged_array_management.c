#include <stdio.h>
#include <stdlib.h>
#define INITIAL_TABLE_CAPACITY 2
#define TABLE_GROWTH_FACTOR 2
#define INITIAL_ROW_CAPACITY 4
#define ROW_GROWTH_FACTOR 2
int main() {
    int **table = NULL;
    int *row_lengths = NULL;
    int *row_capacities = NULL;
    int table_rows = 0;
    int table_capacity = 0;
    printf("Initializing and adding first row...\n");
    if (table_capacity == 0) {
        table_capacity = INITIAL_TABLE_CAPACITY;
        table = (int **)malloc(table_capacity * sizeof(int *));
        row_lengths = (int *)malloc(table_capacity * sizeof(int));
        row_capacities = (int *)malloc(table_capacity * sizeof(int));
        if (!table || !row_lengths || !row_capacities) {
            fprintf(stderr, "Initial allocation failed\n");
            return 1;
        }
    }
    table[table_rows] = (int *)malloc(INITIAL_ROW_CAPACITY * sizeof(int));
    if (!table[table_rows]) {
        fprintf(stderr, "Row allocation failed\n");
        return 1;
    }
    row_lengths[table_rows] = 0;
    row_capacities[table_rows] = INITIAL_ROW_CAPACITY;
    table_rows++;
    for (int i = 0; i < 5; i++) {
        int rowIndex = 0;
        if (row_lengths[rowIndex] == row_capacities[rowIndex]) {
            int new_cap = row_capacities[rowIndex] * ROW_GROWTH_FACTOR;
            int *temp = (int *)realloc(table[rowIndex], new_cap * sizeof(int));
            if (!temp) {
                fprintf(stderr, "Row realloc failed\n");
                for (int r = 0; r < table_rows; r++) free(table[r]);
                free(table); free(row_lengths); free(row_capacities);
                return 1;
            }
            table[rowIndex] = temp;
            row_capacities[rowIndex] = new_cap;
        }
        table[rowIndex][row_lengths[rowIndex]++] = i * 10;
    }
    printf("Adding second row...\n");
    if (table_rows == table_capacity) {
        table_capacity *= TABLE_GROWTH_FACTOR;
        int **temp_table = (int **)realloc(table, table_capacity * sizeof(int *));
        int *temp_lengths = (int *)realloc(row_lengths, table_capacity * sizeof(int));
        int *temp_caps = (int *)realloc(row_capacities, table_capacity * sizeof(int));
        if (!temp_table || !temp_lengths || !temp_caps) {
            fprintf(stderr, "Table realloc failed\n");
            for (int r = 0; r < table_rows; r++) free(table[r]);
            free(table); free(row_lengths); free(row_capacities);
            return 1;
        }
        table = temp_table;
        row_lengths = temp_lengths;
        row_capacities = temp_caps;
    }
    table[table_rows] = (int *)malloc(INITIAL_ROW_CAPACITY * sizeof(int));
    if (!table[table_rows]) {
        fprintf(stderr, "Row allocation failed\n");
        for (int r = 0; r < table_rows; r++) free(table[r]);
        free(table); free(row_lengths); free(row_capacities);
        return 1;
    }
    row_lengths[table_rows] = 0;
    row_capacities[table_rows] = INITIAL_ROW_CAPACITY;
    table_rows++;
    for (int i = 0; i < 3; i++) {
        int rowIndex = 1;
        if (row_lengths[rowIndex] == row_capacities[rowIndex]) {
            int new_cap = row_capacities[rowIndex] * ROW_GROWTH_FACTOR;
            int *temp = (int *)realloc(table[rowIndex], new_cap * sizeof(int));
            if (!temp) {
                fprintf(stderr, "Row realloc failed\n");
                for (int r = 0; r < table_rows; r++) free(table[r]);
                free(table); free(row_lengths); free(row_capacities);
                return 1;
            }
            table[rowIndex] = temp;
            row_capacities[rowIndex] = new_cap;
        }
        table[rowIndex][row_lengths[rowIndex]++] = i * 11 + 1;
    }
    printf("\nCurrent Table State:\n");
    for (int r = 0; r < table_rows; r++) {
        printf("Row %d (length %d, capacity %d): ", r, row_lengths[r], row_capacities[r]);
        for (int c = 0; c < row_lengths[r]; c++) {
            printf("%d ", table[r][c]);
        }
        printf("\n");
    }
    printf("\nRemoving last element from Row 0...\n");
    if (table_rows > 0 && row_lengths[0] > 0) {
        row_lengths[0]--;
    }
    printf("\nTable State After Removing Last Element from Row 0:\n");
    for (int r = 0; r < table_rows; r++) {
        printf("Row %d (length %d, capacity %d): ", r, row_lengths[r], row_capacities[r]);
        for (int c = 0; c < row_lengths[r]; c++) {
            printf("%d ", table[r][c]);
        }
        printf("\n");
    }
    printf("\nRemoving Row 0...\n");
    if (table_rows > 0) {
        free(table[0]);
        for (int r = 0; r < table_rows - 1; r++) {
            table[r] = table[r + 1];
            row_lengths[r] = row_lengths[r + 1];
            row_capacities[r] = row_capacities[r + 1];
        }
        table_rows--;
    }
    printf("\nTable State After Removing Row 0:\n");
    for (int r = 0; r < table_rows; r++) {
        printf("Row %d (length %d, capacity %d): ", r, row_lengths[r], row_capacities[r]);
        for (int c = 0; c < row_lengths[r]; c++) {
            printf("%d ", table[r][c]);
        }
        printf("\n");
    }
    printf("\nCleaning up memory...\n");
    for (int r = 0; r < table_rows; r++) {
        free(table[r]);
    }
    free(table);
    free(row_lengths);
    free(row_capacities);
    table = NULL;
    row_lengths = NULL;
    row_capacities = NULL;
    table_rows = 0;
    table_capacity = 0;
    printf("Memory cleanup complete.\n");
    return 0;
}