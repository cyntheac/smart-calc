#ifndef SRC_SOURCE_BACKEND_H_
#define SRC_SOURCE_BACKEND_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECK "xsincostansqrtlnamodlog+-()*/^1234567890., "
#define CHECK_NUM "0123456789x"
#define CHECK_FUNC "sinasincosacostanatansqrtlnmodlog"
#define CHECK_OP "+-*/^"

struct stack_for_op {
  char op;
  int priority;
  struct stack_for_op *next;
};

typedef struct stack_for_op StackOp;  // синоним структуры
typedef StackOp *StackOpPtr;

struct stack_for_num {
  double num;
  struct stack_for_num *next;
};

typedef struct stack_for_num StackNum;
typedef StackNum *StackNumPtr;

char *get_result(const char *input, int len);
char *check_input_dude();
void make_me_free(char *str);

int check_input(char *str, int len, int *div_by_zero);
char *polish_notation(char *verified_input, int len, int *flag);

int is_empty(StackOpPtr *topPtr);
void push(StackOpPtr *topPtr, char op, int priority);
int pop(StackOpPtr *topPtr);
int show_priority(StackOpPtr *topPtr);
void destroy(StackOpPtr *topPtr);

void push_num(StackNumPtr *topPtr, double num);
double pop_num(StackNumPtr *topPtr);
void destroy_num(StackNumPtr *topPtr);

char *calculate(char *polish);

#ifdef __cplusplus
}
#endif

#endif  // SRC_SOURCE_BACKEND_H_
