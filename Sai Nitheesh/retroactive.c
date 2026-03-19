#include <stdio.h>

#define MAX 100

typedef struct {
    int type; // 1 = push, 2 = pop
    int value;
} Operation;

Operation ops[MAX];
int opCount = 0;

// Add operation at end
void addOperation(int type, int value) {
    ops[opCount].type = type;
    ops[opCount].value = value;
    opCount++;
}

// Insert operation in past
void insertOperation(int pos, int type, int value) {
    for (int i = opCount; i > pos; i--) {
        ops[i] = ops[i - 1];
    }
    ops[pos].type = type;
    ops[pos].value = value;
    opCount++;
}

// Recompute stack
void computeStack() {
    int stack[MAX], top = -1;

    for (int i = 0; i < opCount; i++) {
        if (ops[i].type == 1) {
            stack[++top] = ops[i].value;
        } else if (ops[i].type == 2 && top >= 0) {
            top--;
        }
    }

    printf("Current Stack: ");
    for (int i = 0; i <= top; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

int main() {
    addOperation(1, 10); // push 10
    addOperation(1, 20); // push 20
    addOperation(2, 0);  // pop

    computeStack();

    // Retroactive insert
    insertOperation(1, 1, 30); // insert push(30) at position 1

    computeStack();

    return 0;
}