#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qcustomplot.h>
#include <x_exist.h>

#include <QMainWindow>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif
#include "calculator.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  double x = 0;
  X_exist *x_exist;

 private:
  Ui::MainWindow *ui;
  //    X_exist *x_exist;

 private slots:
  void digits();
  void on_pushButton_dot_clicked();
  void on_pushButtonSkobkaOtkr_clicked();
  void on_pushButtonAC_clicked();
  void on_pushButtonSkobkaZakr_clicked();
  void on_pushButtonClear_clicked();
  void on_pushButton_div_clicked();
  int replace();
  int check_operat();
  int mul_x();
  void on_pushButton_mul_clicked();
  void on_pushButton_sub_clicked();
  void on_pushButton_add_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_result_clicked();
  void on_pushButton_pow_clicked();
  void on_pushButton_x_clicked();
  void on_pushButton_build_clicked();
  void on_pushButton_calculate_credit_clicked();
  void on_pushButton_plusminus_clicked();
  void on_pushButton_calculate_deposit_clicked();

  void on_checkBox_replenishments_stateChanged(int arg1);

 public slots:
  void slotX(QString x);
};
#endif  // MAINWINDOW_H
