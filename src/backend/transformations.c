#include "parser.h"

// Перемещение по оси X
void moveX(Data *data, double distance) {
  for (int i = 3; i < (data->matrix.rows + 1) * 3; i += 3) {
    data->matrix.m[i] += distance;
  }
}

// Перемещение по оси Y
void moveY(Data *data, double distance) {
  for (int i = 4; i < (data->matrix.rows + 1) * 3; i += 3) {
    data->matrix.m[i] += distance;
  }
}

// Перемещение по оси Z
void moveZ(Data *data, double distance) {
  for (int i = 5; i < (data->matrix.rows + 1) * 3; i += 3) {
    data->matrix.m[i] += distance;
  }
}

// Поворот по оси X
void rotateX(Data *data, double angle) {
  for (int i = 1; i < data->matrix.rows + 1; i++) {
    double tempY = data->matrix.m[i * 3 + 1];
    double tempZ = data->matrix.m[i * 3 + 2];
    data->matrix.m[i * 3 + 1] = cos(angle) * tempY - sin(angle) * tempZ;
    data->matrix.m[i * 3 + 2] = sin(angle) * tempY + cos(angle) * tempZ;
  }
}

// Поворот по оси Y
void rotateY(Data *data, double angle) {
  for (int i = 1; i < data->matrix.rows + 1; i++) {
    double tempX = data->matrix.m[i * 3];
    double tempZ = data->matrix.m[i * 3 + 2];
    data->matrix.m[i * 3] = cos(angle) * tempX + sin(angle) * tempZ;
    data->matrix.m[i * 3 + 2] = -sin(angle) * tempX + cos(angle) * tempZ;
  }
}

// Поворот по оси Z
void rotateZ(Data *data, double angle) {
  for (int i = 1; i < data->matrix.rows + 1; i++) {
    double tempX = data->matrix.m[i * 3];
    double tempY = data->matrix.m[i * 3 + 1];
    data->matrix.m[i * 3] = cos(angle) * tempX - sin(angle) * tempY;
    data->matrix.m[i * 3 + 1] = sin(angle) * tempX + cos(angle) * tempY;
  }
}

// Изменение масштаба
void scale(Data *data, double size) {
  if (size) {
    for (int i = 1; i < data->matrix.rows + 1; i++) {
      data->matrix.m[i * 3] *= size;
      data->matrix.m[i * 3 + 1] *= size;
      data->matrix.m[i * 3 + 2] *= size;
    }
  }
}

// Находим максимумы и минимумы по каждой оси
void findMaxMin(Data *data) {
  if (data->status == OK) {
    for (int i = 1; i < data->countOfVertices + 1; i += 1) {
      if (data->matrix.m[i * 3] > data->maxMin.maxX)
        data->maxMin.maxX = data->matrix.m[i * 3];
      if (data->matrix.m[i * 3 + 1] > data->maxMin.maxY)
        data->maxMin.maxY = data->matrix.m[i * 3 + 1];
      if (data->matrix.m[i * 3 + 2] > data->maxMin.maxZ)
        data->maxMin.maxZ = data->matrix.m[i * 3 + 2];
      if (data->matrix.m[i * 3] < data->maxMin.minX)
        data->maxMin.minX = data->matrix.m[i * 3];
      if (data->matrix.m[i * 3 + 1] < data->maxMin.minY)
        data->maxMin.minY = data->matrix.m[i * 3 + 1];
      if (data->matrix.m[i * 3 + 2] < data->maxMin.minZ)
        data->maxMin.minZ = data->matrix.m[i * 3 + 2];
    }
  }
}

// Центруем каждую координату
void center(Data *data) {
  if (data->status == OK) {
    double val = 0.75;  // Задаем масштаб фигуры (выставляем от 0 до 1)
    findMaxMin(data);
    double cX = data->maxMin.minX + (data->maxMin.maxX - data->maxMin.minX) / 2;
    double cY = data->maxMin.minY + (data->maxMin.maxY - data->maxMin.minY) / 2;
    double cZ = data->maxMin.minZ + (data->maxMin.maxZ - data->maxMin.minZ) / 2;
    for (int i = 1; i < data->countOfVertices + 1; i += 1) {
      data->matrix.m[i * 3] -= cX;
      data->matrix.m[i * 3 + 1] -= cY;
      data->matrix.m[i * 3 + 2] -= cZ;
    }
    double x = data->maxMin.maxX - data->maxMin.minX;
    double y = data->maxMin.maxY - data->maxMin.minY;
    double z = data->maxMin.maxZ - data->maxMin.minZ;
    double dMax = findMaxOfThree(x, y, z);
    double k = 2 * val / dMax;
    scale(data, k);
  }
}

double findMaxOfThree(double x, double y, double z) {
  double max = x;
  if (y > max) {
    max = y;
  }
  if (z > max) {
    max = z;
  }
  return max;
}
