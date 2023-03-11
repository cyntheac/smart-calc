#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EXPRESSION "cos(101.42+2)+3+4*5*sin(6^74)+4mod10"
#define NUMBERS "0123456789."
#define LITE_LEXEMES "+-*/^()"
#define HARD_LEXEMES "cosintaqrlg"
#define ARR_SIZE 10

typedef enum { enum_number          = 0, enum_x               = 1, 
                enum_plus           = 2, enum_minus           = 3, 
                enum_multiply       = 4, enum_division        = 5, 
                enum_exponentiation = 6, enum_modulo          = 7, 
                enum_cos            = 8, enum_sin             = 9, 
                enum_tan            = 10, enum_acos           = 11, 
                enum_asin           = 12, enum_atan           = 13, 
                enum_sqrt           = 14, enum_ln             = 15, 
                enum_log            = 16, enum_Lbracket       = 17,
                enum_Rbracket = 18 } type_t;

typedef struct stack_test {
    double value;
    int priority;
    type_t type;
    struct stack_test *NEXT;
} stack_rpn;

stack_rpn *createNode(double value, int priority, type_t type);
void push(stack_rpn **stack, double value, int priority, type_t type);
void pop(stack_rpn **stack);
void f(char *expr);
int f2(char *expr, char *def, char *buff);

#endif  // SRC_S21_MATRIX_H_