#include <stdio.h>
#include <stdlib.h>
void* createNode(int value, void* next) {
    void* newNode = malloc(sizeof(int) + sizeof(void*));
    if (newNode == NULL) {
        return NULL;
    }
    *(int*)newNode = value;
    *(void**)((char*)newNode + sizeof(int)) = next;
    return newNode;
}
void* addNode(void* head, int value) {
    void* newNode = createNode(value, NULL);
    if (newNode == NULL) {
        return head;
    }
    if (head == NULL) {
        return newNode;
    }
    void* current = head;
    while (*(void**)((char*)current + sizeof(int)) != NULL) {
        current = *(void**)((char*)current + sizeof(int));
    }
    *(void**)((char*)current + sizeof(int)) = newNode;
    return head;
}
void* deleteNodeAt(void* head, int position) {
    if (head == NULL) {
        return NULL;
    }
    void* current = head;
    void* prev = NULL;
    int count = 0;
    if (position == 0) {
        void* newHead = *(void**)((char*)head + sizeof(int));
        free(head);
        return newHead;
    }
    while (current != NULL && count < position) {
        prev = current;
        current = *(void**)((char*)current + sizeof(int));
        count++;
    }
    if (current == NULL) {
        return head;
    }
    *(void**)((char*)prev + sizeof(int)) = *(void**)((char*)current + sizeof(int));
    free(current);
    return head;
}
void printList(void* head) {
    void* current = head;
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
    head = addNode(head, 10);
    head = addNode(head, 20);
    head = addNode(head, 30);
    head = addNode(head, 40);
    head = addNode(head, 50);
    printf("Original list: ");
    printList(head);
    head = deleteNodeAt(head, 0);
    printf("After deleting at position 0: ");
    printList(head);
    head = deleteNodeAt(head, 2);
    printf("After deleting at position 2: ");
    printList(head);
    head = deleteNodeAt(head, 2);
    printf("After deleting at position 2 (now end): ");
    printList(head);
    head = addNode(head, 60);
    printf("After adding 60: ");
    printList(head);
    freeList(head);
    return 0;
}