#ifndef X_EXIST_H
#define X_EXIST_H

#include <QDialog>

namespace Ui {
class X_exist;
}

class X_exist : public QDialog {
  Q_OBJECT

 public:
  explicit X_exist(QWidget *parent = nullptr);
  ~X_exist();

 private slots:
  void exit();

  void on_get_result_clicked();

 private:
  Ui::X_exist *ui;

 signals:
  void signal_x(QString);
};

#endif  // X_EXIST_H
