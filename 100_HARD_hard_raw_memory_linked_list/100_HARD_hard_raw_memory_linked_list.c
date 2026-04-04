#include <stdio.h>
#include <stdlib.h>
void *createNode(int value) {
    void *newNode = malloc(sizeof(int) + sizeof(void *));
    if (newNode == NULL) {
        perror("Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    *(int *)newNode = value;
    *(void **)((char *)newNode + sizeof(int)) = NULL;
    return newNode;
}
void insertNode(void **head, int value) {
    void *newNode = createNode(value);
    void **newNodeNextPtr = (void **)((char *)newNode + sizeof(int));
    *newNodeNextPtr = *head;
    *head = newNode;
}
void printList(void *head) {
    printf("List elements: ");
    void *current = head;
    while (current != NULL) {
        printf("%d ", *(int *)current);
        current = *(void **)((char *)current + sizeof(int));
    }
    printf("\n");
}
void freeList(void **head) {
    void *current = *head;
    void *next;
    while (current != NULL) {
        void **currentNextPtr = (void **)((char *)current + sizeof(int));
        next = *currentNextPtr;
        free(current);
        current = next;
    }
    *head = NULL;
    printf("List memory freed.\n");
}
int main() {
    void *head = NULL;
    insertNode(&head, 10);
    insertNode(&head, 20);
    insertNode(&head, 30);
    insertNode(&head, 40);
    insertNode(&head, 50);
    printList(head);
    freeList(&head);
    printList(head);
    return 0;
}