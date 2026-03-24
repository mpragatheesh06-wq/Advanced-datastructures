#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Operation types
typedef enum { PUSH, POP } OpType;

// Operation node
typedef struct Operation {
    int time;       // Timestamp of the operation
    OpType type;    
    int value;      // Only valid for PUSH
    struct Operation* next;
} Operation;

// Stack node
typedef struct StackNode {
    int value;
    struct StackNode* next;
} StackNode;

// Add operation to the operation list in time order
Operation* insertOperation(Operation* head, int time, OpType type, int value) {
    Operation* op = (Operation*)malloc(sizeof(Operation));
    op->time = time;
    op->type = type;
    op->value = value;
    op->next = NULL;

    if (!head || time < head->time) {
        op->next = head;
        return op;
    }

    Operation* curr = head;
    while (curr->next && curr->next->time < time)
        curr = curr->next;

    op->next = curr->next;
    curr->next = op;
    return head;
}

// Rebuild stack at given time
StackNode* buildStack(Operation* head, int queryTime) {
    StackNode* stack = NULL;

    Operation* curr = head;
    while (curr && curr->time <= queryTime) {
        if (curr->type == PUSH) {
            StackNode* node = (StackNode*)malloc(sizeof(StackNode));
            node->value = curr->value;
            node->next = stack;
            stack = node;
        } else if (curr->type == POP && stack) {
            StackNode* temp = stack;
            stack = stack->next;
            free(temp);
        }
        curr = curr->next;
    }

    return stack;
}

// Print stack from top to bottom
void printStack(StackNode* stack) {
    printf("Stack top -> bottom: ");
    while (stack) {
        printf("%d ", stack->value);
        stack = stack->next;
    }
    printf("\n");
}

// Free stack memory
void freeStack(StackNode* stack) {
    while (stack) {
        StackNode* temp = stack;
        stack = stack->next;
        free(temp);
    }
}

// Example usage
int main() {
    Operation* operations = NULL;

    // Add operations retroactively
    operations = insertOperation(operations, 1, PUSH, 10);
    operations = insertOperation(operations, 3, PUSH, 20);
    operations = insertOperation(operations, 2, POP, 0);    // retroactive pop at time 2
    operations = insertOperation(operations, 4, PUSH, 30);

    // Build stack at different times
    StackNode* stackAtTime2 = buildStack(operations, 2);
    printf("Stack at time 2:\n");
    printStack(stackAtTime2);
    freeStack(stackAtTime2);

    StackNode* stackAtTime4 = buildStack(operations, 4);
    printf("Stack at time 4:\n");
    printStack(stackAtTime4);
    freeStack(stackAtTime4);

    // Free operation list
    while (operations) {
        Operation* temp = operations;
        operations = operations->next;
        free(temp);
    }

    return 0;
}
