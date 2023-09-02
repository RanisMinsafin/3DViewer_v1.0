#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QImage>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QPainter>
#include <QSettings>
#include <QString>
#include <QtGui/QOpenGLFunctions>
#include <chrono>
#include <filesystem>
#include <thread>

#include "../gif.hpp"

extern "C" {
#include "../backend/parser.h"
}

class MyOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  Data data;
  int vertType;
  int lineType;
  int prev_angle_x;
  int prev_angle_y;
  int prev_angle_z;
  double facetWidth;
  double vertWidth;
  double prev_coor_x;
  double prev_coor_y;
  double prev_coor_z;
  double translate_x, translate_y, translate_z;

 public slots:
  MyOpenGLWidget(QWidget* parent = nullptr);
  ~MyOpenGLWidget();
  void setLineType(int type);
  void setVertType(int type);
  void setFacetWidth(double fWidth);
  void setVertWidth(double vWidth);
  void setShiftX(double x);
  void setShiftY(double y);
  void setShiftZ(double y);
  void setRotateX(double x);
  void setRotateY(double y);
  void setRotateZ(double z);
  void setScale(double scaleValue);
  void removeStruct();
  void setVertexColor(const QColor& color);
  void setFacetColor(const QColor& color);
  void setBackgroundColors(const QColor& backColor);
  void fileOpener(QString fileName, int* countOfVertices, int* countOfFacets);
  void projectionCenter();
  void projectionParallel();
  void setProjection(int value);
  void gifMaker();

 private slots:
  void initializeGL() override;
  void paintGL() override;
  void paintModel();

 private:
  QPoint mPos, mDelta;
  int glwidth, glheight;
  QColor vertexColor;
  QColor facetColor;
  QColor backgroundColor;
  GLfloat shift_x, shift_y, shift_z;
  GLfloat rotate_x, rotate_y, rotate_z;
  int is_projection_central;
  uint8_t image[800 * 800 * 4];
};

#endif  // MYOPENGLWIDGET_H
;
