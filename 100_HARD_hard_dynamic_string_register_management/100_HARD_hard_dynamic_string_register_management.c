#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    int initial_capacity = 2;
    int current_capacity = initial_capacity;
    int name_count = 0;
    char **register_names = (char **)malloc(current_capacity * sizeof(char *));
    if (register_names == NULL) {
        return 1;
    }
    const char *initial_names[] = {"Alice", "Bob", "Charlie", "David", "Erica"};
    int num_initial_names = sizeof(initial_names) / sizeof(initial_names[0]);
    for (int i = 0; i < num_initial_names; i++) {
        if (name_count == current_capacity) {
            current_capacity *= 2;
            char **temp_register = (char **)realloc(register_names, current_capacity * sizeof(char *));
            if (temp_register == NULL) {
                for (int k = 0; k < name_count; k++) {
                    free(register_names[k]);
                }
                free(register_names);
                return 1;
            }
            register_names = temp_register;
        }
        size_t name_len = strlen(initial_names[i]);
        register_names[name_count] = (char *)malloc((name_len + 1) * sizeof(char));
        if (register_names[name_count] == NULL) {
            for (int k = 0; k < name_count; k++) {
                free(register_names[k]);
            }
            free(register_names);
            return 1;
        }
        strcpy(register_names[name_count], initial_names[i]);
        name_count++;
    }
    printf("--- Initial Names ---\n");
    for (int i = 0; i < name_count; i++) {
        printf("%d: %s\n", i, register_names[i]);
    }
    int reverse_idx = 2;
    if (reverse_idx < name_count) {
        char *name_ptr = register_names[reverse_idx];
        size_t len = strlen(name_ptr);
        for (size_t i = 0; i < len / 2; i++) {
            char temp = name_ptr[i];
            name_ptr[i] = name_ptr[len - 1 - i];
            name_ptr[len - 1 - i] = temp;
        }
    }
    printf("--- After Reversing Name at Index %d ---\n", reverse_idx);
    for (int i = 0; i < name_count; i++) {
        printf("%d: %s\n", i, register_names[i]);
    }
    int remove_idx = 3;
    if (remove_idx < name_count) {
        free(register_names[remove_idx]);
        for (int i = remove_idx; i < name_count - 1; i++) {
            register_names[i] = register_names[i + 1];
        }
        name_count--;
        if (name_count > initial_capacity && name_count < current_capacity / 4) {
            int new_capacity = current_capacity / 2;
            char **temp_register = (char **)realloc(register_names, new_capacity * sizeof(char *));
            if (temp_register != NULL) {
                register_names = temp_register;
                current_capacity = new_capacity;
            }
        }
    }
    printf("--- After Removing Name at Index %d ---\n", remove_idx);
    for (int i = 0; i < name_count; i++) {
        printf("%d: %s\n", i, register_names[i]);
    }
    for (int i = 0; i < name_count; i++) {
        free(register_names[i]);
    }
    free(register_names);
    return 0;
}