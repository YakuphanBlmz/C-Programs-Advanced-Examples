#include <stdio.h>
#include <stdlib.h>
int main() {
    void *head = NULL;
    void *current = NULL;
    int values[] = {10, 20, 30, 40, 50, 60, 70};
    int num_elements = sizeof(values) / sizeof(values[0]);
    int i;
    for (i = 0; i < num_elements; i++) {
        void *newNode = malloc(sizeof(int) + sizeof(void *));
        if (newNode == NULL) {
            return 1;
        }
        *(int *)newNode = values[i];
        *((void **)((char *)newNode + sizeof(int))) = NULL;
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            *((void **)((char *)current + sizeof(int))) = newNode;
            current = newNode;
        }
    }
    int sum = 0;
    current = head;
    while (current != NULL) {
        sum += *(int *)current;
        current = *((void **)((char *)current + sizeof(int)));
    }
    printf("Sum of list elements: %d\n", sum);
    current = head;
    while (current != NULL) {
        void *nextNode = *((void **)((char *)current + sizeof(int)));
        free(current);
        current = nextNode;
    }
    return 0;
}