#include "main.h"

stackRPN *createNode(double operand, char operator, char* function, type_priority type) {
    stackRPN *node = (stackRPN *)malloc(sizeof(stackRPN));
    if (node == NULL) {
        exit(1);
    }
    node->operand = operand;
    node->operator = operator;
    // node->function[0] = '\0';
    if (function) {
        memcpy(node->function, function, strlen(function));
    }
    node->type = type;
    node->next = NULL;
    return node;
}

void push(stackRPN **stack, double operand, char operator, char* function, type_priority type) {
    stackRPN *newNode = createNode(operand, operator, function, type);
    newNode->next = *stack;
    *stack = newNode;
}

void pop(stackRPN** stack) {
    stackRPN *tmp = *stack;
    *stack = tmp->next;
    free(tmp);
}

void freeStack(stackRPN** stack) {
    while (*stack) {
        pop(stack);
    }
}

bool stackIsEmpty(stackRPN* stack) {
    return stack == NULL;
}

void reverseStack(stackRPN* stackSrc, stackRPN** stackDst) {
    while (stackSrc) {
        push(stackDst, stackSrc->operand, stackSrc->operator, stackSrc->function, stackSrc->type);
        pop(&stackSrc);
    }
    // нужно ли чистить, если мы уже всё забрали?
    freeStack(&stackSrc);
}
