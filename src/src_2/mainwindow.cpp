#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "x_exist.h"
#include <QDebug>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits() {
  QString new_label = ui->result_show->text();
  int len = new_label.length();
  if (len >= 2) {
    if (new_label[len - 2] == 'x') {
      new_label = new_label + "* ";
      ui->result_show->setText(new_label + " *");
    }
  }

  QPushButton *button = (QPushButton *)sender();
  new_label = (new_label + button->text());
  ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked() {
  QString number;
  int i, k = 0, len = ui->result_show->text().length();
  number.resize(len + 1);

  for (i = len - 1; i >= 0; i--) {
    number[k++] = ui->result_show->text()[i];
    if (ui->result_show->text()[i] == ' ' ||
        ui->result_show->text()[i] == '(') {
      number[k++] = '\0';
      break;
    }
  }

  if (!(number.contains('.')))
    ui->result_show->setText(ui->result_show->text() + ".");
  number.clear();
}

void MainWindow::on_pushButtonSkobkaOtkr_clicked() {
  QString str = ui->result_show->text();
  int len = str.length();
  if (len > 0) {
    if (str[len - 1] <= '9' && str[len - 1] >= '0') {
      ui->result_show->setText(ui->result_show->text() + " *(");
    } else if (len > 1 && str[len - 2] == 'x') {
      ui->result_show->setText(ui->result_show->text() + "*(");
    } else
      ui->result_show->setText(ui->result_show->text() + "(");
  } else
    ui->result_show->setText(ui->result_show->text() + "(");
}

void MainWindow::on_pushButtonAC_clicked() { ui->result_show->setText(""); }

void MainWindow::on_pushButtonSkobkaZakr_clicked() {
  ui->result_show->setText(ui->result_show->text() + ")");
}

void MainWindow::on_pushButtonClear_clicked() {
  QString str = ui->result_show->text();
  int len = str.length();
  if (str == "INCORRECT EXPRESSION" || str == "LINE IS TOO LONG" ||
      str == "PARENTHESES ERROR") {
    str = "";
  } else if (len > 0 && (str[len - 1] == '(' || str[len - 1] == ' ')) {
    if (str[len - 1] == ' ' || str[len - 1] == '(') {
      str.chop(1);
      len = str.length();
    }
    while (len > 0 && str[len - 1] != ' ' && str[len - 1] != '(' &&
           str[len - 1] != '+' && str[len - 1] != '-') {
      str.chop(1);
      len = str.length();
    }
  } else {
    str.chop(1);
  }
  ui->result_show->setText(str);
  str.clear();
}

int MainWindow::replace() {
  QString str = ui->result_show->text();
  int len = str.length();

  if (len == 0) {
    return 0;
  }

  QChar ch_a = 'a';
  QChar ch_z = 'z';
  QChar ch_x = 'x';

  if (len > 0 && ('0' > str[len - 1] || str[len - 1] > '9')) {
    if (len > 2 && str[len - 1] == ' ' &&
        (str[len - 2] == '*' || str[len - 2] == '+' || str[len - 2] == '-' ||
         str[len - 2] == '/' || str[len - 2] == '^')) {
      str.chop(3);
    } else if (len > 3) {
      if (str[len - 1] == ' ' && str[len - 2] >= ch_a && str[len - 2] <= ch_z &&
          str[len - 2] != ch_x) {
        str.chop(1);
        len = len - 1;
        while (str[len - 1] != ' ' && len != 0) {
          str.chop(1);
          len = len - 1;
        }
        str.chop(1);
      }
    } else if (str[len - 1] == '(' && str[len - 2] == ' ') {
      str.chop(2);
      len = len - 1;
      while (str[len - 1] != ' ' && len != 0) {
        str.chop(1);
        len = len - 1;
      }
      str.chop(1);
    }
    ui->result_show->setText(str);
  }
  return 0;
}

int MainWindow::mul_x() {
  QString str = ui->result_show->text();
  int len = str.length();
  if (len == 0) {
    return 0;
  }
  QChar ch_x = 'x';
  if (len > 1 && str[len - 2] == ch_x) {
    ui->result_show->setText(ui->result_show->text() + "*");
  }
  if (len >= 1) {
    if (str[len - 1] >= '0' && str[len - 1] <= '9') {
      ui->result_show->setText(ui->result_show->text() + " *");
    }
  }
  return 0;
}

int MainWindow::check_operat() {
  QString str = ui->result_show->text();
  int len = str.length();
  if (len == 0) {
    return 0;
  } else if (len >= 2 && (str[len - 2] == '*' || str[len - 2] == '+' ||
                          str[len - 2] == '-' || str[len - 2] == '/' ||
                          str[len - 2] == '^' || str[len - 2] == 'd')) {
    str.chop(1);
    ui->result_show->setText(str);
    return 1;
  }
  return 0;
}

void MainWindow::on_pushButton_div_clicked() {
  replace();
  ui->result_show->setText(ui->result_show->text() + " / ");
}

void MainWindow::on_pushButton_mul_clicked() {
  replace();
  ui->result_show->setText(ui->result_show->text() + " * ");
}

void MainWindow::on_pushButton_sub_clicked() {
  replace();
  ui->result_show->setText(ui->result_show->text() + " - ");
}

void MainWindow::on_pushButton_add_clicked() {
  replace();
  ui->result_show->setText(ui->result_show->text() + " + ");
}

void MainWindow::on_pushButton_mod_clicked() {
  replace();
  ui->result_show->setText(ui->result_show->text() + " mod ");
}

void MainWindow::on_pushButton_ln_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " ln ");
}

void MainWindow::on_pushButton_log_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " log ");
}

void MainWindow::on_pushButton_sqrt_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " sqrt ");
}

void MainWindow::on_pushButton_cos_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " cos ");
}

void MainWindow::on_pushButton_acos_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " acos ");
}

void MainWindow::on_pushButton_asin_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " asin ");
}

void MainWindow::on_pushButton_atan_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " atan ");
}

void MainWindow::on_pushButton_tan_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " tan ");
}

void MainWindow::on_pushButton_sin_clicked() {
  if (check_operat() != 1) {
    replace();
  }
  mul_x();
  ui->result_show->setText(ui->result_show->text() + " sin ");
}

void MainWindow::on_pushButton_pow_clicked() {
  replace();
  ui->result_show->setText(ui->result_show->text() + " ^ ");
}

void MainWindow::on_pushButton_result_clicked() //равно
{
  QString res;
  res = ui->result_show->text();
  if (res == "INCORRECT EXPRESSION" || res == "PARENTHESES ERROR" ||
      res == "" || res == "LINE IS TOO LONG")
    ui->result_show->setText("");
  else if (res.contains('x')) {
    x_exist = new X_exist;
    x_exist->setModal(true);
    connect(x_exist, &X_exist::signal_x, this, &MainWindow::slotX);
    x_exist->show();
  } else {
    std::string str = ui->result_show->text().toStdString();
    const char *p = str.c_str();
    char result[226];
    compute(p, result, 0);
    ui->result_show->setText(result);
  }
}

void MainWindow::on_pushButton_x_clicked() {
  QString str = ui->result_show->text();
  int len = str.length();
  if (len == 0) {
    ui->result_show->setText("x ");
  } else if (len > 0 && ('9' < str[len - 1] || str[len - 1] > '0')) {
    ui->result_show->setText(ui->result_show->text() + " * x ");
  } else
    ui->result_show->setText(ui->result_show->text() + "x ");
}

void MainWindow::on_pushButton_build_clicked() // graph
{
  ui->widget->clearGraphs();
  ui->label_res->setText("");
  int error = 0;

  double x_max = ui->lineEdit_Xmax->text().toDouble();
  if (ui->lineEdit_Xmax->text() != "0" && x_max == 0)
    error = 1;
  double x_min = ui->lineEdit_Xmin->text().toDouble();
  if (ui->lineEdit_Xmin->text() != "0" && x_min == 0)
    error = 1;
  double y_max = ui->lineEdit_Ymax->text().toDouble();
  if (ui->lineEdit_Ymax->text() != "0" && y_max == 0)
    error = 1;
  double y_min = ui->lineEdit_Ymin->text().toDouble();
  if (ui->lineEdit_Ymin->text() != "0" && y_min == 0)
    error = 1;
  double h = ui->lineEdit_h->text().toDouble();
  if (ui->lineEdit_h->text() != "0" && h == 0)
    error = 1;

  if (error == 1 || h <= 0) {
    ui->label_res->setText("Incorrect value");
  } else if (x_min >= x_max || y_min >= y_max) {
    ui->label_res->setText("Max value is less or equal than min value");
  } else if (ui->result_show->text() == "") {
    ui->label_res->setText("Enter an expression");
  } else {
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->xAxis->setRange(x_min, x_max);
    ui->widget->yAxis->setRange(y_min, y_max);

    double X;
    // double n = (x_max - x_min)/h + 2;

    QVector<double> x, y;

    std::string str = ui->result_show->text().toStdString();
    const char *p = str.c_str();
    char result[226];

    compute(p, result, X);
    if (strcmp(result, "INCORRECT EXPRESSION") == 0) { //не работает
      ui->label_res->setText("INCORRECT EXPRESSION");
    } else if (strcmp(result, "LINE IS TOO LONG") == 0) { //не работает
      ui->label_res->setText("LINE IS TOO LONG");
    } else if (strcmp(result, "PARENTHESES ERROR") == 0) { //не работает
      ui->label_res->setText("PARENTHESES ERROR");
    } else {
      for (X = x_min; X <= x_max; X += h) {
        if (compute(p, result, X))
          continue;
        x.push_back(X);
        y.push_back(atof(result));
      }
      ui->label_res->setText(ui->result_show->text());
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->widget->graph(0)->addData(x, y);

    ui->widget->replot();
  }
}

void MainWindow::slotX(QString x) {
  int error = 0;
  int len = x.length();
  if (x.indexOf("-", Qt::CaseInsensitive) > 0) {
    ui->result_show->setText("INCORRECT EXPRESSION");
    error = 1;
  } else {
    int flag = 0;
    for (int i = 0; i < len; i++) {
      if ((x[i] > '9' || x[i] < '0') && x[i] != '.' && x[i] != '-') {
        ui->result_show->setText("INCORRECT EXPRESSION");
        error = 2;
        break;
      } else if (x[i] == '.' && flag == 0) {
        flag = 1;
      } else if (x[i] == '.' && flag == 1) {
        ui->result_show->setText("INCORRECT EXPRESSION");
        error = 1;
        break;
      }
    }
  }
  if (error == 0) {
    double X = x.toDouble();
    std::string str = ui->result_show->text().toStdString();
    const char *p = str.c_str();
    char result[226];
    compute(p, result, X);
    ui->result_show->setText(result);
  }
}

void MainWindow::on_pushButton_calculate_credit_clicked() {
  ui->label_ErrorType->setText("");
  QString totalLoanAmmount_str = ui->lineEdit_totalLoanAm->text();
  QString creditTerm_str = ui->lineEdit_CreditTerm->text();
  QString interest_str = ui->lineEdit_InterestRate->text();

  if (totalLoanAmmount_str == '0' || creditTerm_str == '0' ||
      interest_str == '0') {
    ui->label_ErrorType->setText("Incorrect value!");
  } else {
    double totalLoanAmmount = ui->lineEdit_totalLoanAm->text().toDouble();
    int creditTerm = ui->lineEdit_CreditTerm->text().toInt();
    double interest = ui->lineEdit_InterestRate->text().toDouble();
    if (totalLoanAmmount == 0 || creditTerm == 0 || interest == 0) {
      ui->label_ErrorType->setText("Incorrect value!");
    } else {
      char total_payment[50];
      char overpayment[50];
      char monthly_payment[50];
      int type = 0;
      if (ui->radioButton_Annuity->isChecked()) {
        type = 1;
      } else if (ui->radioButton_Differ->isChecked()) {
        type = 2;
      }
      int n = credit(totalLoanAmmount, creditTerm, interest, type,
                     monthly_payment, overpayment, total_payment);
      if (n == 1) {
        ui->label_ErrorType->setText("Choose type!");
      } else if (n == 2) {
        ui->label_ErrorType->setText("Incorrect value!");
      }
      ui->label_Overpayment->setText(overpayment);
      ui->label_MonthlyP->setText(monthly_payment);
      ui->label_totalPayout->setText(total_payment);
    }
  }
}

void MainWindow::on_pushButton_plusminus_clicked() {
  QString str;
  str = ui->result_show->text();
  int len = str.length();
  if (str[len - 1] != '-') {
    ui->result_show->setText(ui->result_show->text() + "-");
  }
}

void MainWindow::on_pushButton_calculate_deposit_clicked() {
  int error = 0;
  ui->lineEdit_interestProfit->setText("");
  ui->lineEdit_totalAmount->setText("");
  ui->lineEdit_taxAmount->setText("");
  ui->label_ErrorTypeDeposit->setText("");

  int month = ui->lineEdit_month->text().toInt();
  if (ui->lineEdit_month->text() != "0" && month == 0) {
    error = 1;
  }
  int row = 0;
  double replenishment[month];

  if (ui->checkBox_replenishments->isChecked()) {
    while (row < month) {
      QTableWidgetItem *monthly_change =
          ui->tableWidget_Replenishment->item(row, 0);
      if (monthly_change != NULL) {
        replenishment[row] = monthly_change->text().toDouble();
      } else {
        replenishment[row] = 0;
      }
      row++;
    }
  } else {
    while (row < month) {
      replenishment[row] = 0;
      row++;
    }
  }

  double obsh = ui->lineEdit_deposit->text().toDouble();
  if ((ui->lineEdit_deposit->text() != "0" && obsh == 0) || obsh < 0.01) {
    error = 1;
  }
  double proc = ui->lineEdit_interest->text().toDouble();
  if (proc <= 0) {
    error = 1;
  }
  double tax_rate = ui->lineEdit_taxRate->text().toDouble();
  if ((ui->lineEdit_taxRate->text() != "0" && obsh == 0) || tax_rate < 0.01) {
    error = 1;
  }
  double interest_income = 0;
  int payment_periods = 0;
  int capitalization = 0;

  if (ui->radioButton_endTerm->isChecked()) {
    payment_periods = 1;
  } else if (ui->radioButton_monthly->isChecked()) {
    payment_periods = 2;
  }
  if (ui->checkBox_capitalization->isChecked()) {
    capitalization = 1;
  }
  if (error == 0) {
    int n = deposit(&obsh, month, proc, &tax_rate, capitalization,
                    payment_periods, replenishment, &interest_income);
    if (n == 1) {
      ui->label_ErrorTypeDeposit->setText("Choose type of payment!");
    } else {
      QString obsh_str = QString::number(obsh, 'f', 2);
      QString interest_income_str = QString::number(interest_income, 'f', 2);
      QString tax_rate_str = QString::number(tax_rate, 'f', 2);
      ui->lineEdit_interestProfit->setText(interest_income_str);
      ui->lineEdit_totalAmount->setText(obsh_str);
      ui->lineEdit_taxAmount->setText(tax_rate_str);
    }
  } else {
    ui->label_ErrorTypeDeposit->setText(
        "Some value is incorrect or too small!");
  }
}

void MainWindow::on_checkBox_replenishments_stateChanged(int arg1) {
  if (ui->checkBox_replenishments->isChecked()) {
    int month = ui->lineEdit_month->text().toInt();
    ui->tableWidget_Replenishment->setRowCount(month);
    ui->tableWidget_Replenishment->setColumnCount(1);
  } else {
    ui->tableWidget_Replenishment->clear();
  }
}
