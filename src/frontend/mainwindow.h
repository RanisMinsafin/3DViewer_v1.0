#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QBuffer>
#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QMainWindow>
#include <QPixmap>
#include <QRect>
#include <QStandardPaths>
#include <QString>
#include <iostream>
#include <thread>

#include "../gif.hpp"
#include "myopenglwidget.h"

using namespace std;

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
  int countOfFacets;
  int countOfVertices;

 private slots:
  void resetData();
  void setSettings();
  void saveSettings();
  void loadSettings();
  void on_lineColor_clicked();
  void on_peakColor_clicked();
  void on_backColor_clicked();
  void on_saveAsButton_clicked();
  void on_fileSelectButton_clicked();
  void on_make_gif_clicked();
  void on_typeOfVert_currentIndexChanged(int type);
  void on_typeOfLine_currentIndexChanged(int index);
  void on_facetWidth_valueChanged(double width);
  void on_vertWidth_valueChanged(double width);
  void afin();

  void on_typeOfProjection_currentIndexChanged(int index);

 private:
  Ui::MainWindow *ui;
  MyOpenGLWidget *myOpenGLWidget;
  QColor vertexColor;
};
#endif  // MAINWINDOW_H
