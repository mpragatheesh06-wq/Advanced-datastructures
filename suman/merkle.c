#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple hash function (djb2)
unsigned long hash(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c; // h * 33 + c
    return h;
}

// Node structure
typedef struct Node {
    unsigned long hash;
    struct Node *left;
    struct Node *right;
} Node;

// Create leaf node
Node* create_leaf(const char *data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = node->right = NULL;
    node->hash = hash(data);
    return node;
}

// Create parent node
Node* create_parent(Node *left, Node *right) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->left = left;
    node->right = right;

    char combined[50];
    sprintf(combined, "%lu%lu", left->hash, right->hash);
    node->hash = hash(combined);

    return node;
}

// Build Merkle Tree
Node* build_tree(Node **nodes, int n) {
    while (n > 1) {
        int new_n = (n + 1) / 2;
        Node **new_level = malloc(sizeof(Node*) * new_n);

        for (int i = 0; i < n; i += 2) {
            if (i + 1 < n)
                new_level[i/2] = create_parent(nodes[i], nodes[i+1]);
            else
                new_level[i/2] = create_parent(nodes[i], nodes[i]); // duplicate
        }

        nodes = new_level;
        n = new_n;
    }
    return nodes[0];
}

// Free memory
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

// Main
int main() {
    const char *data[] = {"a", "b", "c", "d"};
    int n = 4;

    Node **leaves = malloc(sizeof(Node*) * n);
    for (int i = 0; i < n; i++)
        leaves[i] = create_leaf(data[i]);

    Node *root = build_tree(leaves, n);

    printf("Merkle Root: %lu\n", root->hash);

    free_tree(root);
    return 0;
}
