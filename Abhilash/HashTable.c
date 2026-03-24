#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10

struct Node {
    char key[20];
    int value;
    struct Node *next;
};

struct Node *hashTable[SIZE];

int hashFunction(char key[]) {
    int total = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        total += key[i];
    }
    return total % SIZE;
}

void insert(char key[], int value) {
    int index = hashFunction(key);

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        struct Node *temp = hashTable[index];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void search(char key[]) {
    int index = hashFunction(key);
    struct Node *temp = hashTable[index];

    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            printf("%s found with value %d\n", key, temp->value);
            return;
        }
        temp = temp->next;
    }
    printf("%s not found\n", key);
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        printf("Index %d: ", i);
        struct Node *temp = hashTable[i];
        while (temp != NULL) {
            printf("(%s, %d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

int main() {
    for (int i = 0; i < SIZE; i++) {
        hashTable[i] = NULL;
    }

    insert("red", 10);
    insert("blue", 20);
    insert("black", 30);

    display();

    search("red");
    search("green");

    return 0;
}