#include "main.h"

int main() {
    char expression[256];
    // char* expression = NULL;
    stackRPN* stack = NULL;
    stackRPN* RPN = NULL;
    
    scanf("%s", expression);
    parserExpression(expression, &stack);
    if (!stackIsEmpty(stack)) {
        translationRPN(stack, RPN);
    }
    if (!stackIsEmpty(RPN)) {
        calculationRPN(RPN);
    }
    return 0;
}
