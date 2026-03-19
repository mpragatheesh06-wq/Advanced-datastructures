#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data, degree;
    struct Node *child, *sibling, *parent;
};

struct Node* createNode(int key) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = key;
    n->degree = 0;
    n->child = n->sibling = n->parent = NULL;
    return n;
}

// Link two binomial trees
struct Node* linkTrees(struct Node* y, struct Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
    return z;
}

// Merge root lists (simple version)
struct Node* merge(struct Node* h1, struct Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct Node* head = NULL;
    struct Node** pos = &head;

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            *pos = h1;
            h1 = h1->sibling;
        } else {
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &((*pos)->sibling);
    }

    *pos = (h1) ? h1 : h2;
    return head;
}

// Insert node (simple)
struct Node* insert(struct Node* heap, int key) {
    struct Node* temp = createNode(key);
    return merge(heap, temp);
}

// Print root list
void printHeap(struct Node* heap) {
    printf("Heap roots: ");
    while (heap) {
        printf("%d ", heap->data);
        heap = heap->sibling;
    }
    printf("\n");
}

int main() {
    struct Node* heap = NULL;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);

    printHeap(heap);

    return 0;
}