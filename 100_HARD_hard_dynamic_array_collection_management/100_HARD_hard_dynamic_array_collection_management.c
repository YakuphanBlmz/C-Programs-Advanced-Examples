#include <stdio.h>
#include <stdlib.h>
int main() {
    int** collection = NULL;
    int capacity = 0;
    int count = 0;
    const int INITIAL_CAPACITY = 2;
    const int SHRINK_THRESHOLD_DENOMINATOR = 4;
    collection = (int**)malloc(INITIAL_CAPACITY * sizeof(int*));
    if (collection == NULL) {
        return 1;
    }
    capacity = INITIAL_CAPACITY;
    for (int i = 0; i < capacity; i++) {
        collection[i] = NULL;
    }
    int new_array_size_0 = 5;
    if (count == capacity) {
        int new_capacity = capacity * 2;
        int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
        if (temp_collection == NULL) {
            for (int i = 0; i < count; i++) free(collection[i]);
            free(collection);
            return 1;
        }
        collection = temp_collection;
        for (int i = capacity; i < new_capacity; i++) {
            collection[i] = NULL;
        }
        capacity = new_capacity;
    }
    collection[count] = (int*)malloc(new_array_size_0 * sizeof(int));
    if (collection[count] == NULL) {
        for (int i = 0; i < count; i++) free(collection[i]);
        free(collection);
        return 1;
    }
    for (int j = 0; j < new_array_size_0; j++) {
        collection[count][j] = j + (count * 100);
    }
    count++;
    int new_array_size_1 = 3;
    if (count == capacity) {
        int new_capacity = capacity * 2;
        int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
        if (temp_collection == NULL) {
            for (int i = 0; i < count; i++) free(collection[i]);
            free(collection);
            return 1;
        }
        collection = temp_collection;
        for (int i = capacity; i < new_capacity; i++) {
            collection[i] = NULL;
        }
        capacity = new_capacity;
    }
    collection[count] = (int*)malloc(new_array_size_1 * sizeof(int));
    if (collection[count] == NULL) {
        for (int i = 0; i < count; i++) free(collection[i]);
        free(collection);
        return 1;
    }
    for (int j = 0; j < new_array_size_1; j++) {
        collection[count][j] = j + (count * 100);
    }
    count++;
    int new_array_size_2 = 7;
    if (count == capacity) {
        int new_capacity = capacity * 2;
        int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
        if (temp_collection == NULL) {
            for (int i = 0; i < count; i++) free(collection[i]);
            free(collection);
            return 1;
        }
        collection = temp_collection;
        for (int i = capacity; i < new_capacity; i++) {
            collection[i] = NULL;
        }
        capacity = new_capacity;
    }
    collection[count] = (int*)malloc(new_array_size_2 * sizeof(int));
    if (collection[count] == NULL) {
        for (int i = 0; i < count; i++) free(collection[i]);
        free(collection);
        return 1;
    }
    for (int j = 0; j < new_array_size_2; j++) {
        collection[count][j] = j + (count * 100);
    }
    count++;
    int resize_index = 0;
    int new_target_size = 8;
    if (resize_index >= 0 && resize_index < count) {
        int* temp_array = (int*)realloc(collection[resize_index], new_target_size * sizeof(int));
        if (temp_array == NULL) {
            for (int i = 0; i < count; i++) free(collection[i]);
            free(collection);
            return 1;
        }
        collection[resize_index] = temp_array;
    }
    int remove_index = 1;
    if (remove_index >= 0 && remove_index < count) {
        free(collection[remove_index]);
        for (int i = remove_index; i < count - 1; i++) {
            collection[i] = collection[i+1];
        }
        count--;
        collection[count] = NULL;
        if (capacity > INITIAL_CAPACITY && count < capacity / SHRINK_THRESHOLD_DENOMINATOR) {
            int new_capacity = capacity / 2;
            int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
            if (temp_collection == NULL) {
                for (int i = 0; i < count; i++) free(collection[i]);
                free(collection);
                return 1;
            }
            collection = temp_collection;
            capacity = new_capacity;
        }
    }
    int new_array_size_3 = 4;
    if (count == capacity) {
        int new_capacity = capacity * 2;
        int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
        if (temp_collection == NULL) {
            for (int i = 0; i < count; i++) free(collection[i]);
            free(collection);
            return 1;
        }
        collection = temp_collection;
        for (int i = capacity; i < new_capacity; i++) {
            collection[i] = NULL;
        }
        capacity = new_capacity;
    }
    collection[count] = (int*)malloc(new_array_size_3 * sizeof(int));
    if (collection[count] == NULL) {
        for (int i = 0; i < count; i++) free(collection[i]);
        free(collection);
        return 1;
    }
    for (int j = 0; j < new_array_size_3; j++) {
        collection[count][j] = j + (count * 100);
    }
    count++;
    remove_index = 0;
    if (remove_index >= 0 && remove_index < count) {
        free(collection[remove_index]);
        for (int i = remove_index; i < count - 1; i++) {
            collection[i] = collection[i+1];
        }
        count--;
        collection[count] = NULL;
        if (capacity > INITIAL_CAPACITY && count < capacity / SHRINK_THRESHOLD_DENOMINATOR) {
            int new_capacity = capacity / 2;
            int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
            if (temp_collection == NULL) {
                for (int i = 0; i < count; i++) free(collection[i]);
                free(collection);
                return 1;
            }
            collection = temp_collection;
            capacity = new_capacity;
        }
    }
    remove_index = 0;
    if (remove_index >= 0 && remove_index < count) {
        free(collection[remove_index]);
        for (int i = remove_index; i < count - 1; i++) {
            collection[i] = collection[i+1];
        }
        count--;
        collection[count] = NULL;
        if (capacity > INITIAL_CAPACITY && count < capacity / SHRINK_THRESHOLD_DENOMINATOR) {
            int new_capacity = capacity / 2;
            int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
            if (temp_collection == NULL) {
                for (int i = 0; i < count; i++) free(collection[i]);
                free(collection);
                return 1;
            }
            collection = temp_collection;
            capacity = new_capacity;
        }
    }
    remove_index = 0;
    if (remove_index >= 0 && remove_index < count) {
        free(collection[remove_index]);
        count--;
        collection[count] = NULL;
        if (capacity > INITIAL_CAPACITY && count < capacity / SHRINK_THRESHOLD_DENOMINATOR) {
            int new_capacity = capacity / 2;
            int** temp_collection = (int**)realloc(collection, new_capacity * sizeof(int*));
            if (temp_collection == NULL) {
                for (int i = 0; i < count; i++) free(collection[i]);
                free(collection);
                return 1;
            }
            collection = temp_collection;
            capacity = new_capacity;
        }
    }
    for (int i = 0; i < count; i++) {
        free(collection[i]);
        collection[i] = NULL;
    }
    free(collection);
    collection = NULL;
    count = 0;
    capacity = 0;
    return 0;
}