#include "backend.h"

int len_of_num(char *polish, int len, int i);
double get_res(double first, double second, char char_from_stack);
double get_unary_res(double first, char char_from_stack);
char *get_final_string(double res);

char *calculate(char *polish) {
  setlocale(LC_ALL, "en_US.UTF-8");
  StackNumPtr stack_top = NULL;
  char *ret;
  double first, second, res;
  int len = strlen(polish);
  int num_len;
  char *ptr_helper;
  char char_from_stack;

  for (int i = 0; i < len;) {
    char_from_stack = polish[i];
    if (isdigit(char_from_stack)) {
      num_len = len_of_num(polish, len, i);
      res = strtod((polish + i), &ptr_helper);
      push_num(&stack_top, res);
      i += num_len;
    } else if (strchr(CHECK_OP, char_from_stack) || (char_from_stack == 'm')) {
      second = pop_num(&stack_top);
      first = pop_num(&stack_top);
      res = get_res(first, second, char_from_stack);
      push_num(&stack_top, res);
      i++;
    } else if (char_from_stack == ' ') {
      i++;
      continue;
    } else {
      first = pop_num(&stack_top);
      res = get_unary_res(first, char_from_stack);
      push_num(&stack_top, res);
      i++;
    }
  }

  res = pop_num(&stack_top);
  destroy_num(&stack_top);
  ret = get_final_string(res);
  return ret;
}

char *get_final_string(double res) {
  char *ret = malloc(255 * sizeof(char));
  double helper = fabs(res);
  if ((helper - (long int)helper) < 1e-6) {
    snprintf(ret, 255, "%ld", (long int)res);
  } else {
    snprintf(ret, 255, "%lf", res);
  }
  return ret;
}

double get_unary_res(double first, char char_from_stack) {
  if (char_from_stack == 'a') return asin(first);
  if (char_from_stack == 'b') return acos(first);
  if (char_from_stack == 'd') return atan(first);
  if (char_from_stack == 's') return sin(first);
  if (char_from_stack == 'q') return sqrt(first);
  if (char_from_stack == 'c') return cos(first);
  if (char_from_stack == 't') return tan(first);
  if (char_from_stack == 'l') return log(first);
  if (char_from_stack == 'g') return log10(first);
  if (char_from_stack == '~') return -first;
  return 0;
}

double get_res(double first, double second, char char_from_stack) {
  if (char_from_stack == '+') return (first + second);
  if (char_from_stack == '-') return (first - second);
  if (char_from_stack == '*') return (first * second);
  if (char_from_stack == '/') return (first / second);
  if (char_from_stack == '^') return (pow(first, second));
  if (char_from_stack == 'm') return (fmod(first, second));
  return 0;
}

int len_of_num(char *polish, int len, int i) {
  int counter = 0;
  while (1) {
    if ((*(polish + i) == ' ') || (i >= (len - 1)) ||
        ((isdigit(*(polish + i)) == 0) && (*(polish + i) != '.')))
      break;
    i++;
    counter++;
  }
  return counter;
}
