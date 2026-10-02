#include <stdio.h>
#include <stdlib.h>
int manual_strlen(const char* s) {
    int len = 0;
    if (s == NULL) {
        return 0;
    }
    while (s[len] != '\0') {
        len++;
    }
    return len;
}
char* manual_str_copy_alloc(const char* source) {
    if (source == NULL) {
        return NULL;
    }
    int len = manual_strlen(source);
    char* dest = (char*)malloc((len + 1) * sizeof(char));
    if (dest == NULL) {
        return NULL;
    }
    for (int i = 0; i <= len; i++) {
        dest[i] = source[i];
    }
    return dest;
}
void add_string(char*** array_ptr, int* size_ptr, int* capacity_ptr, const char* new_str) {
    if (*size_ptr == *capacity_ptr) {
        int new_capacity = (*capacity_ptr == 0) ? 4 : (*capacity_ptr * 2);
        char** temp = (char**)realloc(*array_ptr, new_capacity * sizeof(char*));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed during add_string.\n");
            exit(EXIT_FAILURE);
        }
        *array_ptr = temp;
        *capacity_ptr = new_capacity;
    }
    char* copied_str = manual_str_copy_alloc(new_str);
    if (copied_str == NULL) {
        fprintf(stderr, "Memory allocation failed for new string during add_string.\n");
        exit(EXIT_FAILURE);
    }
    (*array_ptr)[*size_ptr] = copied_str;
    (*size_ptr)++;
}
void remove_string(char*** array_ptr, int* size_ptr, int* capacity_ptr, int index) {
    if (index < 0 || index >= *size_ptr) {
        fprintf(stderr, "Invalid index for remove_string.\n");
        return;
    }
    free((*array_ptr)[index]);
    for (int i = index; i < *size_ptr - 1; i++) {
        (*array_ptr)[i] = (*array_ptr)[i+1];
    }
    (*size_ptr)--;
    if (*size_ptr > 0 && *size_ptr < *capacity_ptr / 4) {
        int new_capacity = *capacity_ptr / 2;
        char** temp = (char**)realloc(*array_ptr, new_capacity * sizeof(char*));
        if (temp == NULL) {
            fprintf(stderr, "Memory reallocation failed during remove_string.\n");
            exit(EXIT_FAILURE);
        }
        *array_ptr = temp;
        *capacity_ptr = new_capacity;
    } else if (*size_ptr == 0) {
        free(*array_ptr);
        *array_ptr = NULL;
        *capacity_ptr = 0;
    }
}
void update_string(char*** array_ptr, int size, int index, const char* new_str) {
    if (index < 0 || index >= size) {
        fprintf(stderr, "Invalid index for update_string.\n");
        return;
    }
    free((*array_ptr)[index]);
    char* copied_str = manual_str_copy_alloc(new_str);
    if (copied_str == NULL) {
        fprintf(stderr, "Memory allocation failed for new string during update_string.\n");
        exit(EXIT_FAILURE);
    }
    (*array_ptr)[index] = copied_str;
}
void print_strings(char** array, int size) {
    printf("--- Current Strings (%d) ---\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d: %s\n", i, array[i]);
    }
    printf("---------------------------\n");
}
void free_all_memory(char*** array_ptr, int* size_ptr) {
    if (*array_ptr == NULL) {
        return;
    }
    for (int i = 0; i < *size_ptr; i++) {
        free((*array_ptr)[i]);
        (*array_ptr)[i] = NULL;
    }
    free(*array_ptr);
    *array_ptr = NULL;
    *size_ptr = 0;
}
int main() {
    char** my_strings = NULL;
    int current_size = 0;
    int current_capacity = 0;
    add_string(&my_strings, &current_size, &current_capacity, "Hello");
    add_string(&my_strings, &current_size, &current_capacity, "World");
    add_string(&my_strings, &current_size, &current_capacity, "C Programming");
    print_strings(my_strings, current_size);
    update_string(&my_strings, current_size, 0, "Greetings");
    add_string(&my_strings, &current_size, &current_capacity, "Dynamic Memory");
    print_strings(my_strings, current_size);
    remove_string(&my_strings, &current_size, &current_capacity, 1);
    print_strings(my_strings, current_size);
    add_string(&my_strings, &current_size, &current_capacity, "Pointers Are Fun");
    add_string(&my_strings, &current_size, &current_capacity, "Memory Management");
    print_strings(my_strings, current_size);
    remove_string(&my_strings, &current_size, &current_capacity, 0);
    remove_string(&my_strings, &current_size, &current_capacity, 0);
    remove_string(&my_strings, &current_size, &current_capacity, 0);
    remove_string(&my_strings, &current_size, &current_capacity, 0);
    print_strings(my_strings, current_size);
    free_all_memory(&my_strings, &current_size);
    printf("All memory freed. Final size: %d\n", current_size);
    return 0;
}