#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int filter_and_compact_strings(char*** string_array_ptr, int *current_size_ptr, int min_length) {
    char** array = *string_array_ptr;
    int current_size = *current_size_ptr;
    int write_idx = 0;
    for (int read_idx = 0; read_idx < current_size; read_idx++) {
        if (strlen(array[read_idx]) >= min_length) {
            if (read_idx != write_idx) {
                array[write_idx] = array[read_idx];
            }
            write_idx++;
        } else {
            free(array[read_idx]);
        }
    }
    int new_size = write_idx;
    if (new_size == 0) {
        free(array);
        *string_array_ptr = NULL;
    } else {
        char** temp_array = (char**)realloc(array, new_size * sizeof(char*));
        *string_array_ptr = temp_array;
    }
    *current_size_ptr = new_size;
    return new_size;
}
int main() {
    int initial_string_count = 7;
    char** my_strings = (char**)malloc(initial_string_count * sizeof(char*));
    int current_count = initial_string_count;
    my_strings[0] = (char*)malloc(strlen("apple") + 1);
    strcpy(my_strings[0], "apple");
    my_strings[1] = (char*)malloc(strlen("banana") + 1);
    strcpy(my_strings[1], "banana");
    my_strings[2] = (char*)malloc(strlen("cat") + 1);
    strcpy(my_strings[2], "cat");
    my_strings[3] = (char*)malloc(strlen("dog") + 1);
    strcpy(my_strings[3], "dog");
    my_strings[4] = (char*)malloc(strlen("elephant") + 1);
    strcpy(my_strings[4], "elephant");
    my_strings[5] = (char*)malloc(strlen("a") + 1);
    strcpy(my_strings[5], "a");
    my_strings[6] = (char*)malloc(strlen("frog") + 1);
    strcpy(my_strings[6], "frog");
    printf("Original strings (%d):\n", current_count);
    for (int i = 0; i < current_count; i++) {
        printf("  %s\n", my_strings[i]);
    }
    int min_len = 4;
    printf("\nFiltering strings with minimum length %d...\n", min_len);
    int new_count = filter_and_compact_strings(&my_strings, &current_count, min_len);
    printf("\nFiltered strings (%d):\n", new_count);
    if (my_strings != NULL) {
        for (int i = 0; i < new_count; i++) {
            printf("  %s\n", my_strings[i]);
        }
    } else {
        printf("  (No strings remaining)\n");
    }
    if (my_strings != NULL) {
        for (int i = 0; i < new_count; i++) {
            free(my_strings[i]);
        }
        free(my_strings);
    }
    return 0;
}