#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget* parent) : QOpenGLWidget(parent) {
  vertexColor = Qt::white;
  facetColor = Qt::white;
  is_projection_central = 0;
  shift_x = 0, shift_y = 0, shift_z = 0;
  rotate_x = 0;
  rotate_y = 0;
  rotate_z = 0;
  glwidth = 621, glheight = 591;
}

MyOpenGLWidget::~MyOpenGLWidget() { removeStruct(); }

void MyOpenGLWidget::removeStruct() {
  if (data.matrix.m) free(data.matrix.m);
  if (data.facets.vertices) free(data.facets.vertices);
}

void MyOpenGLWidget::fileOpener(QString fileName, int* countOfVertices,
                                int* countOfFacets) {
  QByteArray byteStr = fileName.toUtf8();
  byteStr.append('\0');
  removeStruct();
  data = openFile(byteStr.data());
  *countOfVertices = data.countOfVertices;
  *countOfFacets = data.countOfFacets;
  if (!data.matrix.m || !data.facets.vertices) {
    QMessageBox::critical(this, tr("Ошибка"),
                          tr("Не удалось открыть файл").arg(fileName));
  }
}

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (is_projection_central) {
    projectionParallel();
  } else {
    projectionCenter();
  }

  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);  // Очистка цветового буфера с использованием
                                 // нового фонового цвета

  paintModel();
  glReadPixels(glwidth / 2, glheight / 2, glwidth, glheight, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
}

void MyOpenGLWidget::setFacetColor(const QColor& color) {
  facetColor = color;
  update();
}

void MyOpenGLWidget::setVertexColor(const QColor& color) {
  vertexColor = color;
  update();
}

void MyOpenGLWidget::setBackgroundColors(const QColor& backColor) {
  backgroundColor = backColor;
  update();  // Вызываем функцию update() для перерисовки виджета
}

void MyOpenGLWidget::setLineType(int type) {
  lineType = type;
  update();
}

void MyOpenGLWidget::setVertType(int type) {
  vertType = type;
  update();
}

void MyOpenGLWidget::setFacetWidth(double fWidth) {
  facetWidth = fWidth;
  update();
}

void MyOpenGLWidget::setVertWidth(double vWidth) {
  vertWidth = vWidth;
  update();
}

void MyOpenGLWidget::setShiftX(double x) {
  moveX(&data, x);
  update();
}

void MyOpenGLWidget::setShiftY(double y) {
  moveY(&data, y);
  update();
}

void MyOpenGLWidget::setShiftZ(double z) {
  moveZ(&data, z);
  update();
}

void MyOpenGLWidget::setRotateX(double x) {
  rotateX(&data, x);
  update();
}

void MyOpenGLWidget::setRotateY(double y) {
  rotateY(&data, y);
  update();
}

void MyOpenGLWidget::setRotateZ(double z) {
  rotateZ(&data, z);
  update();
}

void MyOpenGLWidget::setScale(double scaleValue) {
  scale(&data, scaleValue);
  update();
}

void MyOpenGLWidget::setProjection(int value) { is_projection_central = value; }

void MyOpenGLWidget::paintModel() {
  glVertexPointer(3, GL_DOUBLE, 0, data.matrix.m);
  // Включает использование массива вершин
  glEnableClientState(GL_VERTEX_ARRAY);

  if (lineType) {
    // Включает использование шаблона линий
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
  } else {
    // Паттерн сплошной линии
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(facetWidth);
  glPointSize(vertWidth);

  // Установка цвета вершин
  glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
  if (vertType == 1) {
    glDrawArrays(GL_POINTS, 0, data.countOfVertices);
  } else if (vertType == 2) {
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, data.countOfVertices);
    glDisable(GL_PROGRAM_POINT_SIZE);
    glDisable(GL_POINT_SMOOTH);
  }

  // Установка цвета граней
  glColor3f(facetColor.redF(), facetColor.greenF(), facetColor.blueF());
  glDrawElements(GL_LINES, data.countOfFacets, GL_UNSIGNED_INT,
                 data.facets.vertices);
  glDisableClientState(GL_VERTEX_ARRAY);
}

/* Центральная проекция */
void MyOpenGLWidget::projectionCenter() {
  if (data.countOfFacets && data.countOfVertices) {
    float fov = 30.0 * M_PI / 180;
    float heapHeight = data.maxMin.maxY / (2 * tan(fov / 2));

    glFrustum(data.maxMin.minX, data.maxMin.maxX, data.maxMin.minY,
              data.maxMin.maxY, heapHeight, data.maxMin.maxZ * 100);
    glTranslatef(0, 0, -heapHeight * 3);
  }

  update();
}

/* Параллельная проекция */
void MyOpenGLWidget::projectionParallel() {
  if (data.countOfFacets && data.countOfVertices) {
    glOrtho(data.maxMin.minX * 1.5f, data.maxMin.maxX * 1.5f,
            data.maxMin.minY * 1.5f, data.maxMin.maxY * 1.5f,
            data.maxMin.minZ * 3.5f, data.maxMin.maxZ * 3.5f);
    glTranslatef(0, 0, -0.5);
  }

  update();
}

void MyOpenGLWidget::gifMaker() {
  QString fileName = "../../../../gif_image.gif";  // Путь к файлу
  int delay = 100;  // Задержка между сохранением каждого кадра GIF.
  GifWriter g;
  // Инициализируем структуру GifWriter для записи GIF-файла
  GifBegin(&g, fileName.toStdString().c_str(), glwidth, glheight, delay);
  // Запись кадров GIF
  for (int timer = 0; timer <= 5000; timer += delay) {
    GifWriteFrame(&g, image, glwidth, glheight, 1);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  }
  qDebug() << "Gif is ready";
  GifEnd(&g);
}
