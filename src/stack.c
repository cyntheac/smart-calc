#include "main.h"

stackRPN *createNode(double operand, char operator, type_priority type) {
    stackRPN *node = (stackRPN *)malloc(sizeof(stackRPN));
    if (node == NULL) {
        exit(1);
    }
    node->operand = operand;
    node->operator = operator;
    node->type = type;
    node->next = NULL;
    return node;
}

void push(stackRPN **stack, double operand, char operator, type_priority type) {
    stackRPN *newNode = createNode(operand, operator, type);
    newNode->next = *stack;
    *stack = newNode;
}

void pop(stackRPN **stack) {
    stackRPN *tmp = *stack;
    *stack = tmp->next;
    free(tmp);
}


void freeStack(stackRPN **stack) {
    while (stack) {
        pop(&stack);
    }
}

bool StackIsEmpty(stackRPN* stack) {
    return stack == NULL;
}
