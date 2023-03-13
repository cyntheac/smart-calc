#include "calculator.h"

int credit(double obsh, int month, double proc, int type, char *monthly_payment,
           char *overpayment, char *full_payment) {
  double full_payment_res;
  double overpayment_res = 0;
  memset(monthly_payment, '\0', 50);
  memset(overpayment, '\0', 50);
  memset(full_payment, '\0', 50);
  if (obsh < 0 || month < 0 || proc < 0) {
    return 2;
  }
  if (type == 0) {
    return 1;
  } else if (type == 1) {  // annuit
    double i = (proc / 100) / 12;
    double k = (i * (pow((1 + i), month)) / (pow((1 + i), month) - 1));
    double monthly_payment_osn = k * obsh;
    sprintf(monthly_payment, "%f", monthly_payment_osn);
    full_payment_res = monthly_payment_osn * month;
    overpayment_res = full_payment_res - obsh;
    sprintf(full_payment, "%0.2f", full_payment_res);
    sprintf(overpayment, "%0.2f", overpayment_res);
  } else if (type == 2) {  // differentiated
    double monthly_osn = obsh / month;
    for (int i = 0; i < month; i++) {
      double monthly_proc =
          (obsh - (i * monthly_osn)) * (proc / 100) * 30.4 / 365;
      overpayment_res = overpayment_res + monthly_proc;
    }
    double monthly_proc_max = (obsh * (proc / 100) * 31 / 365) + obsh / month;
    double monthly_proc_min =
        monthly_osn * (proc / 100) * 31 / 365 + obsh / month;
    full_payment_res = obsh + overpayment_res;
    sprintf(monthly_payment, "%0.2f...%0.2f", monthly_proc_max,
            monthly_proc_min);
    sprintf(full_payment, "%0.2f", full_payment_res);
    sprintf(overpayment, "%0.2f", overpayment_res);
  }
  return 0;
}