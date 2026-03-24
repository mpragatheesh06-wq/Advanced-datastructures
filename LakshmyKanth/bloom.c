#include <stdio.h>
#include <string.h>

#define SIZE 20     
#define HASH_COUNT 3 
int bitArray[SIZE] = {0};

int hashFunction(char *item, int seed) {
    int hash = 0;

    for (int i = 0; item[i] != '\0'; i++) {
        hash = hash + item[i] + seed;
    }

    return hash % SIZE;
}

void add(char *item) {
    for (int i = 0; i < HASH_COUNT; i++) {
        int index = hashFunction(item, i);
        bitArray[index] = 1; 
    }
}

int contains(char *item) {
    for (int i = 0; i < HASH_COUNT; i++) {
        int index = hashFunction(item, i);
        if (bitArray[index] == 0) {
            
            return 0;
        }
    }
    
    return 1;
}

int main() {
    add("Cat");
    add("Dog");

    if (contains("Cat"))
        printf("Cat is present (maybe)\n");
    else
        printf("Cat is not present\n");

    if (contains("Bird"))
        printf("Bird is present (maybe)\n");
    else
        printf("Bird is not present\n");

    return 0;
}