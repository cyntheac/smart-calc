#include "main.h"


void initBuff(char* buff, char* expression, char* category, int* lenElement) {
    int counterLen = 0;
    while (*expression && strchr(category, *expression)) {
        buff[counterLen] = *expression;
        counterLen++;
        expression++;
    }
    buff[counterLen] = '\0';
    *lenElement = counterLen;
}

void parserHardLexes(stackRPN** stack, char* expression, int* lenLex, bool* validLex) {
    char buffLex[256];
    initBuff(buffLex, expression, HARD_LEXEMES, lenLex);
    if (strstr(FUNCTIONS, buffLex)) {
        push(stack, 0, ' ', buffLex, function);
    } else {
        printf("ss\n");
        *validLex = false;
    }
}

void parserLiteLexes(stackRPN** stack, char operator) {
    switch (operator) {
        case '-': push(stack, 0, operator, NULL, plus_minus);    break;
        case '+': push(stack, 0, operator, NULL, plus_minus);    break;
        case '/': push(stack, 0, operator, NULL, mult_div);      break;
        case '*': push(stack, 0, operator, NULL, mult_div);      break;
        case '^': push(stack, 0, operator, NULL, exponent);      break;
        case '(': push(stack, 0, operator, NULL, Lbr);           break;
        case ')': push(stack, 0, operator, NULL, Rbr);           break;
    }
}

void parserNumbers(stackRPN** stack, char* expression, int* lenNum) {
    char buffNum[256];
    initBuff(buffNum, expression, NUMBERS, lenNum);
    push(stack, atof(buffNum), ' ', NULL, number);
}

void parserElementExpression(char* expression, stackRPN** stack, bool* stackIsValid) {
    while (*expression && *stackIsValid) {
        int lenElement = 1;
        if (strchr(NUMBERS, *expression)) {
            parserNumbers(stack, expression, &lenElement);
        } else if (strchr(LITE_LEXEMES, *expression)) {
            parserLiteLexes(stack, *expression);
        } else if (strchr(HARD_LEXEMES, *expression)) {
            parserHardLexes(stack, expression, &lenElement, stackIsValid);
        } else {
            *stackIsValid = false;
        }
        expression += lenElement;
    }
}

void parserExpression(char* expression, stackRPN** stack) {
    bool stackIsValid = true;
    parserElementExpression(expression, stack, &stackIsValid);
    if (!stackIsValid) {
        freeStack(stack);
    }
}
