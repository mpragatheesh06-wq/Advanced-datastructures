#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

struct Node {
    int data;
    struct Node *next;
};

struct Node *table[SIZE];

int hash(int key) {
    return key%SIZE;
}

void insert(int key) {
    int idx=hash(key);
    struct Node *n=malloc(sizeof(struct Node));
    n->data=key;
    n->next=table[idx];
    table[idx]=n;
}

int search(int key) {
    int idx=hash(key);
    struct Node *t=table[idx];
    while (t) {
        if (t->data==key)
            return 1;
        t=t->next;
    }
    return 0;
}

void display() {
    for (int i=0;i<SIZE;i++) {
        printf("%d:", i);
        struct Node *t=table[i];
        while (t) {
            printf("%d ->",t->data);
            t=t->next;
        }
        printf("NULL\n");
    }
}

int main() {
    for (int i=0;i<SIZE;i++)
        table[i]=NULL;
    insert(13);
    insert(25);
    insert(56);
    insert(89);
    insert(42);

    display();
    if (search(25))
        printf("25 found");
    else
        printf("25 not found");

    return 0;
}