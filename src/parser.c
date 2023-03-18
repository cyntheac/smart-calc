#include "main.h"

void parserLiteLexes(stackRPN* stack, char operator) {
    switch (operator) {
        case '-': push(&stack, 0, operator, plus_minus);    break;
        case '+': push(&stack, 0, operator, plus_minus);    break;
        case '/': push(&stack, 0, operator, mult_div);      break;
        case '*': push(&stack, 0, operator, mult_div);      break;
        case '^': push(&stack, 0, operator, exponent);      break;
        case '(': push(&stack, 0, operator, Lbr);           break;
        case ')': push(&stack, 0, operator, Rbr);           break;
    }
}

void parserNumbers(stackRPN* stack, char* expression, int* lenNum) {
    char buffNum[256];
    int counterLen = 0;
    while (*expression && strchr(NUMBERS, *expression)) {
        buffNum[counterLen] = *expression;
        counterLen++;
        expression++;
        buffNum[counterLen] = '\0';
    }
    lenNum = counterLen;
    push(&stack, atof(buffNum), "", number);
}

void parserElementExpression(char* expression, stackRPN* stack, bool* stackIsValid) {
    while (*expression) {
        if (strchr(NUMBERS, *expression)) {
            int* lenNum = NULL;
            parserNumbers(stack, expression, lenNum);
            expression += *lenNum;
        } else if (strchr(LITE_LEXEMES, *expression)) {
            parserLiteLexes(stack, *expression);
            expression++;
        } 
        else if (strchr(HARD_LEXEMES, *expression)) {
            int a;
        } else {
            stackIsValid = false;
            break;
        }
    }
}

void parserExpression(char* expression, stackRPN* stack) {
    bool stackIsValid = true;
    parserElementExpression(expression, stack, &stackIsValid);
    if (!stackIsValid) {
        freeStack(&stack);
    }
}
