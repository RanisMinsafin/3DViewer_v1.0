#include "parser.h"

/*
Это парсер, который открывает obj файл и считывает координатs
вершин и данные полигонов, сохраняя их в структуру Data
*/

// Главная функция, которая открывает файл
Data openFile(char *fileName) {
  Data data = initData();

  // Первое чтение файла
  fillCountVertAndFace(&data, fileName);

  // Инициализация матрицы вершин
  initVertexMatrix(&data);

  // Заполнения данных главной структуры
  fillData(&data, fileName);

  // Центруем фигуру
  center(&data);

  // Возвращаем структуру данных
  return data;
}

// Выставляем значения по умолчанию для структуры данных
Data initData() {
  Data data;
  data.status = OK;
  data.countOfFacets = 0;
  data.countOfVertices = 0;
  data.facets.countOfVertiсesInFacets = 0;
  data.matrix.rows = 0;
  data.matrix.columns = 0;
  data.maxMin.maxX = -INFINITY;
  data.maxMin.maxY = -INFINITY;
  data.maxMin.maxZ = -INFINITY;
  data.maxMin.minX = INFINITY;
  data.maxMin.minY = INFINITY;
  data.maxMin.minZ = INFINITY;
  data.countV = 0;
  return data;
}

// Первое чтение файла (подсчет количества вершин и количество полигонов)
void fillCountVertAndFace(Data *data, char *fileName) {
  if (data->status == OK) {
    FILE *f = NULL;
    f = fopen(fileName, "r");
    if (f) {
      data->countOfFacets = 0;
      data->countOfVertices = 0;
      char current, prev = '\n';
      while ((current = fgetc(f)) != EOF) {
        if (current == 'v' && prev == '\n') {
          if ((current = fgetc(f)) == ' ') data->countOfVertices += 1;
        } else if (current == 'f' && prev == '\n') {
          while ((current = fgetc(f)) != '\n' && current != EOF) {
            if ((isdigit(current) || current == '-' || current == '.') &&
                prev == ' ') {
              data->countOfFacets += 2;
            }
            prev = current;
          }
        }
        prev = current;
      }
      fclose(f);
    } else {
      data->status = OPEN_FAIL;
    }
  }
}

// Выделение памяти под матрицу вершин и ее заполнение данными о количестве
// рядов и колонн в матрице
void initVertexMatrix(Data *data) {
  if (data->status == OK) {
    data->matrix.rows = data->countOfVertices;
    data->matrix.columns = 3;
    data->matrix.m = NULL;
    data->matrix.m = (double *)malloc((data->matrix.rows + 1) *
                                      data->matrix.columns * sizeof(double));
    if (data->matrix.m != NULL) {
      data->matrix.m[0] = 0;
      data->matrix.m[1] = 0;
      data->matrix.m[2] = 0;
    } else {
      data->status = MEMORY_FAIL;
    }
  }
}

// Второе чтение файла (заполнение структуры данными)
void fillData(Data *data, char *fileName) {
  if (data->status == OK) {
    FILE *f = NULL;
    f = fopen(fileName, "r'");
    if (f) {
      char buffer[2048];
      int index = 0, arrNum = 0;
      data->facets.countOfVertiсesInFacets = data->countOfFacets;
      data->facets.vertices =
          (int *)malloc(data->facets.countOfVertiсesInFacets * sizeof(int));
      while (fgets(buffer, 2048, f)) {
        if (buffer[0] == 'v' && buffer[1] == ' ') {
          data->countV += 1;
          fillMatrix(data, &index, buffer);
        } else if (buffer[0] == 'f' && buffer[1] == ' ') {
          fillArr(data, &arrNum, buffer);
        }
      }
      fclose(f);
    } else {
      data->status = OPEN_FAIL;
    }
  }
}

// Заполняем матрицу вершин
void fillMatrix(Data *data, int *index, char *buffer) {
  if (data->status == OK) {
    *index += 1;
    int left = 2, right = 2, numLen = 0, colNum = 0;
    char numBuffer[255];
    while (colNum != 3) {
      left = right;
      numLen = 0;
      while (buffer[right] == '.' || isdigit(buffer[right]) ||
             buffer[right] == '-') {
        numBuffer[numLen++] = buffer[right];
        right += 1;
      }
      if (right != left) {
        numBuffer[numLen] = '\0';
        data->matrix.m[(*index) * 3 + colNum] = atof(numBuffer);
        colNum += 1;
      } else {
        while (buffer[right] != ' ' && buffer[right] != '\n' &&
               buffer[right] != '\0') {
          right += 1;
        }
        right += 1;
      }
    }
  }
}

// Заполнение одномерго массива граней
void fillArr(Data *data, int *position, char *buffer) {
  if (data->status == OK) {
    int left = 2, right = 2, numLen = 0, counter = 0;
    double firstNum;
    char numBuffer[255];
    while (buffer[right] != '\n' && buffer[right] != '\0') {
      left = right;
      numLen = 0;
      while (isdigit(buffer[right]) || buffer[right] == '-') {
        numBuffer[numLen++] = buffer[right];
        right += 1;
      }
      if (right != left) {
        numBuffer[numLen] = '\0';
        int num = atof(numBuffer);
        if (num < 0) {
          num = data->countV + num + 1;
        }
        data->facets.vertices[*position] = num;
        if (counter == 0) firstNum = data->facets.vertices[*position];
        counter += 1;
        *position += 1;
        if (counter != 1) {
          data->facets.vertices[*position] =
              data->facets.vertices[(*position) - 1];
          *position += 1;
        }
      } else {
        while (buffer[right] != ' ' && buffer[right] != '\n' &&
               buffer[right] != '\0') {
          right += 1;
        }
        right += 1;
      }
    }
    data->facets.vertices[*position] = firstNum;
    *position += 1;
  }
}
