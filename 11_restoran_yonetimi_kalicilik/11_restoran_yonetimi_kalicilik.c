#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define INVENTORY_FILE "inventory.dat"
#define MENU_FILE "menu.dat"

typedef struct {
    char name[MAX_NAME_LEN];
    int stockQuantity;
} Ingredient;

typedef struct {
    int ingredientId; 
    Ingredient* ingredientPtr;
    int quantityNeeded;
} RecipeItem;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    double price;
    RecipeItem* recipe;
    int numRecipeItems;
} MenuItem;

typedef struct {
    Ingredient* inventory;
    int numIngredients;
    int inventoryCapacity;
    MenuItem* menu;
    int numMenuItems;
    int menuCapacity;
} Restaurant;

void initRestaurant(Restaurant* r) {
    r->inventory = NULL;
    r->numIngredients = 0;
    r->inventoryCapacity = 0;
    r->menu = NULL;
    r->numMenuItems = 0;
    r->menuCapacity = 0;
}

void freeRestaurant(Restaurant* r) {
    int i;
    if (r->inventory) {
        free(r->inventory);
    }
    if (r->menu) {
        for (i = 0; i < r->numMenuItems; i++) {
            if (r->menu[i].recipe) {
                free(r->menu[i].recipe);
            }
        }
        free(r->menu);
    }
    initRestaurant(r);
}

Ingredient* findIngredientByName(Restaurant* r, const char* name) {
    int i;
    for (i = 0; i < r->numIngredients; i++) {
        if (strcmp(r->inventory[i].name, name) == 0) {
            return &r->inventory[i];
        }
    }
    return NULL;
}

int findIngredientIdByName(Restaurant* r, const char* name) {
    int i;
    for (i = 0; i < r->numIngredients; i++) {
        if (strcmp(r->inventory[i].name, name) == 0) {
            return i; 
        }
    }
    return -1;
}

Ingredient* findIngredientById(Restaurant* r, int id) {
    if (id >= 0 && id < r->numIngredients) {
        return &r->inventory[id];
    }
    return NULL;
}

void addIngredientToInventory(Restaurant* r, const char* name, int quantity) {
    if (findIngredientByName(r, name) != NULL) {
        printf("Ingredient '%s' already exists. Updating quantity.\n", name);
        findIngredientByName(r, name)->stockQuantity += quantity;
        return;
    }

    if (r->numIngredients == r->inventoryCapacity) {
        r->inventoryCapacity = (r->inventoryCapacity == 0) ? 2 : r->inventoryCapacity * 2;
        r->inventory = (Ingredient*)realloc(r->inventory, r->inventoryCapacity * sizeof(Ingredient));
        if (!r->inventory) {
            perror("Failed to reallocate inventory");
            exit(EXIT_FAILURE);
        }
    }
    strncpy(r->inventory[r->numIngredients].name, name, MAX_NAME_LEN - 1);
    r->inventory[r->numIngredients].name[MAX_NAME_LEN - 1] = '\0';
    r->inventory[r->numIngredients].stockQuantity = quantity;
    r->numIngredients++;
    printf("Added %s to inventory with %d units.\n", name, quantity);
}

void addMenuItemToMenu(Restaurant* r, const char* name, double price, RecipeItem* recipe, int numRecipeItems) {
    int i;
    if (r->numMenuItems == r->menuCapacity) {
        r->menuCapacity = (r->menuCapacity == 0) ? 2 : r->menuCapacity * 2;
        r->menu = (MenuItem*)realloc(r->menu, r->menuCapacity * sizeof(MenuItem));
        if (!r->menu) {
            perror("Failed to reallocate menu");
            exit(EXIT_FAILURE);
        }
    }

    r->menu[r->numMenuItems].id = r->numMenuItems; 
    strncpy(r->menu[r->numMenuItems].name, name, MAX_NAME_LEN - 1);
    r->menu[r->numMenuItems].name[MAX_NAME_LEN - 1] = '\0';
    r->menu[r->numMenuItems].price = price;
    r->menu[r->numMenuItems].numRecipeItems = numRecipeItems;

    r->menu[r->numMenuItems].recipe = (RecipeItem*)malloc(numRecipeItems * sizeof(RecipeItem));
    if (!r->menu[r->numMenuItems].recipe) {
        perror("Failed to allocate recipe items");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < numRecipeItems; i++) {
        r->menu[r->numMenuItems].recipe[i].ingredientPtr = findIngredientByName(r, recipe[i].ingredientPtr->name);
        if (!r->menu[r->numMenuItems].recipe[i].ingredientPtr) {
            fprintf(stderr, "Error: Ingredient '%s' not found for menu item '%s'.\n", recipe[i].ingredientPtr->name, name);
            exit(EXIT_FAILURE);
        }
        r->menu[r->numMenuItems].recipe[i].quantityNeeded = recipe[i].quantityNeeded;
    }
    r->numMenuItems++;
    printf("Added '%s' to menu.\n", name);
}

void printInventory(const Restaurant* r) {
    int i;
    printf("\n--- Current Inventory ---\n");
    if (r->numIngredients == 0) {
        printf("Inventory is empty.\n");
        return;
    }
    for (i = 0; i < r->numIngredients; i++) {
        printf("  %s: %d units\n", r->inventory[i].name, r->inventory[i].stockQuantity);
    }
    printf("--------------------------\n");
}

void printMenu(const Restaurant* r) {
    int i, j;
    printf("\n--- The Gilded Spoon Menu ---\n");
    if (r->numMenuItems == 0) {
        printf("Menu is empty.\n");
        return;
    }
    for (i = 0; i < r->numMenuItems; i++) {
        printf("  %d. %s (%.2f TL)\n", r->menu[i].id + 1, r->menu[i].name, r->menu[i].price);
        printf("     Ingredients:\n");
        for (j = 0; j < r->menu[i].numRecipeItems; j++) {
            printf("       - %s: %d units\n", r->menu[i].recipe[j].ingredientPtr->name, r->menu[i].recipe[j].quantityNeeded);
        }
    }
    printf("----------------------------\n");
}

void saveRestaurantState(const Restaurant* r) {
    FILE* invFile = fopen(INVENTORY_FILE, "wb");
    FILE* menuFile = fopen(MENU_FILE, "wb");
    int i, j;

    if (!invFile || !menuFile) {
        perror("Failed to open files for saving");
        if (invFile) fclose(invFile);
        if (menuFile) fclose(menuFile);
        return;
    }

    fwrite(&r->numIngredients, sizeof(int), 1, invFile);
    fwrite(r->inventory, sizeof(Ingredient), r->numIngredients, invFile);

    fwrite(&r->numMenuItems, sizeof(int), 1, menuFile);
    for (i = 0; i < r->numMenuItems; i++) {
        fwrite(&r->menu[i].id, sizeof(int), 1, menuFile);
        fwrite(r->menu[i].name, sizeof(char), MAX_NAME_LEN, menuFile);
        fwrite(&r->menu[i].price, sizeof(double), 1, menuFile);
        fwrite(&r->menu[i].numRecipeItems, sizeof(int), 1, menuFile);

        for (j = 0; j < r->menu[i].numRecipeItems; j++) {
            r->menu[i].recipe[j].ingredientId = findIngredientIdByName(r, r->menu[i].recipe[j].ingredientPtr->name);
            fwrite(&r->menu[i].recipe[j].ingredientId, sizeof(int), 1, menuFile);
            fwrite(&r->menu[i].recipe[j].quantityNeeded, sizeof(int), 1, menuFile);
        }
    }

    fclose(invFile);
    fclose(menuFile);
    printf("Restaurant state saved successfully.\n");
}

void loadRestaurantState(Restaurant* r) {
    FILE* invFile = fopen(INVENTORY_FILE, "rb");
    FILE* menuFile = fopen(MENU_FILE, "rb");
    int i, j;

    if (!invFile || !menuFile) {
        printf("No previous state found. Starting with empty restaurant.\n");
        if (invFile) fclose(invFile);
        if (menuFile) fclose(menuFile);
        return;
    }

    freeRestaurant(r); 

    fread(&r->numIngredients, sizeof(int), 1, invFile);
    if (r->numIngredients > 0) {
        r->inventoryCapacity = r->numIngredients;
        r->inventory = (Ingredient*)malloc(r->inventoryCapacity * sizeof(Ingredient));
        if (!r->inventory) {
            perror("Failed to allocate inventory during load");
            exit(EXIT_FAILURE);
        }
        fread(r->inventory, sizeof(Ingredient), r->numIngredients, invFile);
    }

    fread(&r->numMenuItems, sizeof(int), 1, menuFile);
    if (r->numMenuItems > 0) {
        r->menuCapacity = r->numMenuItems;
        r->menu = (MenuItem*)malloc(r->menuCapacity * sizeof(MenuItem));
        if (!r->menu) {
            perror("Failed to allocate menu during load");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < r->numMenuItems; i++) {
            fread(&r->menu[i].id, sizeof(int), 1, menuFile);
            fread(r->menu[i].name, sizeof(char), MAX_NAME_LEN, menuFile);
            fread(&r->menu[i].price, sizeof(double), 1, menuFile);
            fread(&r->menu[i].numRecipeItems, sizeof(int), 1, menuFile);

            r->menu[i].recipe = (RecipeItem*)malloc(r->menu[i].numRecipeItems * sizeof(RecipeItem));
            if (!r->menu[i].recipe) {
                perror("Failed to allocate recipe items during load");
                exit(EXIT_FAILURE);
            }

            for (j = 0; j < r->menu[i].numRecipeItems; j++) {
                fread(&r->menu[i].recipe[j].ingredientId, sizeof(int), 1, menuFile);
                r->menu[i].recipe[j].ingredientPtr = findIngredientById(r, r->menu[i].recipe[j].ingredientId);
                if (!r->menu[i].recipe[j].ingredientPtr) {
                    fprintf(stderr, "Error: Ingredient with ID %d not found during menu load.\n", r->menu[i].recipe[j].ingredientId);
                    exit(EXIT_FAILURE);
                }
                fread(&r->menu[i].recipe[j].quantityNeeded, sizeof(int), 1, menuFile);
            }
        }
    }

    fclose(invFile);
    fclose(menuFile);
    printf("Restaurant state loaded successfully.\n");
}

int main() {
    Restaurant gildedSpoon;
    initRestaurant(&gildedSpoon);

    printf("Attempting to load restaurant state...\n");
    loadRestaurantState(&gildedSpoon);

    if (gildedSpoon.numIngredients == 0) {
        printf("Initializing default inventory and menu...\n");
        addIngredientToInventory(&gildedSpoon, "Flour", 100);
        addIngredientToInventory(&gildedSpoon, "Eggs", 50);
        addIngredientToInventory(&gildedSpoon, "Milk", 30);
        addIngredientToInventory(&gildedSpoon, "Sugar", 25);
        addIngredientToInventory(&gildedSpoon, "Salt", 10);
        addIngredientToInventory(&gildedSpoon, "Butter", 20);
        addIngredientToInventory(&gildedSpoon, "Chicken", 15);
        addIngredientToInventory(&gildedSpoon, "Rice", 40);
        addIngredientToInventory(&gildedSpoon, "Tomatoes", 35);

        Ingredient* flour = findIngredientByName(&gildedSpoon, "Flour");
        Ingredient* eggs = findIngredientByName(&gildedSpoon, "Eggs");
        Ingredient* milk = findIngredientByName(&gildedSpoon, "Milk");
        Ingredient* sugar = findIngredientByName(&gildedSpoon, "Sugar");
        Ingredient* chicken = findIngredientByName(&gildedSpoon, "Chicken");
        Ingredient* rice = findIngredientByName(&gildedSpoon, "Rice");
        Ingredient* tomatoes = findIngredientByName(&gildedSpoon, "Tomatoes");

        RecipeItem pancakeRecipe[] = {
            {.ingredientPtr = flour, .quantityNeeded = 5},
            {.ingredientPtr = eggs, .quantityNeeded = 2},
            {.ingredientPtr = milk, .quantityNeeded = 1}
        };
        addMenuItemToMenu(&gildedSpoon, "Pancakes", 15.50, pancakeRecipe, 3);

        RecipeItem chickenRiceRecipe[] = {
            {.ingredientPtr = chicken, .quantityNeeded = 1},
            {.ingredientPtr = rice, .quantityNeeded = 2},
            {.ingredientPtr = tomatoes, .quantityNeeded = 3}
        };
        addMenuItemToMenu(&gildedSpoon, "Chicken with Rice", 45.00, chickenRiceRecipe, 3);

        RecipeItem omeletteRecipe[] = {
            {.ingredientPtr = eggs, .quantityNeeded = 3},
            {.ingredientPtr = milk, .quantityNeeded = 1}
        };
        addMenuItemToMenu(&gildedSpoon, "Omelette", 20.00, omeletteRecipe, 2);
    }

    printInventory(&gildedSpoon);
    printMenu(&gildedSpoon);

    printf("\n--- Simulating some changes ---\n");
    addIngredientToInventory(&gildedSpoon, "Olive Oil", 10); 
    addIngredientToInventory(&gildedSpoon, "Flour", 20);      

    Ingredient* oliveOil = findIngredientByName(&gildedSpoon, "Olive Oil");
    Ingredient* salt = findIngredientByName(&gildedSpoon, "Salt");

    RecipeItem saladRecipe[] = {
        {.ingredientPtr = tomatoes, .quantityNeeded = 4},
        {.ingredientPtr = oliveOil, .quantityNeeded = 1},
        {.ingredientPtr = salt, .quantityNeeded = 1}
    };
    addMenuItemToMenu(&gildedSpoon, "Fresh Garden Salad", 28.75, saladRecipe, 3);

    printInventory(&gildedSpoon);
    printMenu(&gildedSpoon);

    saveRestaurantState(&gildedSpoon);
    freeRestaurant(&gildedSpoon);

    printf("\nRestaurant closed. Reopening to check persistence...\n");
    initRestaurant(&gildedSpoon);
    loadRestaurantState(&gildedSpoon);
    printInventory(&gildedSpoon);
    printMenu(&gildedSpoon);
    freeRestaurant(&gildedSpoon);

    return 0;
}