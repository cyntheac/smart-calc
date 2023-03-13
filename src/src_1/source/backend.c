#include "backend.h"

char *get_result(const char *str, int len) {
  if (str[len - 1] == '=') len--;
  if (len < 1) return check_input_dude();

  char *input = malloc((len + 5) * sizeof(char));
  strncpy(input, str, len);
  char *res;
  int div_by_zero = 0;

  int flag = check_input(input, len, &div_by_zero);

  if (flag) {
    if (div_by_zero) {
      res = malloc(20 * sizeof(char));
      snprintf(res, 20, "%s", "infinity");
    } else {
      char *polish_expression = polish_notation(input, len, &flag);
      //      printf("%s\n", polish_expression);
      if (!flag) {
        free(polish_expression);
        free(input);
        return check_input_dude();
      }
      res = calculate(polish_expression);
      free(polish_expression);
    }
  } else {
    res = check_input_dude();
  }

  free(input);
  return res;
}

void make_me_free(char *str) { free(str); }

char *check_input_dude() {
  char *ret = malloc(20 * sizeof(char));
  snprintf(ret, 20, "%s", "check input dude");
  return ret;
}
