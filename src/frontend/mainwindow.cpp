#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setSettings();
  loadSettings();

  connect(ui->shift_x_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->shift_x_minus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->shift_y_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->shift_y_minus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->shift_z_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->shift_z_minus, SIGNAL(clicked()), this, SLOT(afin()));

  connect(ui->spin_x_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->spin_x_minus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->spin_y_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->spin_y_minus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->spin_z_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->spin_z_minus, SIGNAL(clicked()), this, SLOT(afin()));

  connect(ui->scale_plus, SIGNAL(clicked()), this, SLOT(afin()));
  connect(ui->scale_minus, SIGNAL(clicked()), this, SLOT(afin()));
}

MainWindow::~MainWindow() {
  saveSettings();
  ui->openGLWidget->~MyOpenGLWidget();
  delete ui;
}

void MainWindow::saveSettings() {
  QSettings settings("MyCompany", "MyApp");
  // Сохранение значений настроек
  settings.setValue("x_move", ui->x_move_spin->value());
  settings.setValue("y_move", ui->y_move_spin->value());
  settings.setValue("z_move", ui->z_move_spin->value());
  settings.setValue("x_rotate", ui->x_rotate_spin->value());
  settings.setValue("y_rotate", ui->y_rotate_spin->value());
  settings.setValue("z_rotate", ui->z_rotate_spin->value());
  settings.setValue("change_scale_minus", ui->scale_minus_value->value());
  settings.setValue("change_scale_plus", ui->scale_plus_value->value());
  settings.setValue("facet_width", ui->facetWidth->value());
  settings.setValue("vert_width", ui->vertWidth->value());
  settings.setValue("type_of_projection", ui->typeOfProjection->currentIndex());
  settings.setValue("type_of_line", ui->typeOfLine->currentIndex());
  settings.setValue("type_of_vert", ui->typeOfVert->currentIndex());
  // Сохранение настроек в файл
  settings.sync();
}

void MainWindow::loadSettings() {
  QSettings settings("MyCompany", "MyApp");
  // Загрузка значений настроек
  ui->x_move_spin->setValue(settings.value("x_move", 0).toDouble());
  ui->y_move_spin->setValue(settings.value("y_move", 0).toDouble());
  ui->z_move_spin->setValue(settings.value("z_move", 0).toDouble());
  ui->x_rotate_spin->setValue(settings.value("x_rotate", 0).toDouble());
  ui->y_rotate_spin->setValue(settings.value("y_rotate", 0).toDouble());
  ui->z_rotate_spin->setValue(settings.value("z_rotate", 0).toDouble());
  ui->scale_minus_value->setValue(
      settings.value("change_scale_minus", 0).toDouble());
  ui->scale_plus_value->setValue(
      settings.value("change_scale_plus", 0).toDouble());
  ui->facetWidth->setValue(settings.value("facet_width", 1).toInt());
  ui->vertWidth->setValue(settings.value("vert_width", 1).toInt());
  ui->typeOfProjection->setCurrentIndex(
      settings.value("type_of_projection", 0).toInt());
  ui->typeOfLine->setCurrentIndex(settings.value("type_of_line", 0).toInt());
  ui->typeOfVert->setCurrentIndex(settings.value("type_of_vert", 0).toInt());
}

void MainWindow::setSettings() {
  ui->scale_minus_value->setSingleStep(0.5);
  ui->scale_minus_value->setRange(0, 0.99);
  ui->scale_minus_value->setValue(0.9);
  ui->scale_plus_value->setSingleStep(0.5);
  ui->scale_plus_value->setRange(1.01, 3);
  ui->scale_plus_value->setValue(1.1);
  ui->facetWidth->setRange(1, 10);
  ui->vertWidth->setRange(1, 10);
  ui->x_move_spin->setRange(-100, 100);
  ui->x_move_spin->setSingleStep(0.01);
  ui->y_move_spin->setRange(-100, 100);
  ui->y_move_spin->setSingleStep(0.01);
  ui->z_move_spin->setRange(-100, 100);
  ui->z_move_spin->setSingleStep(0.01);
  ui->x_rotate_spin->setRange(-360, 360);
  ui->x_rotate_spin->setSingleStep(0.1);
  ui->x_rotate_spin->setValue(0.1);
  ui->y_rotate_spin->setRange(-360, 360);
  ui->y_rotate_spin->setSingleStep(0.1);
  ui->y_rotate_spin->setValue(0.1);
  ui->z_rotate_spin->setRange(-360, 360);
  ui->z_rotate_spin->setSingleStep(0.1);
}

void MainWindow::resetData() {
  ui->x_move_spin->setValue(0);
  ui->y_move_spin->setValue(0);
  ui->z_move_spin->setValue(0);
  ui->x_rotate_spin->setValue(0);
  ui->y_rotate_spin->setValue(0);
  ui->z_rotate_spin->setValue(0);
  ui->scale_minus_value->setValue(0);
  ui->scale_plus_value->setValue(0);
  ui->facetWidth->setValue(1);
  ui->vertWidth->setValue(1);
  ui->typeOfProjection->setCurrentIndex(0);
  ui->typeOfLine->setCurrentIndex(0);
  ui->typeOfVert->setCurrentIndex(0);
}

void MainWindow::afin() {
  QPushButton *button = (QPushButton *)sender();

  QString btn_name = button->objectName();

  if (btn_name == "shift_x_minus") {
    ui->openGLWidget->setShiftX(ui->x_move_spin->value() * -1);
  } else if (btn_name == "shift_y_minus") {
    ui->openGLWidget->setShiftY(ui->y_move_spin->value() * -1);
  } else if (btn_name == "shift_z_minus") {
    ui->openGLWidget->setShiftZ(ui->z_move_spin->value() * -1);
  } else if (btn_name == "shift_x_plus") {
    ui->openGLWidget->setShiftX(ui->x_move_spin->value());
  } else if (btn_name == "shift_y_plus") {
    ui->openGLWidget->setShiftY(ui->y_move_spin->value());
  } else if (btn_name == "shift_z_plus") {
    ui->openGLWidget->setShiftZ(ui->z_move_spin->value());
  } else if (btn_name == "spin_x_minus") {
    ui->openGLWidget->setRotateX(ui->x_rotate_spin->value());
  } else if (btn_name == "spin_y_minus") {
    ui->openGLWidget->setRotateY(ui->y_rotate_spin->value());
  } else if (btn_name == "spin_z_minus") {
    ui->openGLWidget->setRotateZ(ui->z_rotate_spin->value());
  } else if (btn_name == "spin_x_plus") {
    ui->openGLWidget->setRotateX(ui->x_rotate_spin->value() * -1);
  } else if (btn_name == "spin_y_plus") {
    ui->openGLWidget->setRotateY(ui->y_rotate_spin->value() * -1);
  } else if (btn_name == "spin_z_plus") {
    ui->openGLWidget->setRotateZ(ui->z_rotate_spin->value() * -1);
  } else if (btn_name == "scale_plus") {
    ui->openGLWidget->setScale(ui->scale_plus_value->value());
  } else if (btn_name == "scale_minus") {
    ui->openGLWidget->setScale(ui->scale_minus_value->value());
  }
}

void MainWindow::on_fileSelectButton_clicked() {
  QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "",
                                                  "Файлы OBJ (*.obj)");
  if (!filePath.isEmpty()) {
    //       resetData();
    QString fileName = QFileInfo(filePath).filePath();
    ui->openGLWidget->fileOpener(fileName, &countOfVertices, &countOfFacets);
    // Проверка на корректность открываемого файла
    if (!countOfFacets && !countOfVertices) {
      ui->showFileName->setText("Ошибка файла");
    } else {
      ui->showFileName->setText(QFileInfo(filePath).fileName());
    }
    ui->countOfFacets->setText(QString::number(countOfFacets));
    ui->countOfVerts->setText(QString::number(countOfVertices));
  }
}

void MainWindow::on_lineColor_clicked() {
  QColor facetColor =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");
  if (facetColor.isValid()) {
    ui->openGLWidget->setFacetColor(facetColor);
  }
}

void MainWindow::on_peakColor_clicked() {
  QColor verterColor =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет вершин");
  if (verterColor.isValid()) {
    ui->openGLWidget->setVertexColor(verterColor);
  }
}

void MainWindow::on_backColor_clicked() {
  QColor backColor =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  if (backColor.isValid()) {
    ui->openGLWidget->setBackgroundColors(backColor);
  }
}

void MainWindow::on_typeOfVert_currentIndexChanged(int type) {
  ui->openGLWidget->setVertType(type);
}

void MainWindow::on_typeOfLine_currentIndexChanged(int index) {
  ui->openGLWidget->setLineType(index);
}

void MainWindow::on_facetWidth_valueChanged(double width) {
  ui->openGLWidget->setFacetWidth(width);
}

void MainWindow::on_vertWidth_valueChanged(double width) {
  ui->openGLWidget->setVertWidth(width);
}

void MainWindow::on_saveAsButton_clicked() {
  // Создается область rect, охватывающая всю область ui->openGLWidget
  const QRect rect(0, 0, ui->openGLWidget->width(), ui->openGLWidget->height());
  // Создаем pix, содержащий снимок этой области
  QPixmap pix = ui->openGLWidget->grab(rect);
  const QString format = "png";
  QString initialPath = QDir::currentPath() + tr("/screenshot.") + format;
  QFileDialog fileDialog(this, tr("Сохранить скриншот"), initialPath);
  fileDialog.setAcceptMode(QFileDialog::AcceptSave);
  fileDialog.setFileMode(QFileDialog::AnyFile);
  QStringList mimeTypes;
  const QList<QByteArray> baMimeTypes = QImageWriter::supportedMimeTypes();
  for (const QByteArray &bf : baMimeTypes) mimeTypes.append(QLatin1String(bf));
  fileDialog.setMimeTypeFilters(mimeTypes);
  fileDialog.selectMimeTypeFilter("image/" + format);
  fileDialog.setDefaultSuffix(format);
  if (fileDialog.exec() != QDialog::Accepted) return;
  const QString fileName = fileDialog.selectedFiles().first();
  if (!pix.save(fileName)) {
    QMessageBox::warning(this, tr("Save Error"),
                         tr("The image could not be saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(fileName)));
  }
}

void MainWindow::on_make_gif_clicked() {
  // Создание нового потока
  std::thread gif_thread(&MyOpenGLWidget::gifMaker, ui->openGLWidget);
  // Отсоединение потока от основного потока выполнения
  gif_thread.detach();
}

void MainWindow::on_typeOfProjection_currentIndexChanged(int index) {
  ui->openGLWidget->setProjection(index);
}
