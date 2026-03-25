#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Operation {
    int value;
    int time;
};

struct Operation ops[MAX];
int top = -1;

//  ADD OPERATION 
void addOperation(int value, int time) {
    if (top >= MAX - 1) {
        printf("Overflow\n");
        return;
    }
    top++;
    ops[top].value = value;
    ops[top].time = time;
}

//  SORT OPERATIONS 
void sortOperations() {
    for (int i = 0; i <= top; i++) {
        for (int j = 0; j < top - i; j++) {
            if (ops[j].time > ops[j + 1].time) {
                struct Operation temp = ops[j];
                ops[j] = ops[j + 1];
                ops[j + 1] = temp;
            }
        }
    }
}

//  BUILD STACK AT TIME 
void buildStackAtTime(int time) {
    int stack[MAX];
    int sTop = -1;

    for (int i = 0; i <= top; i++) {
        if (ops[i].time <= time) {
            if (sTop < MAX - 1)
                stack[++sTop] = ops[i].value;
        }
    }

    printf("Stack at time %d:\n", time);

    if (sTop == -1) {
        printf("Empty\n");
        return;
    }

    for (int i = 0; i <= sTop; i++) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}


int main() {

    addOperation(10, 1);
    addOperation(20, 3);
    addOperation(30, 2);
    addOperation(40, 5);

    sortOperations();

    buildStackAtTime(2);
    buildStackAtTime(4);

    return 0;
}