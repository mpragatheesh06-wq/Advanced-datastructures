#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

// Node structure
struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED; // New node is always RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Left Rotation
void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right Rotation
void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix violations after insertion
void fixInsert(struct Node *z) {
    while (z != root && z->parent->color == RED) {
        struct Node *parent = z->parent;
        struct Node *grandparent = parent->parent;

        // Parent is left child
        if (parent == grandparent->left) {
            struct Node *uncle = grandparent->right;

            // Case 1: Uncle is RED
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } 
            else {
                // Case 2: z is right child
                if (z == parent->right) {
                    z = parent;
                    leftRotate(z);
                }

                // Case 3
                parent->color = BLACK;
                grandparent->color = RED;
                rightRotate(grandparent);
            }
        } 
        else {
            // Mirror cases
            struct Node *uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } 
            else {
                if (z == parent->left) {
                    z = parent;
                    rightRotate(z);
                }

                parent->color = BLACK;
                grandparent->color = RED;
                leftRotate(grandparent);
            }
        }
    }

    root->color = BLACK; // Root always black
}

// BST Insert
void insert(int data) {
    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(z);
}

// Inorder traversal
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Main function
int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(15);
    insert(5);

    printf("Inorder Traversal:\n");
    inorder(root);

    return 0;
}