#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    int degree;
    struct Node *parent, *child, *sibling;
};

// Create node
struct Node* createNode(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->degree = 0;
    node->parent = node->child = node->sibling = NULL;
    return node;
}

// Merge two binomial trees of same degree
struct Node* mergeTrees(struct Node *b1, struct Node *b2) {
    if (b1->data > b2->data) {
        struct Node *temp = b1;
        b1 = b2;
        b2 = temp;
    }

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

// Merge root lists
struct Node* mergeHeaps(struct Node *h1, struct Node *h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct Node *head = NULL, *tail = NULL;

    while (h1 && h2) {
        struct Node *min;
        if (h1->degree <= h2->degree) {
            min = h1;
            h1 = h1->sibling;
        } else {
            min = h2;
            h2 = h2->sibling;
        }

        if (!head) head = tail = min;
        else {
            tail->sibling = min;
            tail = min;
        }
    }

    if (h1) tail->sibling = h1;
    else tail->sibling = h2;

    return head;
}

// Union operation
struct Node* unionHeap(struct Node *h1, struct Node *h2) {
    struct Node *head = mergeHeaps(h1, h2);
    if (!head) return NULL;

    struct Node *prev = NULL;
    struct Node *curr = head;
    struct Node *next = curr->sibling;

    while (next != NULL) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->data <= next->data) {
                curr->sibling = next->sibling;
                curr = mergeTrees(curr, next);
            } else {
                if (prev == NULL)
                    head = next;
                else
                    prev->sibling = next;

                next = mergeTrees(next, curr);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return head;
}

// Insert
struct Node* insert(struct Node *heap, int data) {
    struct Node *newNode = createNode(data);
    return unionHeap(heap, newNode);
}

// Print root list
void printHeap(struct Node *heap) {
    while (heap != NULL) {
        printf("B%d: %d\n", heap->degree, heap->data);
        heap = heap->sibling;
    }
}

// Main
int main() {
    struct Node *heap = NULL;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);
    heap = insert(heap, 30);

    printf("Binomial Heap:\n");
    printHeap(heap);

    return 0;
}