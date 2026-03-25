#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct node {
    int data;
    int color;
    struct node* left;
    struct node* right;
    struct node* parent;
};

struct node* root = NULL;

//  CREATE NODE 
struct node* createNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->data = value;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

//  LEFT ROTATE 
struct node* leftRotate(struct node* root, struct node* x) {
    struct node* y = x->right;

    if (y == NULL) return root;  // safety

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

    return root;
}

//  RIGHT ROTATE 
struct node* rightRotate(struct node* root, struct node* x) {
    struct node* y = x->left;

    if (y == NULL) return root;  // safety

    x->left = y->right;

    if (y->right != NULL)
        y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;

    return root;
}

//  FIX INSERT 
struct node* fixInsert(struct node* root, struct node* z) {

    while (z != root && z->parent->color == RED) {

        struct node* parent = z->parent;
        struct node* grandparent = parent->parent;

        // Parent is left child
        if (parent == grandparent->left) {

            struct node* uncle = grandparent->right;

            // Case 1: Uncle RED
            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else {
                // Case 2: Triangle
                if (z == parent->right) {
                    root = leftRotate(root, parent);
                    z = parent;
                    parent = z->parent;
                }

                // Case 3: Line
                parent->color = BLACK;
                grandparent->color = RED;
                root = rightRotate(root, grandparent);
            }
        }

        // Mirror case
        else {
            struct node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else {
                if (z == parent->left) {
                    root = rightRotate(root, parent);
                    z = parent;
                    parent = z->parent;
                }

                parent->color = BLACK;
                grandparent->color = RED;
                root = leftRotate(root, grandparent);
            }
        }
    }

    root->color = BLACK;
    return root;
}

//  INSERT 
struct node* insert(struct node* root, int value) {

    struct node* newNode = createNode(value);

    struct node* y = NULL;
    struct node* x = root;

    // BST insert
    while (x != NULL) {
        y = x;
        if (value < x->data)
            x = x->left;
        else
            x = x->right;
    }

    newNode->parent = y;

    if (y == NULL)
        root = newNode;
    else if (value < y->data)
        y->left = newNode;
    else
        y->right = newNode;

    return fixInsert(root, newNode);
}

//  INORDER 
void inorder(struct node* root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
    inorder(root->right);
}


int main() {

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 5);

    printf("Inorder traversal:\n");
    inorder(root);

    return 0;
}