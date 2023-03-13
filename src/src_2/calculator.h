#ifndef SRC_SOURCE_CALCULATOR_H_
#define SRC_SOURCE_CALCULATOR_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  char function;
  double number;
  struct stack *down;
} Stack;

#define INCORRECT_EXPRESSION 1
#define LINE_IS_TOO_LONG 2
#define BINARY_OP 2
#define UNARY_OP 1

int compute(const char *str, char *str_result, double X);
int rename_operands(const char *str, char *temp_result);
int is_function(char n);
double calculate(char op, double a, double b);
int priority(char function);
int postfix(char *str, double X);
double result(Stack **postfix_stack, Stack **empty_stack, int *error_flag);

// Stack
void push(Stack **top, double number, char function);
char pop(Stack **top);  //поменять тип
int is_empty(Stack const *top);

// Credit/deposit
int credit(double obsh, int month, double proc, int type, char *monthly_payment,
           char *overpayment, char *full_payment);
int deposit(double *obsh, int month, double proc, double *tax_rate,
            int capitalization, int payment_periods,
            const double *replanishment, double *interest_income);

#endif  // SRC_SOURCE_CALCULATOR_H_
