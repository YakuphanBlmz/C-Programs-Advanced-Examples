#include <stdio.h>
#include <stdlib.h>
#define INNER_NODE_DATA_OFFSET 0
#define INNER_NODE_NEXT_OFFSET sizeof(int)
#define INNER_NODE_SIZE (sizeof(int) + sizeof(char*))
#define OUTER_NODE_INNER_HEAD_OFFSET 0
#define OUTER_NODE_NEXT_OFFSET sizeof(char*)
#define OUTER_NODE_SIZE (sizeof(char*) + sizeof(char*))
void append_to_sequence_list(char** head, int value);
void append_to_collection_list(char** head, char* sequence_list_head);
void print_collection_list(char* collection_list_head);
void free_all_memory(char* collection_list_head);
void free_sequence_list(char* sequence_list_head);
int main() {
    char* collection_list_head = NULL;
    char* sequence1 = NULL;
    append_to_sequence_list(&sequence1, 10);
    append_to_sequence_list(&sequence1, 20);
    append_to_sequence_list(&sequence1, 30);
    append_to_collection_list(&collection_list_head, sequence1);
    char* sequence2 = NULL;
    append_to_sequence_list(&sequence2, 1);
    append_to_sequence_list(&sequence2, 2);
    append_to_collection_list(&collection_list_head, sequence2);
    char* sequence3 = NULL;
    append_to_sequence_list(&sequence3, 100);
    append_to_collection_list(&collection_list_head, sequence3);
    printf("Collection List Contents:\n");
    print_collection_list(collection_list_head);
    free_all_memory(collection_list_head);
    return 0;
}
void append_to_sequence_list(char** head_ptr, int value) {
    char* new_node = (char*)malloc(INNER_NODE_SIZE);
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for inner node\n");
        exit(EXIT_FAILURE);
    }
    *(int*)(new_node + INNER_NODE_DATA_OFFSET) = value;
    *(char**)(new_node + INNER_NODE_NEXT_OFFSET) = NULL;
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        char* current = *head_ptr;
        while (*(char**)(current + INNER_NODE_NEXT_OFFSET) != NULL) {
            current = *(char**)(current + INNER_NODE_NEXT_OFFSET);
        }
        *(char**)(current + INNER_NODE_NEXT_OFFSET) = new_node;
    }
}
void append_to_collection_list(char** head_ptr, char* sequence_list_head) {
    char* new_node = (char*)malloc(OUTER_NODE_SIZE);
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed for outer node\n");
        exit(EXIT_FAILURE);
    }
    *(char**)(new_node + OUTER_NODE_INNER_HEAD_OFFSET) = sequence_list_head;
    *(char**)(new_node + OUTER_NODE_NEXT_OFFSET) = NULL;
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        char* current = *head_ptr;
        while (*(char**)(current + OUTER_NODE_NEXT_OFFSET) != NULL) {
            current = *(char**)(current + OUTER_NODE_NEXT_OFFSET);
        }
        *(char**)(current + OUTER_NODE_NEXT_OFFSET) = new_node;
    }
}
void print_collection_list(char* collection_list_head) {
    char* current_outer = collection_list_head;
    while (current_outer != NULL) {
        char* current_inner = *(char**)(current_outer + OUTER_NODE_INNER_HEAD_OFFSET);
        while (current_inner != NULL) {
            printf("%d ", *(int*)(current_inner + INNER_NODE_DATA_OFFSET));
            current_inner = *(char**)(current_inner + INNER_NODE_NEXT_OFFSET);
        }
        printf("\n");
        current_outer = *(char**)(current_outer + OUTER_NODE_NEXT_OFFSET);
    }
}
void free_sequence_list(char* sequence_list_head) {
    char* current_inner = sequence_list_head;
    while (current_inner != NULL) {
        char* next_inner = *(char**)(current_inner + INNER_NODE_NEXT_OFFSET);
        free(current_inner);
        current_inner = next_inner;
    }
}
void free_all_memory(char* collection_list_head) {
    char* current_outer = collection_list_head;
    while (current_outer != NULL) {
        char* next_outer = *(char**)(current_outer + OUTER_NODE_NEXT_OFFSET);
        char* inner_list_head_to_free = *(char**)(current_outer + OUTER_NODE_INNER_HEAD_OFFSET);
        free_sequence_list(inner_list_head_to_free);
        free(current_outer);
        current_outer = next_outer;
    }
}