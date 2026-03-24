#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Structure of a binomial heap node
typedef struct Node {
    int key;
    int degree;
    struct Node *parent;
    struct Node *child;
    struct Node *sibling;
} Node;

// Create a new node
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->parent = node->child = node->sibling = NULL;
    return node;
}

// Merge root lists (by degree)
Node* mergeHeaps(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node *head = NULL, *tail = NULL;

    if (h1->degree <= h2->degree) {
        head = tail = h1;
        h1 = h1->sibling;
    } else {
        head = tail = h2;
        h2 = h2->sibling;
    }

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            tail->sibling = h1;
            h1 = h1->sibling;
        } else {
            tail->sibling = h2;
            h2 = h2->sibling;
        }
        tail = tail->sibling;
    }

    tail->sibling = (h1) ? h1 : h2;
    return head;
}

// Link two trees of same degree
void linkTrees(Node* y, Node* z) {
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

// Union of two heaps
Node* unionHeap(Node* h1, Node* h2) {
    Node* newHead = mergeHeaps(h1, h2);
    if (!newHead) return NULL;

    Node *prev = NULL;
    Node *curr = newHead;
    Node *next = curr->sibling;

    while (next) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->key <= next->key) {
                curr->sibling = next->sibling;
                linkTrees(next, curr);
            } else {
                if (!prev)
                    newHead = next;
                else
                    prev->sibling = next;

                linkTrees(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }

    return newHead;
}

// Insert a key
Node* insert(Node* heap, int key) {
    Node* temp = createNode(key);
    return unionHeap(heap, temp);
}

// Find minimum node
Node* getMin(Node* heap) {
    if (!heap) return NULL;

    Node* minNode = heap;
    Node* curr = heap->sibling;

    while (curr) {
        if (curr->key < minNode->key)
            minNode = curr;
        curr = curr->sibling;
    }
    return minNode;
}

// Reverse list (used in extract-min)
Node* reverse(Node* node) {
    Node *prev = NULL, *curr = node, *next;
    while (curr) {
        curr->parent = NULL;
        next = curr->sibling;
        curr->sibling = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Extract minimum
Node* extractMin(Node* heap) {
    if (!heap) return NULL;

    Node *minNode = heap, *minPrev = NULL;
    Node *curr = heap, *prev = NULL;

    // Find min node
    while (curr) {
        if (curr->key < minNode->key) {
            minNode = curr;
            minPrev = prev;
        }
        prev = curr;
        curr = curr->sibling;
    }

    // Remove min node
    if (minPrev)
        minPrev->sibling = minNode->sibling;
    else
        heap = minNode->sibling;

    // Reverse children and union
    Node* child = reverse(minNode->child);
    heap = unionHeap(heap, child);

    printf("Extracted min: %d\n", minNode->key);
    free(minNode);

    return heap;
}

// Print root list
void printHeap(Node* heap) {
    printf("Heap: ");
    while (heap) {
        printf("%d ", heap->key);
        heap = heap->sibling;
    }
    printf("\n");
}

// Main
int main() {
    Node* heap = NULL;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);
    heap = insert(heap, 30);

    printHeap(heap);

    Node* min = getMin(heap);
    if (min)
        printf("Minimum: %d\n", min->key);

    heap = extractMin(heap);
    printHeap(heap);

    return 0;
}
