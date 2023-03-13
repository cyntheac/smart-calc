#include "x_exist.h"
#include "ui_x_exist.h"
#include <qdebug.h>

X_exist::X_exist(QWidget *parent) : QDialog(parent), ui(new Ui::X_exist) {
  ui->setupUi(this);

  QObject::connect(ui->exit_button, SIGNAL(clicked()), this, SLOT(exit()));
}

X_exist::~X_exist() { delete ui; }

void X_exist::exit() { X_exist::close(); }

void X_exist::on_get_result_clicked() {
  emit signal_x(ui->lineEdit_x->text());
  qDebug() << ui->lineEdit_x->text();
  X_exist::close();
}
