#include <stdio.h>
#include <string.h>

#define SIZE 20

int bloom[SIZE];

int hash1(char word[]) {
    int total = 0;
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        total = total + word[i];
    }
    return total % SIZE;
}

int hash2(char word[]) {
    int total = 1;
    int i;
    for (i = 0; word[i] != '\0'; i++) {
        total = (total * word[i]) % SIZE;
    }
    return total;
}

void add(char word[]) {
    bloom[hash1(word)] = 1;
    bloom[hash2(word)] = 1;
}

void check(char word[]) {
    if (bloom[hash1(word)] == 1 && bloom[hash2(word)] == 1) {
        printf("%s : May be present\n", word);
    } else {
        printf("%s : Not present\n", word);
    }
}

int main() {
    int i;

    for (i = 0; i < SIZE; i++) {
        bloom[i] = 0;
    }

    add("red");
    add("blue");

    printf("Bloom Filter: ");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", bloom[i]);
    }
    printf("\n");

    check("red");
    check("blue");
    check("black");

    return 0;
}