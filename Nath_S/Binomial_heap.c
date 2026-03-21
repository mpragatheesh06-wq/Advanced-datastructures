#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
};

//  CREATE NODE 
struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// MERGE TREES 
struct node* mergeTrees(struct node* b1, struct node* b2) {
    if (b1->data > b2->data) {
        struct node* temp = b1;
        b1 = b2;
        b2 = temp;
    }

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;

    return b1;
}

// MERGE ROOT LISTS 
struct node* mergeHeaps(struct node* h1, struct node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    struct node* head = NULL;
    struct node* tail = NULL;

    if (h1->degree <= h2->degree) {
        head = h1;
        h1 = h1->sibling;
    } else {
        head = h2;
        h2 = h2->sibling;
    }

    tail = head;

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

//  UNION 
struct node* unionHeap(struct node* h1, struct node* h2) {
    struct node* newHead = mergeHeaps(h1, h2);
    if (!newHead) return NULL;

    struct node* prev = NULL;
    struct node* curr = newHead;
    struct node* next = curr->sibling;

    while (next != NULL) {

        if ((curr->degree != next->degree) ||
            (next->sibling != NULL && next->sibling->degree == curr->degree)) {

            prev = curr;
            curr = next;
        } 
        else {
            if (curr->data <= next->data) {
                curr->sibling = next->sibling;
                curr = mergeTrees(curr, next);
            } 
            else {
                if (prev == NULL)
                    newHead = next;
                else
                    prev->sibling = next;

                curr = mergeTrees(next, curr);
            }
        }

        next = curr->sibling;
    }

    return newHead;
}

//  INSERT
struct node* insert(struct node* heap, int value) {
    struct node* temp = createNode(value);
    temp->sibling = NULL;   // important
    return unionHeap(heap, temp);
}

//  FIND MIN 
struct node* getMin(struct node* heap) {
    if (!heap) return NULL;

    struct node* min = heap;
    struct node* curr = heap;

    while (curr != NULL) {
        if (curr->data < min->data)
            min = curr;
        curr = curr->sibling;
    }

    return min;
}

//  PRINT HEAP (ROOT LIST) 
void printHeap(struct node* heap) {
    printf("Root List: ");
    while (heap != NULL) {
        printf("%d ", heap->data);
        heap = heap->sibling;
    }
    printf("\n");
}


int main() {
    struct node* heap = NULL;

    heap = insert(heap, 10);
    heap = insert(heap, 20);
    heap = insert(heap, 5);
    heap = insert(heap, 30);

    printHeap(heap);

    struct node* min = getMin(heap);
    if (min != NULL)
        printf("Minimum element: %d\n", min->data);

    return 0;
}