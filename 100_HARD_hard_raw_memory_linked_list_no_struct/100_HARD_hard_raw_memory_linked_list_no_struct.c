#include <stdio.h>
#include <stdlib.h>
void* createNode(int value, void* next_node) {
    void* node_ptr = malloc(sizeof(int) + sizeof(void*));
    if (node_ptr == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    *(int*)node_ptr = value;
    *(void**)((char*)node_ptr + sizeof(int)) = next_node;
    return node_ptr;
}
void insertAtHead(void** head_ptr_to_ptr, int value) {
    void* new_node = createNode(value, *head_ptr_to_ptr);
    *head_ptr_to_ptr = new_node;
}
void printList(void* head) {
    void* current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", *(int*)current);
        current = *(void**)((char*)current + sizeof(int));
    }
    printf("\n");
}
void freeList(void* head) {
    void* current = head;
    while (current != NULL) {
        void* next = *(void**)((char*)current + sizeof(int));
        free(current);
        current = next;
    }
}
int main() {
    void* head = NULL;
    insertAtHead(&head, 10);
    insertAtHead(&head, 20);
    insertAtHead(&head, 30);
    insertAtHead(&head, 40);
    insertAtHead(&head, 50);
    printList(head);
    freeList(head);
    head = NULL;
    insertAtHead(&head, 5);
    insertAtHead(&head, 15);
    printList(head);
    freeList(head);
    return 0;
}