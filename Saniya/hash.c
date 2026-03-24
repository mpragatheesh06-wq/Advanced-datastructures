#include <stdio.h>
#include <stdlib.h>
#define SIZE 50
#define EMPTY -1

int hashtable[SIZE];
int hash(int key) {
    return key % SIZE;
}
void insert() {
    int key;
    printf("Enter key to insert: ");
    scanf("%d", &key);

    int index = hash(key);
    int startIndex = index;

    while(hashtable[index] != EMPTY) {
        index = (index + 1) % SIZE;
        if(index == startIndex) { 
            printf("Hash table is full!\n");
            return;
        }
    }

    hashtable[index] = key;
    printf("Key %d inserted at index %d\n", key, index);
}


void search() {
    int key;
    printf("Enter key to search: ");
    scanf("%d", &key);

    int index = hash(key);
    int startIndex = index;

    while(hashtable[index] != EMPTY) {
        if(hashtable[index] == key) {
            printf("Key %d found at index %d\n", key, index);
            return;
        }
        index = (index + 1) % SIZE;
        if(index == startIndex)
        break;
    }

    printf("Key %d not found in hash table\n", key);
}

void display() {
    printf("Hash table contents:\n");
    for(int i = 0; i < SIZE; i++) {
        if(hashtable[i] != EMPTY)
            printf("Index %d: %d\n", i, hashtable[i]);
        else
            printf("%d: EMPTY\n", i);
    }
}

int main() {
    for(int i=0;i<SIZE;i++){
        hashtable[i]=EMPTY;
    }
    int choice;
    while(1) {
        printf("\n1. Insert\n2. Search\n3. Display\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: insert(); break;
            case 2: search(); break;
            case 3: display(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}