#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_CAPACITY 2
#define GROWTH_FACTOR 2
#define SHRINK_FACTOR 4
int main() {
    char **lines = NULL;
    int current_capacity = 0;
    int current_size = 0;
    lines = (char **)malloc(INITIAL_CAPACITY * sizeof(char *));
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation failed for initial lines array.\n");
        return 1;
    }
    current_capacity = INITIAL_CAPACITY;
    printf("Initial buffer allocated with capacity: %d\n", current_capacity);
    const char *new_line_1 = "This is the first line.";
    const char *new_line_2 = "Second line, a bit longer than the first.";
    const char *new_line_3 = "Third, and the buffer might need resizing.";
    if (current_size == current_capacity) {
        int new_capacity = current_capacity * GROWTH_FACTOR;
        char **temp_lines = (char **)realloc(lines, new_capacity * sizeof(char *));
        if (temp_lines == NULL) {
            fprintf(stderr, "Memory re-allocation failed for lines array.\n");
            for (int i = 0; i < current_size; i++) { free(lines[i]); }
            free(lines);
            return 1;
        }
        lines = temp_lines;
        current_capacity = new_capacity;
        printf("Buffer resized to capacity: %d\n", current_capacity);
    }
    lines[current_size] = (char *)malloc((strlen(new_line_1) + 1) * sizeof(char));
    if (lines[current_size] == NULL) {
        fprintf(stderr, "Memory allocation failed for line %d.\n", current_size);
        for (int i = 0; i < current_size; i++) { free(lines[i]); } free(lines); return 1;
    }
    strcpy(lines[current_size], new_line_1);
    current_size++;
    printf("Added: \"%s\" (Current lines: %d/%d)\n", new_line_1, current_size, current_capacity);
    if (current_size == current_capacity) {
        int new_capacity = current_capacity * GROWTH_FACTOR;
        char **temp_lines = (char **)realloc(lines, new_capacity * sizeof(char *));
        if (temp_lines == NULL) {
            fprintf(stderr, "Memory re-allocation failed for lines array.\n");
            for (int i = 0; i < current_size; i++) { free(lines[i]); } free(lines); return 1;
        }
        lines = temp_lines;
        current_capacity = new_capacity;
        printf("Buffer resized to capacity: %d\n", current_capacity);
    }
    lines[current_size] = (char *)malloc((strlen(new_line_2) + 1) * sizeof(char));
    if (lines[current_size] == NULL) {
        fprintf(stderr, "Memory allocation failed for line %d.\n", current_size);
        for (int i = 0; i < current_size; i++) { free(lines[i]); } free(lines); return 1;
    }
    strcpy(lines[current_size], new_line_2);
    current_size++;
    printf("Added: \"%s\" (Current lines: %d/%d)\n", new_line_2, current_size, current_capacity);
    if (current_size == current_capacity) {
        int new_capacity = current_capacity * GROWTH_FACTOR;
        char **temp_lines = (char **)realloc(lines, new_capacity * sizeof(char *));
        if (temp_lines == NULL) {
            fprintf(stderr, "Memory re-allocation failed for lines array.\n");
            for (int i = 0; i < current_size; i++) { free(lines[i]); } free(lines); return 1;
        }
        lines = temp_lines;
        current_capacity = new_capacity;
        printf("Buffer resized to capacity: %d\n", current_capacity);
    }
    lines[current_size] = (char *)malloc((strlen(new_line_3) + 1) * sizeof(char));
    if (lines[current_size] == NULL) {
        fprintf(stderr, "Memory allocation failed for line %d.\n", current_size);
        for (int i = 0; i < current_size; i++) { free(lines[i]); } free(lines); return 1;
    }
    strcpy(lines[current_size], new_line_3);
    current_size++;
    printf("Added: \"%s\" (Current lines: %d/%d)\n", new_line_3, current_size, current_capacity);
    printf("\n--- Current Lines ---\n");
    for (int i = 0; i < current_size; i++) {
        printf("Line %d: %s\n", i, lines[i]);
    }
    const char *modified_line_1 = "FIRST line, now modified and a bit longer.";
    int modify_idx = 0;
    printf("\nModifying line %d: \"%s\" -> \"%s\"\n", modify_idx, lines[modify_idx], modified_line_1);
    char *temp_str = (char *)realloc(lines[modify_idx], (strlen(modified_line_1) + 1) * sizeof(char));
    if (temp_str == NULL) {
        fprintf(stderr, "Memory re-allocation failed for line %d.\n", modify_idx);
        for (int i = 0; i < current_size; i++) { free(lines[i]); } free(lines); return 1;
    }
    lines[modify_idx] = temp_str;
    strcpy(lines[modify_idx], modified_line_1);
    printf("Line %d modified to: %s\n", modify_idx, lines[modify_idx]);
    printf("\n--- Current Lines After Modification ---\n");
    for (int i = 0; i < current_size; i++) {
        printf("Line %d: %s\n", i, lines[i]);
    }
    int delete_idx = 1;
    if (delete_idx >= 0 && delete_idx < current_size) {
        printf("\nDeleting line %d: \"%s\"\n", delete_idx, lines[delete_idx]);
        free(lines[delete_idx]);
        for (int i = delete_idx; i < current_size - 1; i++) {
            lines[i] = lines[i+1];
        }
        current_size--;
        printf("Line %d deleted. Current lines: %d/%d\n", delete_idx, current_size, current_capacity);
        if (current_size > 0 && current_capacity / SHRINK_FACTOR > current_size) {
            int new_capacity = current_capacity / GROWTH_FACTOR;
            if (new_capacity < INITIAL_CAPACITY && INITIAL_CAPACITY > 0) new_capacity = INITIAL_CAPACITY;
            if (new_capacity < current_size) new_capacity = current_size; 
            if (new_capacity < current_capacity) {
                char **temp_lines = (char **)realloc(lines, new_capacity * sizeof(char *));
                if (temp_lines == NULL) {
                    fprintf(stderr, "Memory re-allocation (shrink) failed for lines array. Continuing without shrinking.\n");
                } else {
                    lines = temp_lines;
                    current_capacity = new_capacity;
                    printf("Buffer shrunk to capacity: %d\n", current_capacity);
                }
            }
        }
    }
    printf("\n--- Current Lines After Deletion ---\n");
    for (int i = 0; i < current_size; i++) {
        printf("Line %d: %s\n", i, lines[i]);
    }
    delete_idx = 1;
    if (delete_idx >= 0 && delete_idx < current_size) {
        printf("\nDeleting line %d: \"%s\"\n", delete_idx, lines[delete_idx]);
        free(lines[delete_idx]);
        for (int i = delete_idx; i < current_size - 1; i++) {
            lines[i] = lines[i+1];
        }
        current_size--;
        printf("Line %d deleted. Current lines: %d/%d\n", delete_idx, current_size, current_capacity);
        if (current_size > 0 && current_capacity / SHRINK_FACTOR > current_size) {
            int new_capacity = current_capacity / GROWTH_FACTOR;
            if (new_capacity < INITIAL_CAPACITY && INITIAL_CAPACITY > 0) new_capacity = INITIAL_CAPACITY;
            if (new_capacity < current_size) new_capacity = current_size;
            if (new_capacity < current_capacity) {
                char **temp_lines = (char **)realloc(lines, new_capacity * sizeof(char *));
                if (temp_lines == NULL) {
                    fprintf(stderr, "Memory re-allocation (shrink) failed for lines array. Continuing without shrinking.\n");
                } else {
                    lines = temp_lines;
                    current_capacity = new_capacity;
                    printf("Buffer shrunk to capacity: %d\n", current_capacity);
                }
            }
        }
    }
    printf("\n--- Current Lines After Second Deletion ---\n");
    for (int i = 0; i < current_size; i++) {
        printf("Line %d: %s\n", i, lines[i]);
    }
    printf("\nCleaning up memory...\n");
    for (int i = 0; i < current_size; i++) {
        free(lines[i]);
        lines[i] = NULL;
    }
    free(lines);
    lines = NULL;
    printf("Memory cleanup complete.\n");
    return 0;
}