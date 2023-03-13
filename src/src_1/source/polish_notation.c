#include "backend.h"

int check_priority(unsigned char x);
void add_unary_minus(char *polish, char *verified_input, int i,
                     StackOpPtr *stack_top, int *top_polish);
void add_to_stack(char *polish, StackOpPtr *stack_top, char x, int *top_polish);
void move_ops_after_bracket(char *polish, StackOpPtr *stack_top,
                            int *top_polish);
void add_func(char *polish, StackOpPtr *stack_top, int *top_polish,
              char *verified_input, int *i, int *flag, int len);
int validate_func(char *verified_input, char *func_name, int func_len,
                  int str_len, int *i);
void add_num(char *polish, int *top_polish, int single_char, char *verified_input,
        int i, int len);

char *polish_notation(char *verified_input, int len, int *flag) {
  char *polish = malloc((len * 2) * sizeof(char));
  int top_polish = 0;
  unsigned char single_char;
  StackOpPtr stack_top = NULL;
  *flag = 1;

  for (int i = 0; (i < len) && (*flag); i++) {
    single_char = verified_input[i];
    if (single_char == '-') {
      add_unary_minus(polish, verified_input, i, &stack_top, &top_polish);

      // если число, скидываем в массив numbers
    } else if (isdigit(single_char) || single_char == '.' ||
               single_char == ',') {
      add_num(polish, &top_polish, single_char, verified_input, i, len);

    } else if (single_char == '(') {
      push(&stack_top, single_char, 0);
    } else if (single_char == ')') {
      move_ops_after_bracket(polish, &stack_top, &top_polish);

    } else if (strchr(CHECK_OP, single_char)) {  // если операция
      add_to_stack(polish, &stack_top, single_char, &top_polish);

    } else if (strchr(CHECK_FUNC, single_char)) {  // если функция
      add_func(polish, &stack_top, &top_polish, verified_input, &i, flag, len);
    } else {
      continue;
    }
  }

  // Заносим в польскую все операторы из стека
  while (!is_empty(&stack_top)) polish[top_polish++] = pop(&stack_top);
  polish[top_polish++] = '\0';

  destroy(&stack_top);
  return polish;
}

int validate_func(char *verified_input, char *func_name, int func_len,
                  int str_len, int *i) {
  int ret = 1;
  char temp[6];
  if (((*i) + func_len - 1) >= str_len) return 0;

  strncpy(temp, (verified_input + (*i)), func_len);
  if (strstr(temp, func_name))
    *i = (*i) + func_len - 1;
  else
    ret = 0;
  return ret;
}

void add_func(char *polish, StackOpPtr *stack_top, int *top_polish,
              char *verified_input, int *i, int *flag, int len) {
  char single_char = verified_input[*i];

  if (verified_input[*i] == 'a') {
    if (validate_func(verified_input, "asin", 4, len, i))
      single_char = 'a';
    else if (validate_func(verified_input, "acos", 4, len, i))
      single_char = 'b';
    else if (validate_func(verified_input, "atan", 4, len, i))
      single_char = 'd';
    else
      *flag = 0;

  } else if (verified_input[*i] == 's') {
    if (validate_func(verified_input, "sin", 3, len, i))
      single_char = 's';
    else if (validate_func(verified_input, "sqrt", 4, len, i))
      single_char = 'q';
    else
      *flag = 0;

  } else if (verified_input[*i] == 'c') {
    if (validate_func(verified_input, "cos", 3, len, i))
      single_char = 'c';
    else
      *flag = 0;

  } else if (verified_input[*i] == 't') {
    if (validate_func(verified_input, "tan", 3, len, i))
      single_char = 't';
    else
      *flag = 0;

  } else if (verified_input[*i] == 'm') {
    if (validate_func(verified_input, "mod", 3, len, i))
      single_char = 'm';
    else
      *flag = 0;

  } else if (verified_input[*i] == 'l') {
    if (validate_func(verified_input, "ln", 2, len, i))
      single_char = 'l';
    else if (validate_func(verified_input, "log", 3, len, i))
      single_char = 'g';
    else
      *flag = 0;

  } else {
    *flag = 0;
  }
  if (flag) add_to_stack(polish, stack_top, single_char, top_polish);
}

int check_priority(unsigned char x) {
  int priority;
  if (x == '+' || x == '-') {
    priority = 1;
  } else if (x == '*' || x == '/' || x == 'm') {
    priority = 2;
  } else if (x == '^') {
    priority = 5;
  } else if (x == '(') {
    priority = 0;
  } else if (x == '~') {
    priority = 4;
  } else {
    priority = 3;
  }
  return priority;
}

void add_unary_minus(char *polish, char *verified_input, int i,
                     StackOpPtr *stack_top, int *top_polish) {
  if (i == 0) {
    add_to_stack(polish, stack_top, '~', top_polish);

  } else if ((isdigit(verified_input[i - 1]) == 0) &&
             (verified_input[i - 1] != ')')) {
    add_to_stack(polish, stack_top, '~', top_polish);
  } else {
    add_to_stack(polish, stack_top, '-', top_polish);
  }
}

void add_to_stack(char *polish, StackOpPtr *stack_top, char x,
                  int *top_polish) {
  int priority = check_priority(x);
  if (is_empty(stack_top)) {  // начало стека операторов
    push(stack_top, x, priority);

  } else if (priority > show_priority(stack_top)) {
    // приоритет больше чем у предыдущего оператора
    push(stack_top, x, priority);

  } else {
    // приоритет меньше или равен предыдущему оператору
    if (*top_polish == 0) {
      push(stack_top, x, priority);

    } else {
      while (!(is_empty(stack_top)) && (priority <= show_priority(stack_top))) {
        polish[*top_polish] = pop(stack_top);
        (*top_polish)++;
      }
      push(stack_top, x, priority);
    }
  }
}

void move_ops_after_bracket(char *polish, StackOpPtr *stack_top,
                            int *top_polish) {
  char temp;
  if (!is_empty(stack_top)) {
    while ((temp = pop(stack_top)) != '(') {
      polish[*top_polish] = temp;
      (*top_polish)++;
    }
  }
}

void add_num(char *polish, int *top_polish, int single_char, char *verified_input,
        int i, int len) {
  if (isdigit(single_char)) {
    polish[*top_polish] = single_char;
    (*top_polish)++;
  } else {
    polish[*top_polish] = '.';
    (*top_polish)++;
  }

  if (i < (len - 1)) {
    if ((isdigit(verified_input[i + 1]) == 0) &&
        (verified_input[i + 1] != '.') && (verified_input[i + 1] != ',')) {
      polish[*top_polish] = ' ';
      (*top_polish)++;
    }
  }
}
