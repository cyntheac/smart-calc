#include "s21_calc.h"
char F_ARRAY[256][256] = {"mod", "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};

int main() {
    f(EXPRESSION);
    return 0;
}

void f(char *expr) {
    stack_rpn *newNode = NULL;
    while (*expr) {
        if (strchr(NUMBERS, *expr)) {
            char buff[256];
            expr += f2(expr, NUMBERS, buff);
            const char *atof_expr = buff;
            push(&newNode, atof(atof_expr), 0, enum_number);
        } else if (strchr(LITE_LEXEMES, *expr)) {
            switch (*expr) {
            case '-': push(&newNode, 0, 1, enum_minus);             break;
            case '+': push(&newNode, 0, 1, enum_plus);              break;
            case '/': push(&newNode, 0, 2, enum_division);          break;
            case '*': push(&newNode, 0, 2, enum_multiply);          break;
            case '^': push(&newNode, 0, 3, enum_exponentiation);    break;
            case '(': push(&newNode, 0, 6, enum_Lbracket);          break;
            case ')': push(&newNode, 0, 6, enum_Rbracket);          break;
            }
            expr++;
        } else if (strchr(HARD_LEXEMES, *expr)) {
            char buff[256];
            expr += f2(expr, HARD_LEXEMES, buff);
            for (int i = 0; i < ARR_SIZE; i++) {
                const char *strA = F_ARRAY[i];
                const char *strB = buff;
                if (strstr(strA, strB)) {
                    if (i == 0)
                        push(&newNode, 0, 3, i + 7);
                    else
                        push(&newNode, 0, 4, i + 7);
                    break;
                }
            }
        } else {
            expr++;
        }
    }
    printf("VALUE:\t\t\tTYPE:\n");
    while (newNode) {
        if (newNode->type == 0)
            printf("%lf\n", newNode->value);
        else
            printf("\t\t\t%d\n", newNode->type);
        pop(&newNode);
    }
}

int f2(char *expr, char *def, char *buff) {
    int count = 0;
    while (*expr && strchr(def, *expr)) {
        buff[count] = *expr;
        count++;
        expr++;
        buff[count] = '\0';
    }
    return count;
}
