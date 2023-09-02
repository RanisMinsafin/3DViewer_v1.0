#ifndef SRC_PARSER_H
#define SRC_PARSER_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Структура для хранения граней
typedef struct Facets {
  int *vertices;
  int countOfVertiсesInFacets;
} Facets;

//
typedef struct MaxMin {
  double maxX;
  double maxY;
  double maxZ;
  double minX;
  double minY;
  double minZ;
} MaxMin;

// Структура для хранения матрицы вершин
typedef struct Matrix {
  double *m;
  int rows;
  int columns;
} Matrix;

// Переменная, которая содержит в себе статус операций
typedef enum Status { OK = 0, MEMORY_FAIL = 1, OPEN_FAIL = 2 } Status;

// Основная структура с данными
typedef struct Data {
  int countOfVertices;
  int countOfFacets;
  Matrix matrix;
  Facets facets;
  Status status;
  MaxMin maxMin;
  int countV;
} Data;

// Главная функция открытия файла
Data openFile(char *file_name);

// Функции парсинга
Data initData();
void fillCountVertAndFace(Data *data, char *fileName);
void initVertexMatrix(Data *data);
void fillData(Data *data, char *fileName);
void fillMatrix(Data *data, int *index, char *buffer);
void fillArr(Data *data, int *position, char *buffer);

// Преобразования
void moveX(Data *data, double distance);
void moveY(Data *data, double distance);
void moveZ(Data *data, double distance);
void rotateX(Data *data, double angle);
void rotateY(Data *data, double angle);
void rotateZ(Data *data, double angle);
void scale(Data *data, double size);
void findMaxMin(Data *data);
void center(Data *data);
double findMaxOfThree(double x, double y, double z);

#endif  // SRC_PARSER_H
