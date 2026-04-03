#include <stdio.h>
#include <stdlib.h>
int get_node_data(void *node) {
    return *(int *)node;
}
void *get_node_next(void *node) {
    return *(void **)((char *)node + sizeof(int));
}
void set_node_next(void *node, void *next_node) {
    *(void **)((char *)node + sizeof(int)) = next_node;
}
void *create_node(int value, void *next_node) {
    void *node = malloc(sizeof(int) + sizeof(void *));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed for node\n");
        exit(EXIT_FAILURE);
    }
    *(int *)node = value;
    *(void **)((char *)node + sizeof(int)) = next_node;
    return node;
}
void *reverse_list(void *head) {
    void *prev = NULL;
    void *current = head;
    void *next_node;
    while (current != NULL) {
        next_node = get_node_next(current);
        set_node_next(current, prev);
        prev = current;
        current = next_node;
    }
    return prev;
}
void free_list(void *head) {
    void *current = head;
    void *next_node;
    while (current != NULL) {
        next_node = get_node_next(current);
        free(current);
        current = next_node;
    }
}
int main() {
    int values[] = {10, 20, 30, 40, 50};
    int n = sizeof(values) / sizeof(values[0]);
    void *head = NULL;
    for (int i = n - 1; i >= 0; i--) {
        head = create_node(values[i], head);
    }
    printf("Original List: ");
    void *current = head;
    while (current != NULL) {
        printf("%d ", get_node_data(current));
        current = get_node_next(current);
    }
    printf("\n");
    head = reverse_list(head);
    printf("Reversed List: ");
    current = head;
    while (current != NULL) {
        printf("%d ", get_node_data(current));
        current = get_node_next(current);
    }
    printf("\n");
    free_list(head);
    return 0;
}