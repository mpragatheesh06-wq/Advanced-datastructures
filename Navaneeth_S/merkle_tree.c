#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char hash[50];
    struct Node *left, *right;
};

// Simple hash function (sum of ASCII values)
void computeHash(char *input, char *output) {
    int sum = 0;
    for (int i = 0; input[i] != '\0'; i++)
        sum += input[i];

    sprintf(output, "%d", sum);
}

// Create a leaf node
struct Node* createLeaf(char *data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    computeHash(data, node->hash);
    node->left = node->right = NULL;
    return node;
}

// Create a parent node
struct Node* createParent(struct Node *left, struct Node *right) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));

    char combined[100];
    strcpy(combined, left->hash);
    strcat(combined, right->hash);

    computeHash(combined, node->hash);

    node->left = left;
    node->right = right;
    return node;
}

// Build Merkle Tree
struct Node* buildMerkleTree(struct Node *nodes[], int n) {
    while (n > 1) {
        int i, j = 0;

        for (i = 0; i < n; i += 2) {
            if (i + 1 < n)
                nodes[j++] = createParent(nodes[i], nodes[i + 1]);
            else
                nodes[j++] = createParent(nodes[i], nodes[i]); // duplicate last
        }

        n = j;
    }
    return nodes[0]; // root
}

// Inorder traversal
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->hash);
        inorder(root->right);
    }
}

// Main function
int main() {
    struct Node *nodes[4];

    nodes[0] = createLeaf("A");
    nodes[1] = createLeaf("B");
    nodes[2] = createLeaf("C");
    nodes[3] = createLeaf("D");

    struct Node *root = buildMerkleTree(nodes, 4);

    printf("Merkle Root: %s\n", root->hash);

    printf("Inorder Traversal:\n");
    inorder(root);

    return 0;
}