#include "main.h"

void translationRPN(stackRPN* stack, stackRPN* RPN) {
    stackRPN* buffStack = NULL;
    while (stack) {
        switch (stack->type) {
            case number:
                push(&RPN, stack->operand, stack->operator, stack->function, stack->type);
                break;
            case Lbr:
                push(&buffStack, stack->operand, stack->operator, stack->function, stack->type);
                break;
            case Rbr:
                break;
            case function:
                push(&RPN, stack->operand, stack->operator, stack->function, stack->type);
                break;
            case exponent:
                break;
            case mult_div:
                break;
            case plus_minus:
                break;
        }
    }
}
