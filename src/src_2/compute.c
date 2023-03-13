#include "calculator.h"

void push(Stack **top, double number, char function) {
  Stack *up = malloc(sizeof(Stack));
  if (up != NULL) {
    up->function = function;  //если мы пушим число, то оператор 0, и наоборот
    up->number = number;
    up->down = *top;
    *top = up;
  } else {
    printf("Error malloc");
  }
}

char pop(Stack **top) {
  Stack *temp = *top;
  //   double number = (*top)->number;
  char function = (*top)->function;
  *top = (*top)->down;
  free(temp);

  return function;
}

int is_empty(Stack const *top) { return top == NULL; }

int is_function(char n) {
  if (n == '%' || n == '+' || n == '-' || n == '*' || n == '/' || n == '^') {
    return BINARY_OP;
  } else if (n == 's' || n == 'c' || n == 't' || n == 'a' || n == 'b' ||
             n == 'd' || n == 'l' || n == 'g' || n == 'q' || n == '~' ||
             n == '@') {
    return UNARY_OP;
  } else {
    return 0;
  }
}

int priority(char function) {
  int priority = -2;
  if (function == '+' || function == '-') {
    priority = 0;
  } else if (function == '*' || function == '/' || function == '%') {
    priority = 1;
  } else if (function == 's' || function == 'c' || function == 't' ||
             function == 'a' || function == 'b' || function == 'd' ||
             function == 'l' || function == 'g' || function == 'q' ||
             function == '~' || function == '@') {
    priority = 3;
  } else if (function == '^') {
    priority = 4;
  } else if (function == '(') {
    priority = -1;
  }
  return priority;
}

double calculate(char op, double a, double b) {
  double result_value = 0;
  if (op == '+') {
    result_value = a + b;
  } else if (op == '-') {
    result_value = a - b;
  } else if (op == '*') {
    result_value = a * b;
  } else if (op == '/') {
    result_value = a / b;
  } else if (op == '^') {
    result_value = pow(a, b);
  } else if (op == '%') {
    result_value = fmod(a, b);
  } else if (op == '~') {
    result_value = -a;
  } else if (op == 'c') {
    result_value = cos(a);
  } else if (op == 's') {
    result_value = sin(a);
  } else if (op == 't') {
    result_value = tan(a);
  } else if (op == 'a') {
    result_value = asin(a);
  } else if (op == 'b') {
    result_value = acos(a);
  } else if (op == 'd') {
    result_value = atan(a);
  } else if (op == 'q') {
    result_value = sqrt(a);
  } else if (op == 'l') {
    result_value = (double)logl(a);
  } else if (op == 'g') {
    result_value = (double)log10l(a);
  }
  return result_value;
}

double result(Stack **postfix_stack, Stack **empty_stack, int *error_flag) {
  double a;
  double b;
  double result = 0;
  while (!is_empty(*postfix_stack)) {
    if ((*postfix_stack)->function == ')' ||
        (*postfix_stack)->function == '(') {
      *error_flag = 2;
      return INCORRECT_EXPRESSION;
    }

    if ((*postfix_stack)->function == 0) {
      push(empty_stack, (*postfix_stack)->number, 0);
      pop(postfix_stack);
    } else {
      if (is_function((*postfix_stack)->function) == 2) {
        if (!is_empty(*empty_stack)) {
          b = (*empty_stack)->number;
          pop(empty_stack);
          if (!is_empty(*empty_stack)) {
            a = (*empty_stack)->number;
            pop(empty_stack);
            push(empty_stack, calculate((*postfix_stack)->function, a, b), 0);
            pop(postfix_stack);
          } else {
            *error_flag = 1;
            return INCORRECT_EXPRESSION;
          }
        } else {
          *error_flag = 1;
          return INCORRECT_EXPRESSION;
        }
      } else if (is_function((*postfix_stack)->function) == 1) {
        if (!is_empty(*empty_stack)) {
          a = (*empty_stack)->number;
          pop(empty_stack);
          push(empty_stack, calculate((*postfix_stack)->function, a, 0), 0);
          pop(postfix_stack);
        } else {
          *error_flag = 1;
          return INCORRECT_EXPRESSION;
        }
      }
    }
  }
  result = (*empty_stack)->number;
  return result;
}

int postfix(char *str, double X) {
  Stack *operator_stack = NULL;
  Stack *number_stack = NULL;
  char number[270] = {'\0'};
  int error_flag = 0;
  int i = 0;
  int k = 0;
  while (str[i]) {
    if ((str[i] >= 48 && str[i] <= 59) || str[i] == '.') {
      while ((str[i] >= 48 && str[i] <= 59) || str[i] == '.') {
        number[k] = str[i];
        k++;
        i++;
      }
      number[k] = '\0';
      push(&number_stack, atof(number), 0);
      memset(number, '\0', sizeof(number));
      k = 0;
    } else if (str[i] == 'x') {
      i++;
      push(&number_stack, X, 0);
    } else if (str[i] == '(') {
      push(&operator_stack, 0, str[i]);
      i++;
    } else if (is_function(str[i]) == 2) {
      if (is_empty(operator_stack) ||
          (str[i] == '^' && operator_stack->function == '^')) {
        push(&operator_stack, 0, str[i]);
        i++;
      } else if (is_empty(operator_stack) ||
                 priority(str[i]) > priority(operator_stack->function)) {
        push(&operator_stack, 0, str[i]);
        i++;
      } else {
        while (!is_empty(operator_stack) &&
               priority(str[i]) <= priority(operator_stack->function)) {
          push(&number_stack, 0, operator_stack->function);
          pop(&operator_stack);
        }
        if (is_empty(operator_stack) ||
            priority(str[i]) > priority(operator_stack->function)) {
          push(&operator_stack, 0, str[i]);
        }
        i++;
      }
    } else if (is_function(str[i]) == 1) {
      push(&operator_stack, 0, str[i]);
      i++;
    } else if (str[i] == ')') {
      while (!is_empty(operator_stack) && operator_stack->function != '(') {
        push(&number_stack, 0, operator_stack->function);
        pop(&operator_stack);
      }
      if (is_empty(operator_stack)) {
        free(operator_stack);
        free(number_stack);
        return INCORRECT_EXPRESSION;  //ошибка скобок
      } else if (operator_stack->function == '(') {
        pop(&operator_stack);
      }
      i++;
    } else if (str[i] == ' ') {
      i++;
    }
  }
  if (str[i] == '\0') {
    while (!is_empty(number_stack)) {
      push(&operator_stack, number_stack->number, number_stack->function);
      pop(&number_stack);
    }
  }
  double res = result(&operator_stack, &number_stack, &error_flag);
  if (error_flag == 1) {
    strcpy(str, "INCORRECT EXPRESSION");
  } else if (error_flag == 2) {
    strcpy(str, "PARENTHESES ERROR");
  } else {
    sprintf(str, "%.7f", res);
  }
  free(operator_stack);
  free(number_stack);
  return 0;
}

int rename_operands(const char *str, char *temp_result) {
  char temp[260];
  int len = strlen(str);
  int i = 0;
  int k = 0;
  if (len > 255) {
    return LINE_IS_TOO_LONG;
  } else if (len == 1 && str[len - 1] != 'x' &&
             (str[len - 1] < '0' || str[len - 1] > '9'))
    return INCORRECT_EXPRESSION;
  else if ((len == 1 && str[len - 1] >= '0' && str[len - 1] <= '9') ||
           str[len - 1] == 'x') {
    ;
  } else if (str[len - 1] != ')' &&
             (str[len - 1] >= 'a' &&
              str[len - 1] <= 'z'))  // убрала (&& str[len - 1] != 'x')
    return INCORRECT_EXPRESSION;
  while (i <= len) {
    if (str[i] == 'm') {  // mod = m
      temp[k] = '%';
      i = i + 3;
      k++;
    }

    if (str[i] == 's' && str[i + 1] == 'i') {  // sin = s
      temp[k] = 's';
      i = i + 3;
      k++;
    }

    if (str[i] == 'c') {  // cos = c
      temp[k] = 'c';
      i = i + 3;
      k++;
    }

    if (str[i] == 't') {  // tan - t
      temp[k] = 't';
      i = i + 3;
      k++;
    }

    if (str[i] == 'a' && str[i + 1] == 's') {  // asin = a
      temp[k] = 'a';
      i = i + 4;
      k++;
    }

    if (str[i] == 'a' && str[i + 1] == 'c') {  // acos = b
      temp[k] = 'b';
      i = i + 4;
      k++;
    }

    if (str[i] == 'a' && str[i + 1] == 't') {  // atan = d
      temp[k] = 'd';
      i = i + 4;
      k++;
    }

    if (str[i] == 'l' && str[i + 1] == 'n') {  // ln = l
      temp[k] = 'l';
      i = i + 2;
      k++;
    }

    if (str[i] == 'l' && str[i + 1] == 'o') {  // log = g
      temp[k] = 'g';
      i = i + 3;
      k++;
    }

    if (str[i] == 's' && str[i + 1] == 'q') {  // sqrt = q
      temp[k] = 'q';
      i = i + 4;
      k++;
    }

    if (str[i] < 97 || str[i] > 122 || str[i] == 'x') {
      temp[k] = str[i];
      i++;
      k++;
    }
  }
  i = k;
  k = 0;
  while (k <= i) {
    if (temp[k] == '-') {
      if ((k >= 2 && is_function(temp[k - 2])) &&
          (!is_function(temp[k - 1]) && temp[k - 1] != '('))
        temp[k] = '-';
      else if (k == 0 || temp[k - 1] == '(' ||
               (k >= 2 && is_function(temp[k - 2])))  // == 2
      {
        temp[k] = '~';
      }
    }
    k++;
  }
  temp[k] = '\0';
  strcpy(temp_result, temp);
  return 0;
}

int compute(const char *str, char *str_result, double X) {
  char temp_result[260] = "\0";
  int error = 0;
  error = rename_operands(str, temp_result);
  if (error == 1) {
    strcpy(temp_result, "INCORRECT EXPRESSION");
  } else if (error == 2) {
    strcpy(temp_result, "LINE IS TOO LONG");
  } else if (str[0] != 'x' && is_function(str[0] == 2))
    strcpy(temp_result, "INCORRECT EXPRESSION");
  else if (postfix(temp_result, X) == INCORRECT_EXPRESSION)
    strcpy(temp_result, "PARENTHESES ERROR");
  else if (strcmp(temp_result, "nan") == 0 || strcmp(temp_result, "inf") == 0 ||
           strcmp(temp_result, "-inf") == 0)
    strcpy(temp_result, "INCORRECT EXPRESSION");
  strcpy(str_result, temp_result);
  return (0);
}

// int main(void) {
//     const char str[200] = "-1+8";
//     char result[200];
//     compute(str, result, 0);
//     printf(result);
// }