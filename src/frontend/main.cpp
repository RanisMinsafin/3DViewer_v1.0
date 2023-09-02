#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setFixedSize(1090, 709);
  w.setWindowTitle("3DViewer");
  w.show();
  return a.exec();
}
