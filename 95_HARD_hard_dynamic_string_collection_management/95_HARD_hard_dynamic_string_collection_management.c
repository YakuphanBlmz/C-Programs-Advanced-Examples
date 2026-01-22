#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char **g_strings = NULL;
int g_current_count = 0;
int g_allocated_capacity = 0;
void initializeCollection(int initialCapacity) {
    g_strings = (char **)malloc(initialCapacity * sizeof(char *));
    if (g_strings == NULL) {
        exit(EXIT_FAILURE);
    }
    g_allocated_capacity = initialCapacity;
    g_current_count = 0;
}
void resizeCollection(int newCapacity) {
    char **temp_strings = (char **)realloc(g_strings, newCapacity * sizeof(char *));
    if (temp_strings == NULL) {
        exit(EXIT_FAILURE);
    }
    g_strings = temp_strings;
    g_allocated_capacity = newCapacity;
}
void addString(const char *str) {
    if (g_current_count == g_allocated_capacity) {
        resizeCollection(g_allocated_capacity * 2);
    }
    g_strings[g_current_count] = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (g_strings[g_current_count] == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(g_strings[g_current_count], str);
    g_current_count++;
}
void insertString(const char *str, int index) {
    if (index < 0 || index > g_current_count) {
        return;
    }
    if (g_current_count == g_allocated_capacity) {
        resizeCollection(g_allocated_capacity * 2);
    }
    memmove(&g_strings[index + 1], &g_strings[index], (g_current_count - index) * sizeof(char *));
    g_strings[index] = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (g_strings[index] == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(g_strings[index], str);
    g_current_count++;
}
void mergeAndRemoveString(int targetIndex, int sourceIndex) {
    if (targetIndex < 0 || targetIndex >= g_current_count ||
        sourceIndex < 0 || sourceIndex >= g_current_count ||
        targetIndex == sourceIndex) {
        return;
    }
    char *merged_content = (char *)malloc(strlen(g_strings[targetIndex]) + strlen(g_strings[sourceIndex]) + 1);
    if (merged_content == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(merged_content, g_strings[targetIndex]);
    strcat(merged_content, g_strings[sourceIndex]);
    free(g_strings[targetIndex]);
    g_strings[targetIndex] = merged_content;
    free(g_strings[sourceIndex]);
    memmove(&g_strings[sourceIndex], &g_strings[sourceIndex + 1], (g_current_count - sourceIndex - 1) * sizeof(char *));
    g_current_count--;
    if (g_current_count > 0 && g_current_count * 4 < g_allocated_capacity && g_allocated_capacity > 4) {
        resizeCollection(g_allocated_capacity / 2);
    } else if (g_current_count == 0 && g_allocated_capacity > 4) {
        resizeCollection(4);
    }
}
void printCollection() {
    printf("Current String Collection (Count: %d, Capacity: %d):\n", g_current_count, g_allocated_capacity);
    for (int i = 0; i < g_current_count; i++) {
        printf("  [%d]: \"%s\"\n", i, g_strings[i]);
    }
}
void freeCollection() {
    for (int i = 0; i < g_current_count; i++) {
        free(g_strings[i]);
    }
    free(g_strings);
    g_strings = NULL;
    g_current_count = 0;
    g_allocated_capacity = 0;
}
int main() {
    initializeCollection(4);
    addString("Alpha");
    addString("Bravo");
    addString("Charlie");
    addString("Delta");
    printCollection();
    insertString("Echo", 1);
    printCollection();
    addString("Foxtrot");
    printCollection();
    mergeAndRemoveString(0, 2);
    printCollection();
    insertString("Gamma", 3);
    printCollection();
    mergeAndRemoveString(1, 3);
    printCollection();
    freeCollection();
    return 0;
}