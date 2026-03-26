#include <stdio.h>
#include <stdlib.h>
void **get_next_pointer_address(void *node_block) {
    return (void**)((char*)node_block + sizeof(int));
}
int *get_data_pointer_address(void *node_block) {
    return (int*)node_block;
}
void addNode(void **head_ptr, int value) {
    void *newNode = malloc(sizeof(int) + sizeof(void*));
    *get_data_pointer_address(newNode) = value;
    *get_next_pointer_address(newNode) = NULL;
    if (*head_ptr == NULL) {
        *head_ptr = newNode;
    } else {
        void *current = *head_ptr;
        while (*get_next_pointer_address(current) != NULL) {
            current = *get_next_pointer_address(current);
        }
        *get_next_pointer_address(current) = newNode;
    }
}
void deleteNode(void **head_ptr, int value) {
    void *current = *head_ptr;
    void *previous = NULL;
    while (current != NULL && *get_data_pointer_address(current) != value) {
        previous = current;
        current = *get_next_pointer_address(current);
    }
    if (current == NULL) {
        return;
    }
    if (previous == NULL) {
        *head_ptr = *get_next_pointer_address(current);
    } else {
        *get_next_pointer_address(previous) = *get_next_pointer_address(current);
    }
    free(current);
}
void printList(void *head) {
    void *current = head;
    while (current != NULL) {
        printf("%d ", *get_data_pointer_address(current));
        current = *get_next_pointer_address(current);
    }
    printf("\n");
}
void freeList(void **head_ptr) {
    void *current = *head_ptr;
    void *next;
    while (current != NULL) {
        next = *get_next_pointer_address(current);
        free(current);
        current = next;
    }
    *head_ptr = NULL;
}
int main() {
    void *head = NULL;
    addNode(&head, 10);
    addNode(&head, 20);
    addNode(&head, 30);
    addNode(&head, 40);
    printList(head);
    deleteNode(&head, 20);
    printList(head);
    deleteNode(&head, 10);
    printList(head);
    addNode(&head, 50);
    printList(head);
    deleteNode(&head, 40);
    printList(head);
    deleteNode(&head, 100);
    printList(head);
    deleteNode(&head, 30);
    printList(head);
    deleteNode(&head, 50);
    printList(head);
    addNode(&head, 1);
    addNode(&head, 2);
    addNode(&head, 3);
    printList(head);
    freeList(&head);
    printList(head);
    return 0;
}