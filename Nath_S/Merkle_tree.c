#include <stdio.h>

//  HASH FUNCTION 
int hash(int x) {
    return (x * 31) % 1000;
}

//  BUILD MERKLE TREE
int buildMerkle(int arr[], int n) {
    if (n == 1)
        return hash(arr[0]);

    int temp[1000];
    int j = 0;

    for (int i = 0; i < n; i += 2) {
        int left = hash(arr[i]);
        int right;

        if (i + 1 < n)
            right = hash(arr[i + 1]);
        else
            right = left;  // duplicate if odd

        temp[j++] = hash(left + right);
    }

    return buildMerkle(temp, j);
}

//  MAIN 
int main() {
    int m;

    printf("Enter number of elements: ");
    scanf("%d", &m);

    if (m <= 0) {
        printf("Invalid input\n");
        return 0;
    }

    int arr[1000];

    printf("Enter %d numbers:\n", m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr[i]);
    }

    int root = buildMerkle(arr, m);

    printf("Merkle Root = %d\n", root);

    return 0;
}