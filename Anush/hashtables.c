#include <stdio.h>

#define SIZE 10

int table[SIZE];

int main() {

    int i, key, index;

     
    for (i = 0; i < SIZE; i++) {
        table[i] = -1;   
    }

    
    int values[] = {23, 43, 13, 27};

    for (i = 0; i < 4; i++) {

        key = values[i];

       
        index = key % SIZE;

       
        while (table[index] != -1) {
            index = (index + 1) % SIZE;
        }

        table[index] = key;
    }

   
    printf("Hash Table Contents:\n");
    for (i = 0; i < SIZE; i++) {
        if (table[i] == -1)
            printf("Index %d : EMPTY\n", i);
        else
            printf("Index %d : %d\n", i, table[i]);
    }

   
    key = 43;
    index = key % SIZE;
    int start = index;
    int found = 0;

    while (table[index] != -1) {

        if (table[index] == key) {
            printf("\nKey %d found at index %d\n", key, index);
            found = 1;
            break;
        }

        index = (index + 1) % SIZE;

        if (index == start)
            break;
    }

    if (!found) {
        printf("\nKey %d not found\n", key);
    }

    return 0;
}