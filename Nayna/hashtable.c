#include <stdio.h>

#define SIZE 10

int table[SIZE];


void init() {
    for (int i = 0; i < SIZE; i++)
        table[i] = -1;
}


int hash(int key) {
    return key % SIZE;
}


void insert(int key) {
    int index = hash(key);

    while (table[index] != -1) {
        index = (index + 1) % SIZE;
    }
    table[index] = key;
}


int search(int key) {
    int index = hash(key);
    int start = index;

    while (table[index] != -1) {
        if (table[index] == key)
            return index;
        index = (index + 1) % SIZE;
        if (index == start)
            break;
    }
    return -1;
}


void delete(int key) {
    int index = search(key);
    if (index != -1)
        table[index] = -1;
}


void display() {
    for (int i = 0; i < SIZE; i++)
        printf("%d -> %d\n", i, table[i]);
}

int main() {
    init();

    insert(10);
    insert(20);
    insert(30);
    insert(25);

    display();

    printf("\nSearching 20: Index %d\n", search(20));

    delete(20);
    printf("\nAfter deleting 20:\n");
    display();

    return 0;
}