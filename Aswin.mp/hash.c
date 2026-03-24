#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

struct Node {
    int data;
    struct Node *next;
};

struct Node *table[SIZE];

int hash(int key) {
    return key % SIZE;
}

void insert(int key) {
    int i = hash(key);
    struct Node *n = malloc(sizeof(struct Node));
    n->data = key;
    n->next = table[i];
    table[i] = n;
}

void delete(int key) {
    int i = hash(key);
    struct Node *t = table[i], *p = NULL;

    while (t) {
        if (t->data == key) {
            if (p) p->next = t->next;
            else table[i] = t->next;
            free(t);
            printf("Deleted\n");
            return;
        }
        p = t;
        t = t->next;
    }
    printf("Not found\n");
}

void display() {
    for (int i = 0; i < SIZE; i++) {
        printf("%d: ", i);
        for (struct Node *t = table[i]; t; t = t->next)
            printf("%d -> ", t->data);
        printf("NULL\n");
    }
}

int main() {
    int ch, key;

    for (int i = 0; i < SIZE; i++) table[i] = NULL;

    while (1) {
        printf("\n1.Insert 2.Delete 3.Display 4.Exit: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("Value: ");
            scanf("%d", &key);
            insert(key);
        }
        else if (ch == 2) {
            printf("Value: ");
            scanf("%d", &key);
            delete(key);
        }
        else if (ch == 3) display();
        else break;
    }
    return 0;
}