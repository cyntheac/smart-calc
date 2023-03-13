#include "calculator.h"

int deposit(double *obsh, int month, double proc, double *tax_rate,
            int capitalization, int payment_periods,
            const double *replanishment, double *interest_income) {
  if (payment_periods == 0) {
    return 1;  // ошибка - выберите тип
  }
  double monthly_profit = 0;
  if (!capitalization) {  // если нет капитализации
    for (int i = 0; i < month; i++) {
      *obsh = *obsh + replanishment[i];
      if (*obsh < 0) {
        return 2;  // снятие больше чем есть
      }
      monthly_profit = *obsh * proc / 1200;
      *interest_income = *interest_income +
                         monthly_profit;  // это надо вернуть!! цикл здесь нужен
                                          // потому что могут быть доп взносы
    }
    *obsh = *obsh + *interest_income;  //проверить переменные
    *tax_rate = *interest_income * *tax_rate / 100;
  } else {
    if (payment_periods ==
        1) {  // если есть ежемесячная капитализация и cнятие в конце срока
      for (int i = 0; i < month; i++) {
        *obsh = *obsh + replanishment[i] + monthly_profit;
        if (*obsh < 0) {
          return 2;  // снятие больше чем есть
        }
        monthly_profit = *obsh * proc / 1200;
        *interest_income = *interest_income + monthly_profit;
      }
      *obsh =
          *obsh + monthly_profit;  //проверить переменные // спросить у Наташи??
      *tax_rate = *interest_income * *tax_rate / 100;
    } else if (payment_periods == 2) {  //каждый месяц снятие
      for (int i = 0; i < month; i++) {
        *obsh = *obsh + replanishment[i];
        if (*obsh < 0) {
          return 2;  // снятие больше чем есть
        }
        monthly_profit = *obsh * proc / 1200;
        *interest_income = *interest_income + monthly_profit;
      }
      *obsh = *obsh + *interest_income;  // проверить переменные
      *tax_rate = *interest_income * *tax_rate / 100;
    }
  }
  // Вывод - сумма налога tax_rate, начисленные проценты interest_rate, сумма на
  // вкладе к концу срока obsh
  return 0;
}