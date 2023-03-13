#include "mainwindow.h"

#include <QChar>
#include <QColor>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <string>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->Main_Display->setStyleSheet("background-color: lavender;");

  //    QScrollBar::add-line:vertical:pressed {
  //        background-color: pink;
  //    }

  ui->Main_Display->setValidator(new QRegularExpressionValidator(
      QRegularExpression("[A-Za-z0-9-+=()*/^,.]*"), this));
  ui->MinX->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[0-9-.]*"), this));
  ui->MaxX->setValidator(
      new QRegularExpressionValidator(QRegularExpression("[0-9-.]*"), this));

  ui->widget->xAxis->grid()->setPen(
      QPen(QColor(123, 104, 238), 0.5, Qt::DotLine));
  ui->widget->yAxis->grid()->setPen(
      QPen(QColor(123, 104, 238), 0.5, Qt::DotLine));

  QPushButton *numButtons[10];
  for (int i = 0; i < 10; i++) {
    QString butName = "Button" + QString::number(i);
    numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
    connect(numButtons[i], SIGNAL(pressed()), this, SLOT(NumPressed()));
  }

  QPushButton *funcButtons[10];
  for (int i = 100, j = 0; j < 10; i++, j++) {
    QString butName = "Button" + QString::number(i);
    funcButtons[j] = MainWindow::findChild<QPushButton *>(butName);
    connect(funcButtons[j], SIGNAL(pressed()), this, SLOT(FuncPressed()));
  }

  QPushButton *otherButtons[9];
  for (int i = 200, j = 0; j < 9; i++, j++) {
    QString butName = "Button" + QString::number(i);
    otherButtons[j] = MainWindow::findChild<QPushButton *>(butName);
    connect(otherButtons[j], SIGNAL(pressed()), this, SLOT(OtherPressed()));
  }

  connect(ui->All_Clean, SIGNAL(pressed()), this, SLOT(AcPressed()));
  connect(ui->UnarySign, SIGNAL(pressed()), this, SLOT(ChangeSignPressed()));
  connect(ui->Equals, SIGNAL(pressed()), this, SLOT(EqualsPressed()));
  connect(ui->Main_Display, SIGNAL(textChanged(QString)), this,
          SLOT(CheckUser()));
  connect(ui->Main_Display, SIGNAL(returnPressed()), this,
          SLOT(EqualsPressed()));

  //    void dit::keyPressEvent(QKeyEvent *event);
  ui->widget->setBackground(QColorConstants::Svg::lavender);
  connect(ui->Graph, SIGNAL(pressed()), this, SLOT(CreateGraph()));
}

MainWindow::~MainWindow() { delete ui; }

// TODO(sparelis): Refactoring needed
void MainWindow::CreateGraph() {
  QString displayVal = ui->Main_Display->text();
  int len_helper = displayVal.length();
  QByteArray ba = displayVal.toLocal8Bit();
  char *c_str2 = ba.data();
  char *helperPtr;
  double res;
  int fixLen;
  bool ok;
  ui->widget->clearGraphs();

  if (std::strchr(c_str2, 'x') == NULL) {
    char *ret = get_result(c_str2, (int)displayVal.length());
    ui->Main_Display->setText(ret);
    if (std::strstr(ret, "check input")) {
      make_me_free(ret);
      return;
    }
    res = std::strtod(ret, &helperPtr);

    // generate some data:
    QVector<double> x(11), y(11);  // initialize with entries 0..100
    for (int i = 0, j = -5; i < 11; ++i, ++j) {
      x[i] = i;    // x goes from -1 to 1
      y[i] = res;  // let's plot a function
    }

    // create and configure plottables:
    QCPGraph *graph1 = ui->widget->addGraph();
    graph1->setData(x, y);
    graph1->setPen(QPen(QColor(123, 104, 238), 3));

    // adapt axes ranges, so we see all data:
    ui->widget->graph(0)->rescaleAxes();
    ui->widget->replot();
    make_me_free(ret);
  } else {
    int extraHelperPtr = -1;
    int check = check_input(c_str2, (int)displayVal.length(), &extraHelperPtr);
    if (check == 0) {
      ui->Main_Display->setText("check input dude");
      return;
    }

    QVector<double> x(200), y(200);
    QString minVal = ui->MinX->text();
    //            qDebug() << "min val is" << minVal;
    QString maxVal = ui->MaxX->text();
    //            qDebug() << "max val is" << maxVal;
    double rangeMin, rangeMax, step;

    if (minVal.length() > 0 && maxVal.length() > 0) {
      rangeMin = minVal.toDouble(&ok);
      //                  qDebug() << "rangeMin is" << rangeMin;
      rangeMax = maxVal.toDouble(&ok);
      //                  qDebug() << "rangeMax is" << rangeMax;
    } else {
      return;
    }

    step = std::fabs((rangeMax - rangeMin) / 200.0);
    //            qDebug() << "step is" << step;
    double yMin = 0, yMax = 0;
    double j = rangeMin;

    for (int i = 0; i < 200; ++i) {
      if ((std::fabs(j)) < 1e-6) j = 0;
      x[i] = j;
      //                qDebug() << "x is " << j;
      char *convertString = insertX(displayVal, j, len_helper, &fixLen);
      //      qDebug() << "convert string is " << convertString;
      char *polishHelper = get_result(convertString, fixLen);  // попробовать

      //                qDebug() << "y is" << polishHelper;
      y[i] = std::strtod(polishHelper, &helperPtr);
      make_me_free(polishHelper);
      polishHelper = NULL;
      delete convertString;
      convertString = nullptr;
      if (i == 0) {
        yMin = yMax = y[i];
      } else {
        if (y[i] > yMax) yMax = y[i];
        if (y[i] < yMin) yMin = y[i];
      }
      j = j + step;
    }

    // create and configure plottables:
    QCPGraph *graph1 = ui->widget->addGraph();
    graph1->setData(x, y);
    graph1->setLineStyle(QCPGraph::LineStyle::lsNone);
    graph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,
                                            QColor(123, 104, 238, 255), 3));

    //                setPen(QPen(QColor(123,104,238), 3));

    ui->widget->xAxis->setRange(rangeMin, rangeMax);
    ui->widget->yAxis->setRange(yMin, yMax);
    ui->widget->replot();
  }
}

char *MainWindow::insertX(QString originalStr, double xVal, int len_helper,
                          int *fixLen) {
  //    qDebug() << originalStr;

  QString numStr = QString::number(xVal);
  int len = numStr.length();
  char *ret =
      new char((int)originalStr.length() * 2 + (originalStr.count('x')));

  int j = 0;
  for (int i = 0; i < len_helper; i++) {
    if (originalStr[i] != 'x') {
      ret[j++] = originalStr.at(i).toLatin1();
    } else {
      for (int k = 0; k < len; k++) {
        ret[j++] = numStr.at(k).toLatin1();
      }
    }
  }

  ret[j] = '\0';
  *fixLen = j;
  //    qDebug() << ret;
  return ret;
}

void MainWindow::NumPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();
  QString displayVal = ui->Main_Display->text();
  QString newVal = displayVal + butVal;
  ui->Main_Display->setText(newVal);
}

void MainWindow::FuncPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();
  QString displayVal = ui->Main_Display->text();
  QString newVal = displayVal + butVal + ((butVal == "mod") ? "" : "(");
  ui->Main_Display->setText(newVal);
}

void MainWindow::OtherPressed() {
  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();
  QString displayVal = ui->Main_Display->text();
  QString newVal = displayVal + butVal;
  ui->Main_Display->setText(newVal);
}

void MainWindow::AcPressed() { ui->Main_Display->setText(""); }

void MainWindow::EqualsPressed() {
  QString displayVal = ui->Main_Display->text();
  QByteArray ba = displayVal.toLocal8Bit();
  const char *c_str2 = ba.data();
  if (std::strchr(c_str2, 'x')) return;

  char *ret = get_result(c_str2, (int)displayVal.length());
  ui->Main_Display->setText(ret);
  make_me_free(ret);
}

void MainWindow::CheckUser() {
  QString displayVal = ui->Main_Display->text();
  int length = displayVal.length();
  if (length > 0 && (displayVal[length - 1] == '=')) EqualsPressed();
}

void MainWindow::ChangeSignPressed() {
  QString displayVal = ui->Main_Display->text();
  int size = displayVal.length();

  if (size &&
      (displayVal[size - 1].isDigit() || (displayVal[size - 1] == 'x'))) {
    int index = -1;
    QString tmp;
    int detectDigit = 0;
    for (int i = (size - 1); i >= 0; i--) {
      if (displayVal[i].isDigit() || (displayVal[i] == 'x')) {
        detectDigit++;
      } else if (detectDigit && (index == -1) && (displayVal[i] != '.') &&
                 (displayVal[i] != ',')) {
        index = i;
        break;
      }
    }
    if (index == -1) {
      tmp = "(-" + displayVal + ")";
    } else if (displayVal[index] == '+') {
      if (index == 0) {
        tmp = displayVal.right(size - 1);
      } else {
        tmp = displayVal.left(index) + "-" + displayVal.right(size - index - 1);
      }
    } else if (displayVal[index] == '-') {
      if (index > 0 && (displayVal[index - 1] == '('))
        tmp = displayVal.left(index) + displayVal.right(size - index - 1);
      else
        tmp = displayVal.left(index) + "+" + displayVal.right(size - index - 1);
    } else {
      tmp = displayVal.left(index + 1) + "(-" +
            displayVal.right(size - index - 1) + ")";
    }
    ui->Main_Display->setText(tmp);
  } else {
    ui->Main_Display->setText(displayVal);
  }
}
