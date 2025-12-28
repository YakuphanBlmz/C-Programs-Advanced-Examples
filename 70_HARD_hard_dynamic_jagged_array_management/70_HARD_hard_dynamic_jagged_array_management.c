#include <stdio.h>
#include <stdlib.h>
#define INITIAL_ALLOC_SIZE 4
#define GROWTH_FACTOR 2
void addElementToJaggedArray(int*** lines, int** line_counts, int** line_capacities,
                             int* line_array_count, int* line_array_capacity,
                             int line_index, int value) {
    if (line_index < 0) {
        return;
    }
    if (line_index >= *line_array_capacity) {
        int new_array_capacity = (*line_array_capacity == 0) ? INITIAL_ALLOC_SIZE : (*line_array_capacity) * GROWTH_FACTOR;
        if (line_index >= new_array_capacity) {
            new_array_capacity = line_index + 1;
        }
        int** new_lines_ptr = (int**)realloc(*lines, new_array_capacity * sizeof(int*));
        if (new_lines_ptr == NULL) {
            return;
        }
        *lines = new_lines_ptr;
        int* new_line_counts_ptr = (int*)realloc(*line_counts, new_array_capacity * sizeof(int));
        if (new_line_counts_ptr == NULL) {
            return;
        }
        *line_counts = new_line_counts_ptr;
        int* new_line_capacities_ptr = (int*)realloc(*line_capacities, new_array_capacity * sizeof(int));
        if (new_line_capacities_ptr == NULL) {
            return;
        }
        *line_capacities = new_line_capacities_ptr;
        for (int i = *line_array_capacity; i < new_array_capacity; ++i) {
            (*lines)[i] = NULL;
            (*line_counts)[i] = 0;
            (*line_capacities)[i] = 0;
        }
        *line_array_capacity = new_array_capacity;
    }
    if (line_index >= *line_array_count) {
        *line_array_count = line_index + 1;
    }
    if ((*lines)[line_index] == NULL) {
        (*lines)[line_index] = (int*)malloc(INITIAL_ALLOC_SIZE * sizeof(int));
        if ((*lines)[line_index] == NULL) {
            return;
        }
        (*line_counts)[line_index] = 0;
        (*line_capacities)[line_index] = INITIAL_ALLOC_SIZE;
    } else if ((*line_counts)[line_index] >= (*line_capacities)[line_index]) {
        int new_line_capacity = (*line_capacities)[line_index] * GROWTH_FACTOR;
        if (new_line_capacity == 0) new_line_capacity = INITIAL_ALLOC_SIZE;
        int* new_line_ptr = (int*)realloc((*lines)[line_index], new_line_capacity * sizeof(int));
        if (new_line_ptr == NULL) {
            return;
        }
        (*lines)[line_index] = new_line_ptr;
        (*line_capacities)[line_index] = new_line_capacity;
    }
    (*lines)[line_index][(*line_counts)[line_index]] = value;
    (*line_counts)[line_index]++;
}
int main() {
    int** lines = NULL;
    int* line_counts = NULL;
    int* line_capacities = NULL;
    int line_array_count = 0;
    int line_array_capacity = 0;
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 0, 10);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 0, 20);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 1, 30);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 0, 40);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 2, 50);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 1, 60);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 2, 70);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 5, 80);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 5, 90);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 5, 100);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 5, 110);
    addElementToJaggedArray(&lines, &line_counts, &line_capacities, &line_array_count, &line_array_capacity, 5, 120);
    for (int i = 0; i < line_array_count; ++i) {
        if (lines != NULL && lines[i] != NULL) {
            free(lines[i]);
            lines[i] = NULL;
        }
    }
    if (lines != NULL) {
        free(lines);
        lines = NULL;
    }
    if (line_counts != NULL) {
        free(line_counts);
        line_counts = NULL;
    }
    if (line_capacities != NULL) {
        free(line_capacities);
        line_capacities = NULL;
    }
    return 0;
}