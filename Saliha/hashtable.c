#include <stdio.h>

#define SIZE 10

int hashTable[SIZE];

void initialize() {
    for (int i = 0; i < SIZE; i++)
        hashTable[i] = -1;
}

void insert() {
    int key, index;

    printf("Enter key to insert: ");
    scanf("%d", &key);

    index = key % SIZE;

    while (hashTable[index] != -1) {
        index = (index + 1) % SIZE;   // Linear probing
    }

    hashTable[index] = key;
    printf("Key inserted successfully.\n");
}

void search() {
    int key, index, start;

    printf("Enter key to search: ");
    scanf("%d", &key);

    index = key % SIZE;
    start = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            printf("Key found at index %d\n", index);
            return;
        }
        index = (index + 1) % SIZE;
        if (index == start)
            break;
    }

    printf("Key not found.\n");
}

 void deleteKey() {
    int key, index, start;

    printf("Enter key to delete: ");
    scanf("%d", &key);

    index = key % SIZE;
    start = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            hashTable[index] = -1;
            printf("Key deleted successfully.\n");
            return;
        }
        index = (index + 1) % SIZE;
        if (index == start)
            break;
    }

    printf("Key not found.\n");
}

void display() {
    printf("\nHash Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (hashTable[i] == -1)
            printf("Index %d: Empty\n", i);
        else
            printf("Index %d: %d\n", i, hashTable[i]);
    }
}

int main() {
    int choice;

    initialize();

    while (1) {
        printf("\n--- Hash Table Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: search(); break;
            case 3: deleteKey(); break;
            case 4: display(); break;
            case 5: return 0;
            default: printf("Invalid choice\n");
        }
    }
}