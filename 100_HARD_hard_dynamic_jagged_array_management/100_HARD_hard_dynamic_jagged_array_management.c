#include <stdio.h>
#include <stdlib.h>
int main() {
    int **sets = NULL;
    int *set_counts = NULL;
    int num_sets = 0;
    sets = (int **)realloc(sets, (num_sets + 1) * sizeof(int *));
    set_counts = (int *)realloc(set_counts, (num_sets + 1) * sizeof(int));
    sets[num_sets] = NULL;
    set_counts[num_sets] = 0;
    num_sets++;
    sets = (int **)realloc(sets, (num_sets + 1) * sizeof(int *));
    set_counts = (int *)realloc(set_counts, (num_sets + 1) * sizeof(int));
    sets[num_sets] = NULL;
    set_counts[num_sets] = 0;
    num_sets++;
    sets = (int **)realloc(sets, (num_sets + 1) * sizeof(int *));
    set_counts = (int *)realloc(set_counts, (num_sets + 1) * sizeof(int));
    sets[num_sets] = NULL;
    set_counts[num_sets] = 0;
    num_sets++;
    int set_idx = 0;
    int value = 10;
    sets[set_idx] = (int *)realloc(sets[set_idx], (set_counts[set_idx] + 1) * sizeof(int));
    sets[set_idx][set_counts[set_idx]] = value;
    set_counts[set_idx]++;
    value = 20;
    sets[set_idx] = (int *)realloc(sets[set_idx], (set_counts[set_idx] + 1) * sizeof(int));
    sets[set_idx][set_counts[set_idx]] = value;
    set_counts[set_idx]++;
    set_idx = 1;
    value = 30;
    sets[set_idx] = (int *)realloc(sets[set_idx], (set_counts[set_idx] + 1) * sizeof(int));
    sets[set_idx][set_counts[set_idx]] = value;
    set_counts[set_idx]++;
    value = 40;
    sets[set_idx] = (int *)realloc(sets[set_idx], (set_counts[set_idx] + 1) * sizeof(int));
    sets[set_idx][set_counts[set_idx]] = value;
    set_counts[set_idx]++;
    value = 50;
    sets[set_idx] = (int *)realloc(sets[set_idx], (set_counts[set_idx] + 1) * sizeof(int));
    sets[set_idx][set_counts[set_idx]] = value;
    set_counts[set_idx]++;
    set_idx = 2;
    value = 60;
    sets[set_idx] = (int *)realloc(sets[set_idx], (set_counts[set_idx] + 1) * sizeof(int));
    sets[set_idx][set_counts[set_idx]] = value;
    set_counts[set_idx]++;
    printf("--- Initial Sets ---\n");
    for (int i = 0; i < num_sets; i++) {
        printf("Set %d (size %d): [", i, set_counts[i]);
        for (int j = 0; j < set_counts[i]; j++) {
            printf("%d%s", sets[i][j], (j == set_counts[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("\n");
    set_idx = 0;
    int element_to_remove_val = 20;
    int element_found_idx = -1;
    for (int j = 0; j < set_counts[set_idx]; j++) {
        if (sets[set_idx][j] == element_to_remove_val) {
            element_found_idx = j;
            break;
        }
    }
    if (element_found_idx != -1) {
        for (int j = element_found_idx; j < set_counts[set_idx] - 1; j++) {
            sets[set_idx][j] = sets[set_idx][j+1];
        }
        set_counts[set_idx]--;
        if (set_counts[set_idx] == 0) {
            free(sets[set_idx]);
            sets[set_idx] = NULL;
        } else {
            sets[set_idx] = (int *)realloc(sets[set_idx], set_counts[set_idx] * sizeof(int));
        }
    }
    printf("--- Sets After Removing 20 from Set 0 ---\n");
    for (int i = 0; i < num_sets; i++) {
        printf("Set %d (size %d): [", i, set_counts[i]);
        for (int j = 0; j < set_counts[i]; j++) {
            printf("%d%s", sets[i][j], (j == set_counts[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("\n");
    int set_to_remove_idx = 1;
    if (set_to_remove_idx >= 0 && set_to_remove_idx < num_sets) {
        free(sets[set_to_remove_idx]);
        for (int i = set_to_remove_idx; i < num_sets - 1; i++) {
            sets[i] = sets[i+1];
            set_counts[i] = set_counts[i+1];
        }
        num_sets--;
        if (num_sets == 0) {
            free(sets);
            sets = NULL;
            free(set_counts);
            set_counts = NULL;
        } else {
            sets = (int **)realloc(sets, num_sets * sizeof(int *));
            set_counts = (int *)realloc(set_counts, num_sets * sizeof(int));
        }
    }
    printf("--- Sets After Removing Set 1 ---\n");
    for (int i = 0; i < num_sets; i++) {
        printf("Set %d (size %d): [", i, set_counts[i]);
        for (int j = 0; j < set_counts[i]; j++) {
            printf("%d%s", sets[i][j], (j == set_counts[i] - 1) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("\n");
    for (int i = 0; i < num_sets; i++) {
        free(sets[i]);
    }
    free(sets);
    free(set_counts);
    return 0;
}