#include "backend.h"

int check_op(char *str, int len);
int check_ops_and_brackets(char *str, int len);
int check_div_by_zero(char *str, int len);
int check_funcs(char *str, int len);

int check_input(char *str, int len, int *div_by_zero) {
  int ret = 1;
  for (int i = 0; (i < len) && ret; i++) {
    if (strchr(CHECK, str[i]) == NULL) ret = 0;
  }
  if (ret) ret = check_op(str, len);
  if (ret) ret = check_ops_and_brackets(str, len);
  if (ret) ret = check_funcs(str, len);
  if (ret) *div_by_zero = check_div_by_zero(str, len);
  return ret;
}

int check_op(char *str, int len) {
  int ret = 1;
  if (strchr(CHECK_OP, (int)str[0]) && (str[0] != '-')) {
    ret = 0;
  }
  if (strchr(CHECK_OP, str[len - 1])) {
    ret = 0;
  }
  if (strchr(CHECK_FUNC, str[len - 1])) {
    ret = 0;
  }
  if (str[0] == ')' || str[len - 1] == '(') {
    ret = 0;
  }
  return ret;
}

int check_ops_and_brackets(char *str, int len) {
  int ret = 1;
  int open_bracket = 0, close_bracket = 0;

  for (int i = 0; (i < len - 1) && ret; i++) {
    if (strchr(CHECK_OP, (int)str[i]) && strchr(CHECK_OP, (int)str[i + 1])) {
      ret = 0;
      if (str[i + 1] == '-') ret = 1;
    }
    if (strchr(CHECK_NUM, (int)str[i]) && (str[i + 1] == '(')) {
      ret = 0;
    }
    if (strchr(CHECK_NUM, (int)str[i + 1]) && (str[i] == ')')) {
      ret = 0;
    }
    if ((str[i] == ')' && str[i + 1] == '(') ||
        (str[i] == '(' && str[i + 1] == ')')) {
      ret = 0;
    }
    if ((strchr(CHECK_OP, (int)str[i]) && str[i + 1] == ')') ||
        ((strchr(CHECK_OP, (int)str[i + 1]) && str[i + 1] != '-') &&
         str[i] == '(')) {
      ret = 0;
    }
    if (str[i] == '(') open_bracket++;
    if (str[i] == ')') close_bracket++;
  }

  if (str[len - 1] == '(') open_bracket++;
  if (str[len - 1] == ')') close_bracket++;
  if (open_bracket != close_bracket) ret = 0;
  return ret;
}

int check_div_by_zero(char *str, int len) {
  int ret = 0;
  int warn = 0;
  for (int i = 0; (i < len) && (ret == 0); i++) {
    if (str[i] == '/') {
      warn++;
    } else if (warn) {
      if (str[i] == ' ')
        continue;
      else if (str[i] == '0')
        ret++;
      else
        warn = 0;
    }
  }
  return ret;
}

int check_funcs(char *str, int len) {
  int ret = 1;
  for (int i = 0; (i < len - 1) && ret; i++) {
    if ((str[i] == 'n' || str[i] == 'g') && str[i + 1] != '(') {
      ret = 0;
    }
    if (str[i] == 'd' &&
        (str[i + 1] == '(' || (strchr(CHECK_NUM, str[i + 1]) == NULL))) {
      ret = 0;
    }
    if ((str[i + 1] == 'q' || str[i + 1] == 'i') && str[i] != 's') {
      ret = 0;
    }
    if (str[i] == 'i' && str[i + 1] != 'n') {
      ret = 0;
    }
    if (str[i] == 'm' && str[i + 1] != 'o') {
      ret = 0;
    }
    if (str[i] == 'c' && str[i + 1] != 'o') {
      ret = 0;
    }
    if (str[i] == 'o' && (strchr("sdg", str[i + 1])) == NULL) {
      ret = 0;
    }
    if (str[i] == 's' && (strchr("q(i", str[i + 1])) == NULL) {
      ret = 0;
    }
    if (str[i] == 't' && (strchr("a(", str[i + 1])) == NULL) {
      ret = 0;
    }
    if (str[i] == 'a' && (strchr("nsct", str[i + 1])) == NULL) {
      ret = 0;
    }
    if (str[i] == 'q' && str[i + 1] != 'r') {
      ret = 0;
    }
    if (str[i] == 'r' && str[i + 1] != 't') {
      ret = 0;
    }
    if (str[i] == 'l' && (strchr("no", str[i + 1])) == NULL) {
      ret = 0;
    }
  }
  return ret;
}
