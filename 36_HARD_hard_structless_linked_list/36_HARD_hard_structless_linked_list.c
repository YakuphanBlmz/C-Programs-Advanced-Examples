#include <stdio.h>
#include <stdlib.h>
void add_to_head(void** head_ref, int value) {
    void* new_node_memory = malloc(sizeof(int) + sizeof(void*));
    if (new_node_memory == NULL) {
        fprintf(stderr, "Memory allocation failed in add_to_head.\n");
        exit(EXIT_FAILURE);
    }
    *(int*)new_node_memory = value;
    *(void**)((char*)new_node_memory + sizeof(int)) = *head_ref;
    *head_ref = new_node_memory;
}
int remove_from_head(void** head_ref) {
    if (*head_ref == NULL) {
        fprintf(stderr, "Error: Attempted to remove from an empty list.\n");
        exit(EXIT_FAILURE);
    }
    void* current_head = *head_ref;
    int value = *(int*)current_head;
    void* next_node = *(void**)((char*)current_head + sizeof(int));
    *head_ref = next_node;
    free(current_head);
    return value;
}
void print_list(void* head) {
    void* current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", *(int*)current);
        current = *(void**)((char*)current + sizeof(int));
    }
    printf("\n");
}
void free_list(void** head_ref) {
    void* current = *head_ref;
    void* next;
    while (current != NULL) {
        next = *(void**)((char*)current + sizeof(int));
        free(current);
        current = next;
    }
    *head_ref = NULL;
}
int main() {
    void* head = NULL;
    printf("Adding elements to the list:\n");
    add_to_head(&head, 10);
    add_to_head(&head, 20);
    add_to_head(&head, 30);
    print_list(head);
    printf("Removing head element:\n");
    int removed_val = remove_from_head(&head);
    printf("Removed value: %d\n", removed_val);
    print_list(head);
    printf("Adding another element:\n");
    add_to_head(&head, 40);
    print_list(head);
    printf("Removing two more elements:\n");
    removed_val = remove_from_head(&head);
    printf("Removed value: %d\n", removed_val);
    print_list(head);
    removed_val = remove_from_head(&head);
    printf("Removed value: %d\n", removed_val);
    print_list(head);
    printf("Freeing the entire list:\n");
    free_list(&head);
    print_list(head);
    return 0;
}