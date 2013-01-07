#include "SimCityWindow.h"
#include "ui_SimCityWindow.h"
#include <QLine>

SimCityWindow::SimCityWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::SimCityWindow)
{
  ui->setupUi(this);
  fpsCounter_ = new QLabel("0");
  speedCounter_ = new QLabel("x1");

  statusBar()->addWidget(new QLabel("FPS: ", this));
  statusBar()->addWidget(fpsCounter_);
  statusBar()->addWidget(new QLabel("  |  ", this));
  statusBar()->addWidget(new QLabel("Speed: ", this));
  statusBar()->addWidget(speedCounter_);
}

SimCityWindow::~SimCityWindow()
{
  delete ui;
}
