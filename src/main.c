#include "main.h"

int main() {
    // обязательно ли руками выдавать память для каждого символа в дин.массиве?
    char expression[256];
    // char* expression = NULL;
    stackRPN* stack = NULL;
    stackRPN* revStack = NULL;
    stackRPN* RPN = NULL;
    
    scanf("%s", expression);
    parserExpression(expression, &stack);
    if (!stackIsEmpty(stack)) {
        reverseStack(stack, &revStack);
        // while (revStack) конструкция для отображения стека (убрать при работе)
        while (revStack) {
            printf("num: %lf, oper: %c, func: %s\n", revStack->operand, revStack->operator, revStack->function);
            pop(&revStack);
        }
        translationRPN(revStack, RPN);
        freeStack(&revStack);
    }
    if (!stackIsEmpty(RPN)) {
        calculationRPN(RPN);
        freeStack(&RPN);
    }
    return 0;
}
