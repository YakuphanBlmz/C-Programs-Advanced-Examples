#include <stdio.h>
#include <stdlib.h>
int main() {
    int **dal = NULL;
    int num_lines = 0;
    int *line_lengths = NULL;
    printf("Initializing Dynamic Array of Lines (DAL) operations.\n");
    printf("\nAdding line 1 (length 5).\n");
    int new_line_len1 = 5;
    int **temp_dal_realloc_ptr = (int **)realloc(dal, (num_lines + 1) * sizeof(int *));
    if (temp_dal_realloc_ptr == NULL) {
        fprintf(stderr, "Error: Failed to reallocate DAL for new line 1.\n");
        exit(EXIT_FAILURE);
    }
    dal = temp_dal_realloc_ptr;
    int *temp_line_lengths_realloc_ptr = (int *)realloc(line_lengths, (num_lines + 1) * sizeof(int));
    if (temp_line_lengths_realloc_ptr == NULL) {
        fprintf(stderr, "Error: Failed to reallocate line_lengths for new line 1.\n");
        exit(EXIT_FAILURE);
    }
    line_lengths = temp_line_lengths_realloc_ptr;
    dal[num_lines] = (int *)malloc(new_line_len1 * sizeof(int));
    if (dal[num_lines] == NULL) {
        fprintf(stderr, "Error: Failed to allocate line 1 content.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < new_line_len1; i++) {
        dal[num_lines][i] = i + 10;
    }
    line_lengths[num_lines] = new_line_len1;
    num_lines++;
    printf("DAL after adding line 1:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("  Line %d (length %d): ", i, line_lengths[i]);
        for (int j = 0; j < line_lengths[i]; j++) {
            printf("%d ", dal[i][j]);
        }
        printf("\n");
    }
    printf("\nAdding line 2 (length 3).\n");
    int new_line_len2 = 3;
    temp_dal_realloc_ptr = (int **)realloc(dal, (num_lines + 1) * sizeof(int *));
    if (temp_dal_realloc_ptr == NULL) {
        fprintf(stderr, "Error: Failed to reallocate DAL for new line 2.\n");
        exit(EXIT_FAILURE);
    }
    dal = temp_dal_realloc_ptr;
    temp_line_lengths_realloc_ptr = (int *)realloc(line_lengths, (num_lines + 1) * sizeof(int));
    if (temp_line_lengths_realloc_ptr == NULL) {
        fprintf(stderr, "Error: Failed to reallocate line_lengths for new line 2.\n");
        exit(EXIT_FAILURE);
    }
    line_lengths = temp_line_lengths_realloc_ptr;
    dal[num_lines] = (int *)malloc(new_line_len2 * sizeof(int));
    if (dal[num_lines] == NULL) {
        fprintf(stderr, "Error: Failed to allocate line 2 content.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < new_line_len2; i++) {
        dal[num_lines][i] = (i + 1) * 100;
    }
    line_lengths[num_lines] = new_line_len2;
    num_lines++;
    printf("DAL after adding line 2:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("  Line %d (length %d): ", i, line_lengths[i]);
        for (int j = 0; j < line_lengths[i]; j++) {
            printf("%d ", dal[i][j]);
        }
        printf("\n");
    }
    printf("\nModifying dal[0][2] = 999.\n");
    if (num_lines > 0 && line_lengths[0] > 2) {
        dal[0][2] = 999;
    }
    printf("DAL after modifying line 0:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("  Line %d (length %d): ", i, line_lengths[i]);
        for (int j = 0; j < line_lengths[i]; j++) {
            printf("%d ", dal[i][j]);
        }
        printf("\n");
    }
    printf("\nResizing line 0 from length %d to 8.\n", line_lengths[0]);
    int index_to_resize = 0;
    int new_resized_len = 8;
    if (index_to_resize < num_lines) {
        int *temp_line_realloc_ptr = (int *)realloc(dal[index_to_resize], new_resized_len * sizeof(int));
        if (temp_line_realloc_ptr == NULL) {
            fprintf(stderr, "Error: Failed to reallocate line %d.\n", index_to_resize);
            exit(EXIT_FAILURE);
        }
        dal[index_to_resize] = temp_line_realloc_ptr;
        for (int i = line_lengths[index_to_resize]; i < new_resized_len; i++) {
            dal[index_to_resize][i] = 0;
        }
        line_lengths[index_to_resize] = new_resized_len;
    }
    printf("DAL after resizing line 0:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("  Line %d (length %d): ", i, line_lengths[i]);
        for (int j = 0; j < line_lengths[i]; j++) {
            printf("%d ", dal[i][j]);
        }
        printf("\n");
    }
    printf("\nRemoving line at index 0.\n");
    int index_to_remove = 0;
    if (index_to_remove < num_lines) {
        free(dal[index_to_remove]);
        for (int i = index_to_remove; i < num_lines - 1; i++) {
            dal[i] = dal[i + 1];
            line_lengths[i] = line_lengths[i + 1];
        }
        num_lines--;
        if (num_lines == 0) {
            free(dal);
            dal = NULL;
            free(line_lengths);
            line_lengths = NULL;
        } else {
            temp_dal_realloc_ptr = (int **)realloc(dal, num_lines * sizeof(int *));
            if (temp_dal_realloc_ptr == NULL) {
                fprintf(stderr, "Error: Failed to reallocate DAL after removing line.\n");
                exit(EXIT_FAILURE);
            }
            dal = temp_dal_realloc_ptr;
            temp_line_lengths_realloc_ptr = (int *)realloc(line_lengths, num_lines * sizeof(int));
            if (temp_line_lengths_realloc_ptr == NULL) {
                fprintf(stderr, "Error: Failed to reallocate line_lengths after removing line.\n");
                exit(EXIT_FAILURE);
            }
            line_lengths = temp_line_lengths_realloc_ptr;
        }
    }
    printf("DAL after removing line 0:\n");
    for (int i = 0; i < num_lines; i++) {
        printf("  Line %d (length %d): ", i, line_lengths[i]);
        for (int j = 0; j < line_lengths[i]; j++) {
            printf("%d ", dal[i][j]);
        }
        printf("\n");
    }
    printf("\nCleaning up all allocated memory.\n");
    for (int i = 0; i < num_lines; i++) {
        free(dal[i]);
    }
    free(dal);
    free(line_lengths);
    printf("Memory successfully freed. Program exiting.\n");
    return 0;
}