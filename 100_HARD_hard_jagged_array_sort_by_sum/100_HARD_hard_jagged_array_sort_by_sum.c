#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(NULL));
    int num_rows = 5 + rand() % 6; 
    int **master_array = (int **)malloc(num_rows * sizeof(int *));
    for (int i = 0; i < num_rows; i++) {
        int row_data_size = 5 + rand() % 11; 
        int *current_row = (int *)malloc((row_data_size + 1) * sizeof(int));
        current_row[0] = row_data_size;
        for (int j = 0; j < row_data_size; j++) {
            current_row[j + 1] = rand() % 100;
        }
        master_array[i] = current_row;
    }
    printf("Initial Arrays:\n");
    for (int i = 0; i < num_rows; i++) {
        int *row = master_array[i];
        int data_size = row[0];
        printf("Row %d (Size: %d, Sum: ", i, data_size);
        long long current_sum = 0;
        for (int j = 0; j < data_size; j++) {
            current_sum += row[j + 1];
        }
        printf("%lld): ", current_sum);
        for (int j = 0; j < data_size; j++) {
            printf("%d ", row[j + 1]);
        }
        printf("\n");
    }
    for (int i = 0; i < num_rows - 1; i++) {
        for (int j = 0; j < num_rows - i - 1; j++) {
            int *row_a = master_array[j];
            int data_size_a = row_a[0];
            long long sum_a = 0;
            for (int k = 0; k < data_size_a; k++) {
                sum_a += row_a[k + 1];
            }
            int *row_b = master_array[j + 1];
            int data_size_b = row_b[0];
            long long sum_b = 0;
            for (int k = 0; k < data_size_b; k++) {
                sum_b += row_b[k + 1];
            }
            if (sum_a > sum_b) {
                int *temp = master_array[j];
                master_array[j] = master_array[j + 1];
                master_array[j + 1] = temp;
            }
        }
    }
    printf("\nSorted Arrays by Sum (Ascending):\n");
    for (int i = 0; i < num_rows; i++) {
        int *row = master_array[i];
        int data_size = row[0];
        printf("Row %d (Size: %d, Sum: ", i, data_size);
        long long current_sum = 0;
        for (int j = 0; j < data_size; j++) {
            current_sum += row[j + 1];
        }
        printf("%lld): ", current_sum);
        for (int j = 0; j < data_size; j++) {
            printf("%d ", row[j + 1]);
        }
        printf("\n");
    }
    for (int i = 0; i < num_rows; i++) {
        free(master_array[i]);
    }
    free(master_array);
    return 0;
}