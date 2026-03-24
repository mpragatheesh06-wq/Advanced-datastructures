#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;

// Create node
Node* createNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->color = RED;
    n->left = n->right = n->parent = NULL;
    return n;
}

// Left Rotate
void leftRotate(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Right Rotate
void rightRotate(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;

    if (!y->parent)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix Insert
void fixInsert(Node **root, Node *z) {
    while (z->parent && z->parent->color == RED) {
        Node *p = z->parent;
        Node *g = p->parent;

        if (p == g->left) {
            Node *u = g->right;

            if (u && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->right) {
                    z = p;
                    leftRotate(root, z);
                }
                p->color = BLACK;
                g->color = RED;
                rightRotate(root, g);
            }
        } else {
            Node *u = g->left;

            if (u && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                g->color = RED;
                z = g;
            } else {
                if (z == p->left) {
                    z = p;
                    rightRotate(root, z);
                }
                p->color = BLACK;
                g->color = RED;
                leftRotate(root, g);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insert
void insert(int data) {
    Node *z = createNode(data);
    Node *y = NULL;
    Node *x = root;

    while (x) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (!y)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(&root, z);
}

// Minimum
Node* minimum(Node *node) {
    while (node->left)
        node = node->left;
    return node;
}

// Transplant
void transplant(Node **root, Node *u, Node *v) {
    if (!u->parent)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

// Search
Node* search(Node *root, int key) {
    if (!root || root->data == key)
        return root;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

// Fix Delete
void fixDelete(Node **root, Node *x) {
    while (x != *root && (!x || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;

            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right)
                    w->right->color = BLACK;

                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node *w = x->parent->left;

            if (w && w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left)
                    w->left->color = BLACK;

                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x)
        x->color = BLACK;
}

// Delete
void deleteNode(int key) {
    Node *z = search(root, key);
    if (!z) {
        printf("Value not found!\n");
        return;
    }

    Node *y = z;
    Node *x;
    int yOriginalColor = y->color;

    if (!z->left) {
        x = z->right;
        transplant(&root, z, z->right);
    } else if (!z->right) {
        x = z->left;
        transplant(&root, z, z->left);
    } else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(&root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(&root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK)
        fixDelete(&root, x);
}

// Inorder Traversal
void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
    inorder(root->right);
}

// MAIN MENU
int main() {
    int choice, value;

    while (1) {
        printf("\n--- Red Black Tree Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Traverse (Inorder)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                break;

            case 3:
                printf("Inorder traversal:\n");
                inorder(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
