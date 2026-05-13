#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 5
#define NAME_LEN 50
typedef struct {
    int id;
    char name[NAME_LEN];
    int quantity;
} Item;
Item inventory[MAX_ITEMS];
int itemCount = 0;
void addItem();
void updateItemQuantity();
void displayInventory();
int findItemIndex(int id);
int main() {
    int choice;
    do {
        printf("\n--- Inventory Management System ---\n");
        printf("1. Add Item\n");
        printf("2. Update Item Quantity\n");
        printf("3. Display Inventory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                updateItemQuantity();
                break;
            case 3:
                displayInventory();
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory is full. Cannot add more items.\n");
        return;
    }
    Item newItem;
    int id;
    printf("Enter Item ID: ");
    scanf("%d", &id);
    if (findItemIndex(id) != -1) {
        printf("An item with this ID already exists. Please use a unique ID.\n");
        return;
    }
    newItem.id = id;
    printf("Enter Item Name: ");
    scanf(" %49[^
]", newItem.name);
    printf("Enter Item Quantity: ");
    scanf("%d", &newItem.quantity);
    inventory[itemCount] = newItem;
    itemCount++;
    printf("Item added successfully.\n");
}
void updateItemQuantity() {
    int id;
    int newQuantity;
    printf("Enter Item ID to update: ");
    scanf("%d", &id);
    int index = findItemIndex(id);
    if (index == -1) {
        printf("Item with ID %d not found.\n", id);
        return;
    }
    printf("Enter new quantity for %s (current: %d): ", inventory[index].name, inventory[index].quantity);
    scanf("%d", &newQuantity);
    if (newQuantity < 0) {
        printf("Quantity cannot be negative.\n");
        return;
    }
    inventory[index].quantity = newQuantity;
    printf("Quantity updated successfully.\n");
}
void displayInventory() {
    if (itemCount == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    printf("\n--- Current Inventory ---\n");
    printf("%-5s %-20s %-10s\n", "ID", "Name", "Quantity");
    printf("------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%-5d %-20s %-10d\n", inventory[i].id, inventory[i].name, inventory[i].quantity);
    }
    printf("------------------------------------\n");
}
int findItemIndex(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            return i;
        }
    }
    return -1;
}