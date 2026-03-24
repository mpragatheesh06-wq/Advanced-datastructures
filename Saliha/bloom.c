#include <stdio.h>

#define SIZE 10

int bloom[SIZE];

void initialize() {
    for (int i = 0; i < SIZE; i++)
        bloom[i] = 0;
}

int hash1(int key) {
    return key % SIZE;
}

int hash2(int key) {
    return (key / SIZE) % SIZE;
}

void insert() {
    int key;
    printf("enter the element to insert ");
    scanf("%d", &key);

    int h1 = hash1(key);
    int h2 = hash2(key);

    bloom[h1] = 1;
    bloom[h2] = 1;

    printf("element is inserted");
}

void search() {
    int key;
    printf("enter eelement to search ");
    scanf("%d", &key);

    int h1 = hash1(key);
    int h2 = hash2(key);

    if (bloom[h1] == 1 && bloom[h2] == 1)
        printf("Element may be present");
    else
        printf("Element is DEFINITELY not present");
}

void display() {
    printf("Bloom Filter ");
    for (int i = 0; i < SIZE; i++)
        printf("%d ", bloom[i]);
    printf("\n");
}

int main() {
    int choice;
    initialize();

    while (1) {
        printf("\n--- Bloom Filter Menu ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: search(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}