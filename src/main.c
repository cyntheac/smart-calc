#include <stdio.h>
#include <string.h>

#define NUMBERS "0123456789"
#define LITE_LEXEMES "+-*/^()"

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

void translationRPN(char* expression, stackRPN* RPN);
void calculationRPN(stackRPN* RPN);
bool IsEmptyRPN(stackRPN* RPN);



int main() {
    char* expression = NULL;
    stackRPN* RPN = NULL;
    scanf("%s", expression);
    translationRPN(expression, RPN);
    if (IsEmptyRPN(RPN)) {
        calculationRPN(RPN);
    }

    return 0;
}


void translationRPN(char* expression, stackRPN* RPN) {
    stackRPN* stack = NULL;
    stackRPN* buffer = NULL;
    while(*expression) {
        switch (*expression) {
            case '-': push(&buffer, 0, *expression, plus_minus);    break;
            case '+': push(&buffer, 0, *expression, plus_minus);    break;
            case '/': push(&buffer, 0, *expression, mult_div);      break;
            case '*': push(&buffer, 0, *expression, mult_div);      break;
            case '^': push(&buffer, 0, *expression, exponent);      break;
            case '(': push(&buffer, 0, *expression, Lbr);           break;
            case ')': push(&buffer, 0, *expression, Rbr);           break;
        }
        if (strchr(NUMBERS, *expression)) {
            
        }
    }
    // чистка памяти
    while (stack != NULL) {
        pop(&stack);
    }
    while (buffer != NULL) {
        pop(&buffer);
    }
}

void calculationRPN(stackRPN* RPN) {

}

bool IsEmptyRPN(stackRPN* RPN) {
    return RPN == NULL;
}
