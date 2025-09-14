#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for inventory items
typedef struct {
    int id;
    char name[50];
    int quantity;
    float price;
} Item;

// Function to add an item
void addItem() {
    FILE *file = fopen("inventory.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Item item;
    printf("Enter item ID: ");
    if (scanf("%d", &item.id) != 1) {
        printf("Invalid input for ID.\n");
        fclose(file);
        return;
    }
    printf("Enter item name: ");
    scanf(" %49[^\n]", item.name);  // Limit input length
    printf("Enter quantity: ");
    if (scanf("%d", &item.quantity) != 1) {
        printf("Invalid input for quantity.\n");
        fclose(file);
        return;
    }
    printf("Enter price: ");
    if (scanf("%f", &item.price) != 1) {
        printf("Invalid input for price.\n");
        fclose(file);
        return;
    }

    fprintf(file, "%d %s %d %.2f\n", item.id, item.name, item.quantity, item.price);
    fclose(file);
    printf("Item added successfully!\n");
}


// Function to display items
void displayItems() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No items found!\n");
        return;
    }

    Item item;
    int itemsFound = 0;
    printf("\nID\tName\t\tQuantity\tPrice\n");
    printf("---------------------------------------------\n");
    while (fscanf(file, "%d %49s %d %f", &item.id, item.name, &item.quantity, &item.price) == 4) {
        printf("%d\t%-15s\t%d\t\t%.2f\n", item.id, item.name, item.quantity, item.price);
        itemsFound++;
    }

    if (itemsFound == 0) {
        printf("No items to display.\n");
    }
    fclose(file);
}



// Function to search for an item by ID
void searchItem() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No items found!\n");
        return;
    }

    int searchId;
    printf("Enter item ID to search: ");
    if (scanf("%d", &searchId) != 1) {
        printf("Invalid input for ID.\n");
        fclose(file);
        return;
    }

    Item item;
    int found = 0;
    while (fscanf(file, "%d %49s %d %f", &item.id, item.name, &item.quantity, &item.price) == 4) {
        if (item.id == searchId) {
            printf("\nItem found:\n");
            printf("ID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\n", item.id, item.name, item.quantity, item.price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item not found!\n");
    }
    fclose(file);
}


// Function to update the quantity of an item
void updateItem() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No items found!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(file);
        return;
    }

    int updateId, newQuantity;
    printf("Enter item ID to update: ");
    if (scanf("%d", &updateId) != 1) {
        printf("Invalid input for ID.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }
    printf("Enter new quantity: ");
    if (scanf("%d", &newQuantity) != 1) {
        printf("Invalid input for quantity.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    Item item;
    int found = 0;
    while (fscanf(file, "%d %49s %d %f", &item.id, item.name, &item.quantity, &item.price) == 4) {
        if (item.id == updateId) {
            item.quantity = newQuantity;
            found = 1;
        }
        fprintf(tempFile, "%d %s %d %.2f\n", item.id, item.name, item.quantity, item.price);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Item updated successfully!\n");
    } else {
        remove("temp.txt");
        printf("Item not found!\n");
    }
}

//Function to delete an item
void deleteItem() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("No items found!\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(file);
        return;
    }

    int deleteId;
    printf("Enter item ID to delete: ");
    if (scanf("%d", &deleteId) != 1) {
        printf("Invalid input for ID.\n");
        fclose(file);
        fclose(tempFile);
        return;
    }

    Item item;
    int found = 0;
    while (fscanf(file, "%d %49s %d %f", &item.id, item.name, &item.quantity, &item.price) == 4) {
        if (item.id == deleteId) {
            found = 1; // Mark as found and skip writing this item to the temp file
            continue;
        }
        fprintf(tempFile, "%d %s %d %.2f\n", item.id, item.name, item.quantity, item.price);
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Item with ID %d deleted successfully!\n", deleteId);
    } else {
        remove("temp.txt");
        printf("Item with ID %d not found!\n", deleteId);
    }
}

// Function to display the menu
void displayMenu() {
    printf("\nInventory Management System\n");
    printf("1. Add Item\n");
    printf("2. Display Items\n");
    printf("3. Search Item\n");
    printf("4. Update Item\n");
    printf("5. Delete Item\n");
    printf("6. Exit\n");
}


int main() {
    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                searchItem();
                break;
            case 4:
                updateItem();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
