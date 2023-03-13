#ifndef SRC_SOURCE_MAINWINDOW_H_
#define SRC_SOURCE_MAINWINDOW_H_

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QWidget>

#include "backend.h"

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

 private slots:
  void NumPressed();
  void FuncPressed();
  void OtherPressed();
  void EqualsPressed();
  void AcPressed();
  void CheckUser();
  void ChangeSignPressed();
  void CreateGraph();
  char *insertX(QString originalStr, double xVal, int len_helper, int *fixLen);

 private:
  Ui::MainWindow *ui;
};

#endif  // SRC_SOURCE_MAINWINDOW_H_
