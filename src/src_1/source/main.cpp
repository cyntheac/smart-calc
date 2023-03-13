#include <QApplication>
#include <QFile>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile styleSheetFile(":/new/lala/SpyBot.qss");
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(styleSheetFile.readAll());
  a.setStyleSheet(styleSheet);

  MainWindow w;
  w.show();

  a.exec();
  styleSheetFile.close();

  return 0;
}
