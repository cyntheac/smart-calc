#ifndef SRC_MAIN_
#define SRC_MAIN_

// библиотеки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// константы
#define NUMBERS "0123456789."
#define LITE_LEXEMES "+-*/^()"
#define HARD_LEXEMES "cosintaqrlg~"
#define FUNCTIONS "cos_sin_tan_acos_asin_atan_sqrt_ln_log_~"

// описание собственных типов
typedef enum {false, true} bool;
typedef enum {number, Lbr, Rbr, function, exponent, mult_div, plus_minus} type_priority;
typedef struct stack_for_RPN {
    double operand;
    char operator;
    char* function;
    type_priority type;
    struct stack_for_RPN* next;
} stackRPN;

// подпрограммы стека
// stackRPN *createNode(double operand, char operator, char* function, type_priority type);
void push(stackRPN **stack, double operand, char operator, char* function, type_priority type);
void pop(stackRPN **stack);
void freeStack(stackRPN **stack);
bool stackIsEmpty(stackRPN* stack);

// подрограммы парсера
// void parserHardLexes(stackRPN** stack, char* expression, int* lenLex, bool* validLex);
// void parserLiteLexes(stackRPN** stack, char operator);
// void parserNumbers(stackRPN** stack, char* expression, int* lenNum);
// void parserElementExpression(char* expression, stackRPN** stack, bool* stackIsValid);
void parserExpression(char* expression, stackRPN** RPN);

// подпрограммы перевода в ОПН
void translationRPN(stackRPN* stack, stackRPN* RPN);

// подпрограммы калькулятора ОПН
void calculationRPN(stackRPN* RPN);


#endif  // SRC_MAIN_
