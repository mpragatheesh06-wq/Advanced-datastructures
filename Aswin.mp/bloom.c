#include <stdio.h>
#include <string.h>

#define SIZE 20

int bloom[SIZE] = {0};

int hash1(char *str) {
    return strlen(str) % SIZE;
}

int hash2(char *str) {
    int sum = 0;
    for (int i = 0; str[i]; i++)
        sum += str[i];
    return sum % SIZE;
}

void insert(char *str) {
    bloom[hash1(str)] = 1;
    bloom[hash2(str)] = 1;
    printf("Inserted\n");
}

int check(char *str) {
    return bloom[hash1(str)] && bloom[hash2(str)];
}

void display() {
    for (int i = 0; i < SIZE; i++)
        printf("%d ", bloom[i]);
    printf("\n");
}

int main() {
    int choice;
    char word[30];

    while (1) {
        printf("\n1.Insert  2.Check  3.Display  4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter word: ");
            scanf("%s", word);
            insert(word);
        }
        else if (choice == 2) {
            printf("Enter word: ");
            scanf("%s", word);
            if (check(word))
                printf("Possibly present\n");
            else
                printf("Definitely not present\n");
        }
        else if (choice == 3) {
            display();
        }
        else break;
    }

    return 0;
}