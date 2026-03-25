#include <stdio.h>
#include <stdlib.h>

//  NODE 
struct node {
    int x, y;
    int data;
    struct node *nw, *ne, *sw, *se;
};

//  CREATE NODE 
struct node* createNode(int x, int y, int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->x = x;
    newNode->y = y;
    newNode->data = data;

    newNode->nw = newNode->ne = newNode->sw = newNode->se = NULL;

    return newNode;
}

// INSERT 
struct node* insert(struct node* root, int x, int y, int data) {
    if (root == NULL)
        return createNode(x, y, data);

    // Decide quadrant
    if (x < root->x && y >= root->y)
        root->nw = insert(root->nw, x, y, data);   // NW

    else if (x >= root->x && y >= root->y)
        root->ne = insert(root->ne, x, y, data);   // NE

    else if (x < root->x && y < root->y)
        root->sw = insert(root->sw, x, y, data);   // SW

    else
        root->se = insert(root->se, x, y, data);   // SE

    return root;
}

//  TRAVERSE 
void traverse(struct node* root) {
    if (root == NULL)
        return;

    printf("(%d,%d) ", root->x, root->y);

    traverse(root->nw);
    traverse(root->ne);
    traverse(root->sw);
    traverse(root->se);
}

int main() {
    struct node* root = NULL;

    root = insert(root, 50, 50, 1);
    root = insert(root, 30, 70, 2);
    root = insert(root, 70, 70, 3);
    root = insert(root, 30, 30, 4);
    root = insert(root, 70, 30, 5);

    printf("Quad Tree nodes:\n");
    traverse(root);

    return 0;
}