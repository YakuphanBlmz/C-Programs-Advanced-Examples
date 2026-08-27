#include <stdio.h>
#include <stdlib.h>
int get_string_length(const char *s) {
    int length = 0;
    while (*s != '\0') {
        length++;
        s++;
    }
    return length;
}
int main() {
    const char *initial_data[] = {
        "apple",
        "banana",
        "cat",
        "doggy",
        "elephant",
        "frog",
        "zebra",
        "ant"
    };
    int num_initial_strings = sizeof(initial_data) / sizeof(initial_data[0]);
    char **string_array = (char **)malloc(num_initial_strings * sizeof(char *));
    if (string_array == NULL) {
        return 1;
    }
    for (int i = 0; i < num_initial_strings; i++) {
        int len = get_string_length(initial_data[i]);
        string_array[i] = (char *)malloc((len + 1) * sizeof(char));
        if (string_array[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(string_array[j]);
            }
            free(string_array);
            return 1;
        }
        for (int k = 0; k <= len; k++) {
            string_array[i][k] = initial_data[i][k];
        }
    }
    printf("Original strings:\n");
    for (int i = 0; i < num_initial_strings; i++) {
        printf("  %s (length: %d)\n", string_array[i], get_string_length(string_array[i]));
    }
    printf("\n");
    for (int i = 0; i < num_initial_strings - 1; i++) {
        for (int j = 0; j < num_initial_strings - i - 1; j++) {
            if (get_string_length(string_array[j]) > get_string_length(string_array[j+1])) {
                char *temp = string_array[j];
                string_array[j] = string_array[j+1];
                string_array[j+1] = temp;
            }
        }
    }
    printf("Sorted strings by length:\n");
    for (int i = 0; i < num_initial_strings; i++) {
        printf("  %s (length: %d)\n", string_array[i], get_string_length(string_array[i]));
    }
    printf("\n");
    for (int i = 0; i < num_initial_strings; i++) {
        free(string_array[i]);
    }
    free(string_array);
    return 0;
}