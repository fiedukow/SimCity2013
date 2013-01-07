#include "SimCityWindow.h"
#include "ui_SimCityWindow.h"

SimCityWindow::SimCityWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SimCityWindow)
{
  ui->setupUi(this);
}

SimCityWindow::~SimCityWindow()
{
  delete ui;
}
