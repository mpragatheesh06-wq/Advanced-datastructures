#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

int bloom[SIZE];


int hash1(int key) {
    return key % SIZE;
}


int hash2(int key) {
    return (key / 7) % SIZE;
}


void insert(int key) {
    bloom[hash1(key)] = 1;
    bloom[hash2(key)] = 1;
}


bool check(int key) {
    if (bloom[hash1(key)] && bloom[hash2(key)])
        return true;    
    return false;      
}


void display() {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", bloom[i]);
    printf("\n");
}

int main() {
    insert(10);
    insert(20);
    insert(30);

    display();

    printf("Check 20: %s\n", check(20) ? "Possibly Present" : "Not Present");
    printf("Check 25: %s\n", check(25) ? "Possibly Present" : "Not Present");

    return 0;
}