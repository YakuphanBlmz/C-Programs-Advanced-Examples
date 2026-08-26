#include <stdio.h>
#include <stdlib.h>
int main() {
    int **ledger = NULL;
    int *account_sizes = NULL;
    int *account_capacities = NULL;
    int num_accounts = 0;
    int ledger_capacity = 0;
    printf("Initializing ledger and adding 3 accounts...\n");
    for (int i = 0; i < 3; i++) {
        if (num_accounts >= ledger_capacity) {
            ledger_capacity = (ledger_capacity == 0) ? 2 : ledger_capacity * 2;
            int **temp_ledger = (int**)realloc(ledger, ledger_capacity * sizeof(int*));
            int *temp_sizes = (int*)realloc(account_sizes, ledger_capacity * sizeof(int));
            int *temp_caps = (int*)realloc(account_capacities, ledger_capacity * sizeof(int));
            if (!temp_ledger || !temp_sizes || !temp_caps) {
                fprintf(stderr, "Memory reallocation failed for ledger structure\n");
                exit(EXIT_FAILURE);
            }
            ledger = temp_ledger;
            account_sizes = temp_sizes;
            account_capacities = temp_caps;
        }
        ledger[num_accounts] = NULL;
        account_sizes[num_accounts] = 0;
        account_capacities[num_accounts] = 0;
        num_accounts++;
    }
    printf("Adding transactions to account 0 and 1...\n");
    int account_idx_0 = 0;
    int transaction_values_0[] = {100, 200, 300};
    for (int i = 0; i < 3; i++) {
        if (account_sizes[account_idx_0] >= account_capacities[account_idx_0]) {
            account_capacities[account_idx_0] = (account_capacities[account_idx_0] == 0) ? 4 : account_capacities[account_idx_0] * 2;
            int *temp = (int*)realloc(ledger[account_idx_0], account_capacities[account_idx_0] * sizeof(int));
            if (!temp) {
                fprintf(stderr, "Memory reallocation failed for account %d transactions\n", account_idx_0);
                exit(EXIT_FAILURE);
            }
            ledger[account_idx_0] = temp;
        }
        ledger[account_idx_0][account_sizes[account_idx_0]++] = transaction_values_0[i];
    }
    int account_idx_1 = 1;
    int transaction_values_1[] = {50, 75};
    for (int i = 0; i < 2; i++) {
        if (account_sizes[account_idx_1] >= account_capacities[account_idx_1]) {
            account_capacities[account_idx_1] = (account_capacities[account_idx_1] == 0) ? 4 : account_capacities[account_idx_1] * 2;
            int *temp = (int*)realloc(ledger[account_idx_1], account_capacities[account_idx_1] * sizeof(int));
            if (!temp) {
                fprintf(stderr, "Memory reallocation failed for account %d transactions\n", account_idx_1);
                exit(EXIT_FAILURE);
            }
            ledger[account_idx_1] = temp;
        }
        ledger[account_idx_1][account_sizes[account_idx_1]++] = transaction_values_1[i];
    }
    printf("\n--- Current Ledger State ---\n");
    for (int i = 0; i < num_accounts; i++) {
        printf("Account %d (Size: %d, Capacity: %d): ", i, account_sizes[i], account_capacities[i]);
        if (account_sizes[i] == 0) {
            printf("[Empty]\n");
        } else {
            for (int j = 0; j < account_sizes[i]; j++) {
                printf("%d ", ledger[i][j]);
            }
            printf("\n");
        }
    }
    printf("Total Accounts: %d, Ledger Capacity: %d\n", num_accounts, ledger_capacity);
    printf("\nRemoving transaction at index 1 from account 0...\n");
    int target_account_idx_remove_tx = 0;
    int target_transaction_idx = 1;
    if (target_account_idx_remove_tx < num_accounts && account_sizes[target_account_idx_remove_tx] > 0 && target_transaction_idx < account_sizes[target_account_idx_remove_tx]) {
        for (int j = target_transaction_idx; j < account_sizes[target_account_idx_remove_tx] - 1; j++) {
            ledger[target_account_idx_remove_tx][j] = ledger[target_account_idx_remove_tx][j + 1];
        }
        account_sizes[target_account_idx_remove_tx]--;
        if (account_capacities[target_account_idx_remove_tx] > 0 && account_sizes[target_account_idx_remove_tx] * 4 < account_capacities[target_account_idx_remove_tx]) {
            account_capacities[target_account_idx_remove_tx] /= 2;
            if (account_capacities[target_account_idx_remove_tx] == 0) {
                free(ledger[target_account_idx_remove_tx]);
                ledger[target_account_idx_remove_tx] = NULL;
            } else {
                int *temp = (int*)realloc(ledger[target_account_idx_remove_tx], account_capacities[target_account_idx_remove_tx] * sizeof(int));
                if (!temp) {
                    fprintf(stderr, "Memory realloc shrink failed for account %d transactions\n", target_account_idx_remove_tx);
                    exit(EXIT_FAILURE);
                }
                ledger[target_account_idx_remove_tx] = temp;
            }
        }
    } else {
        printf("Invalid account or transaction index for removal.\n");
    }
    printf("\n--- Ledger State After Transaction Removal ---\n");
    for (int i = 0; i < num_accounts; i++) {
        printf("Account %d (Size: %d, Capacity: %d): ", i, account_sizes[i], account_capacities[i]);
        if (account_sizes[i] == 0) {
            printf("[Empty]\n");
        } else {
            for (int j = 0; j < account_sizes[i]; j++) {
                printf("%d ", ledger[i][j]);
            }
            printf("\n");
        }
    }
    printf("Total Accounts: %d, Ledger Capacity: %d\n", num_accounts, ledger_capacity);
    printf("\nDeleting account at index 1...\n");
    int target_account_idx_delete_acc = 1;
    if (target_account_idx_delete_acc < num_accounts) {
        free(ledger[target_account_idx_delete_acc]);
        for (int i = target_account_idx_delete_acc; i < num_accounts - 1; i++) {
            ledger[i] = ledger[i + 1];
            account_sizes[i] = account_sizes[i + 1];
            account_capacities[i] = account_capacities[i + 1];
        }
        num_accounts--;
        if (ledger_capacity > 0 && num_accounts * 4 < ledger_capacity) {
            ledger_capacity /= 2;
            if (ledger_capacity == 0) {
                free(ledger);
                ledger = NULL;
                free(account_sizes);
                account_sizes = NULL;
                free(account_capacities);
                account_capacities = NULL;
            } else {
                int **temp_ledger = (int**)realloc(ledger, ledger_capacity * sizeof(int*));
                int *temp_sizes = (int*)realloc(account_sizes, ledger_capacity * sizeof(int));
                int *temp_caps = (int*)realloc(account_capacities, ledger_capacity * sizeof(int));
                if (!temp_ledger || !temp_sizes || !temp_caps) {
                    fprintf(stderr, "Memory realloc shrink failed for ledger structure\n");
                    exit(EXIT_FAILURE);
                }
                ledger = temp_ledger;
                account_sizes = temp_sizes;
                account_capacities = temp_caps;
            }
        }
    } else {
        printf("Invalid account index for deletion.\n");
    }
    printf("\n--- Ledger State After Account Deletion ---\n");
    for (int i = 0; i < num_accounts; i++) {
        printf("Account %d (Size: %d, Capacity: %d): ", i, account_sizes[i], account_capacities[i]);
        if (account_sizes[i] == 0) {
            printf("[Empty]\n");
        } else {
            for (int j = 0; j < account_sizes[i]; j++) {
                printf("%d ", ledger[i][j]);
            }
            printf("\n");
        }
    }
    printf("Total Accounts: %d, Ledger Capacity: %d\n", num_accounts, ledger_capacity);
    printf("\nCleaning up all memory...\n");
    for (int i = 0; i < num_accounts; i++) {
        free(ledger[i]);
    }
    free(ledger);
    free(account_sizes);
    free(account_capacities);
    printf("Memory cleanup complete.\n");
    return 0;
}