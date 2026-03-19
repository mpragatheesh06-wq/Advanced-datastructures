#include <stdio.h>
#include <string.h>

// Simple hash function (for demo only)
int hash(char *str) {
    int sum = 0;
    for (int i = 0; i < strlen(str); i++) {
        sum += str[i];
    }
    return sum;
}

int main() {
    char data[4][10] = {"A", "B", "C", "D"};

    int h[4];
    
    // Step 1: Hash leaf nodes
    for (int i = 0; i < 4; i++) {
        h[i] = hash(data[i]);
        printf("Hash of %s = %d\n", data[i], h[i]);
    }

    // Step 2: Combine hashes
    int h12 = hash("AB"); // simplified
    int h34 = hash("CD");

    printf("Hash of AB = %d\n", h12);
    printf("Hash of CD = %d\n", h34);

    // Step 3: Root
    int root = hash("ABCD");

    printf("Merkle Root = %d\n", root);

    return 0;
}