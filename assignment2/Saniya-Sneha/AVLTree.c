#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
    int height;
};

int height(struct node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

struct node* create(int data) {
    struct node *n = (struct node*)malloc(sizeof(struct node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return n;
}

struct node* rightRotate(struct node *y) {
    struct node *x = y->left;

    y->left = x->right;
    x->right = y;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct node* leftRotate(struct node *x) {
    struct node *y = x->right;

    x->right = y->left;
    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int balance(struct node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

struct node* insert(struct node *root, int data) {

    if (root == NULL)
        return create(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int bf = balance(root);

    if (bf > 1 && data < root->left->data)
        return rightRotate(root);
        
    if (bf < -1 && data > root->right->data)
        return leftRotate(root);
        
    if (bf > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    struct node *root = NULL;
    int choice, key;

    while (1) {
        printf("\n1.Insert\n2.Display\n3.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter value: ");
            scanf("%d", &key);
            root = insert(root, key);
        }
        else if (choice == 2) {
            printf("AVL Tree: ");
            inorder(root);
            printf("\n");
        }
        else if (choice == 3) {
            break;
        }
        else {
            printf("Wrong choice\n");
        }
    }
    return 0;
}
