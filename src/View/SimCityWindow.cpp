#include "SimCityWindow.h"
#include "ui_SimCityWindow.h"
#include <Controller/QtUnspaghetti.h>

#include <QLine>
#include <QLabel>
#include <QTimer>
#include <QSpinBox>
#include <QGraphicsView>

#include <cmath>
namespace SimCity
{

SimCityWindow::SimCityWindow(Controller::QtUnspaghetti& qtUnspaghetti,
                             QWidget *parent)
  : QMainWindow(parent),
    ui(new Ui::SimCityWindow),
    qtUnspaghetti_(qtUnspaghetti)
{
  ui->setupUi(this);
  fpsCounter_ = new QLabel("0");
  speedCounter_ = new QLabel("x1");

  statusBar()->addWidget(new QLabel("FPS: ", this));
  statusBar()->addWidget(fpsCounter_);
  statusBar()->addWidget(new QLabel("  |  ", this));
  statusBar()->addWidget(new QLabel("Speed: ", this));
  statusBar()->addWidget(speedCounter_);
  sceneTimer = new QTimer(this);
  //connect(ogreSceneTimer, SIGNAL(timeout()),   ogre, SLOT(repaint()));
  connect(ui->actionPlay, SIGNAL(triggered()), &qtUnspaghetti_, SLOT(start()));
  connect(ui->actionStop, SIGNAL(triggered()), &qtUnspaghetti_, SLOT(stop()));
  connect(ui->actionPause, SIGNAL(triggered()), &qtUnspaghetti_, SLOT(pause()));
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
  QSpinBox* frameRateSpin = new QSpinBox(this);

  ui->mainToolBar->addWidget(frameRateSpin);
  frameRateSpin->setRange(1, 120);
  frameRateSpin->setValue(30);
  connect(frameRateSpin,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setFramerate(int)));
  setFramerate(frameRateSpin->value());
  sceneTimer->start();
}

SimCityWindow::~SimCityWindow()
{
  sceneTimer->stop();
  delete ui;
}

void SimCityWindow::setFramerate(int frameRate)
{
  int interval = round(1000.0/(double)frameRate);
  sceneTimer->setInterval(interval);
}

}//namespace SimCity
