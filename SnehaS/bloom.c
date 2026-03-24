//bloom filter
#include <stdio.h>
#define SIZE 10
int bloom[SIZE];
int hash1(int key) {
    return key % SIZE;
}
int hash2(int key) {
    return (key / SIZE) % SIZE;
}
int main() {
    int i, choice, key;
    for (i = 0; i < SIZE; i++)
        bloom[i] = 0;
    while (1) {
        printf("\n1)Insert\n2)Search\n3)Display\n4)Exit\n");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter key: ");
            scanf("%d", &key);
            bloom[hash1(key)] = 1;
            bloom[hash2(key)] = 1;
            printf("Key inserted\n");
        }
        else if (choice == 2) {
            printf("Enter key to search: ");
            scanf("%d", &key);
            if (bloom[hash1(key)] == 1 &&
                bloom[hash2(key)] == 1)
                printf("Key may be present\n");
            else
                printf("Key not present\n");
        }
        else if (choice == 3) {
            for (i = 0; i < SIZE; i++)
                printf("%d ", bloom[i]);
            printf("\n");
        }
        else if (choice == 4) {
            break;
        }
        else {
            printf("Invalid choice\n");
        }
    }
        return 0;
}
    
        