#include "main.h"

int main() {
    char* expression = NULL;
    stackRPN* stack = NULL;
    // stackRPN* RPN = NULL;
    scanf("%s", expression);
    parserExpression(expression, stack);
    // if (!StackIsEmpty(stack)) {
    //     translationRPN(stack, RPN);
    // }
    // if (!StackIsEmpty(RPN)) {
    //     calculationRPN(RPN);
    // }
    return 0;
}

// void translationRPN(stackRPN* stack, stackRPN* RPN) {
//     int c;
// }

// void calculationRPN(stackRPN* RPN) {
//     int d;
// }

