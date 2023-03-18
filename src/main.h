#ifndef SRC_MAIN_
#define SRC_MAIN_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBERS "0123456789."
#define LITE_LEXEMES "+-*/^()"
#define HARD_LEXEMES "cos sin tan acos asin atan sqrt ln log"

typedef enum {false, true} bool;
typedef enum {number, Lbr, Rbr, exponent, mult_div, plus_minus} type_priority;

typedef struct stack_for_RPN {
    double operand;
    char operator;
    type_priority type;
    struct stack_for_RPN* next;
} stackRPN;

stackRPN *createNode(double operand, char operator, type_priority type);
void push(stackRPN **stack, double operand, char operator, type_priority type);
void pop(stackRPN **stack);
void freeStack(stackRPN **stack);

void parserExpression(char* expression, stackRPN* RPN);
void translationRPN(stackRPN* stack, stackRPN* RPN);
void calculationRPN(stackRPN* RPN);
bool StackIsEmpty(stackRPN* stack);

#endif  // SRC_MAIN_