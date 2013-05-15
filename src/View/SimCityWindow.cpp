#include "SimCityWindow.h"
#include "ui_SimCityWindow.h"
#include <Controller/QtUnspaghetti.h>
#include <View/MapScene.h>

#include <QLine>
#include <QLabel>
#include <QTimer>
#include <QSpinBox>
#include <QGraphicsView>
#include <QSlider>

#include <cmath>
#include <iostream>

namespace SimCity
{
namespace View
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
  connect(sceneTimer, SIGNAL(timeout()), &qtUnspaghetti_, SLOT(requestSnapshot()));
  connect(&qtUnspaghetti_, SIGNAL(updateState()), this, SLOT(updateMoveable()));
  connect(ui->actionPlay, SIGNAL(triggered()), &qtUnspaghetti_, SLOT(start()));
  connect(ui->actionStop, SIGNAL(triggered()), &qtUnspaghetti_, SLOT(stop()));
  connect(ui->actionPause, SIGNAL(triggered()), &qtUnspaghetti_, SLOT(pause()));
  connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
  connect(this, SIGNAL(requestNewMapSnapshot()),
          &qtUnspaghetti_, SLOT(requestNewMapSnapshot()));
  connect(&qtUnspaghetti_, SIGNAL(updateMap()),
          this, SLOT(drawMap()));
  connect(ui->carLimit,
          SIGNAL(textChanged(QString)),
          &qtUnspaghetti_,
          SLOT(setCarLimit(QString)));
  connect(ui->pedestrianLimit,
          SIGNAL(textChanged(QString)),
          &qtUnspaghetti_,
          SLOT(setPedestrianLimit(QString)));

  QLabel* speedLabel = new QLabel("Simulation Speed: ", this);
  QSpinBox* frameRateSpin = new QSpinBox(this);
  QSlider* speedSlider = new QSlider(Qt::Horizontal, this);
  speedSlider->setValue(5);

  ui->mainToolBar->addWidget(frameRateSpin);
  ui->mainToolBar->addSeparator();
  ui->mainToolBar->addWidget(speedLabel);
  ui->mainToolBar->addWidget(speedSlider);
  connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(setSpeed(int)));
  frameRateSpin->setRange(1, 100);
  frameRateSpin->setValue(30);
  connect(frameRateSpin,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setFramerate(int)));
  setFramerate(frameRateSpin->value());
  sceneTimer->start();
  emit requestNewMapSnapshot();
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

void SimCityWindow::drawMap()
{
  Model::MapPtr map = qtUnspaghetti_.getMapSnapshot();
  QGraphicsScene* scene = new MapScene(map, ui->view2D);
  connect(ui->actionMapScalePlus,
          SIGNAL(triggered()),
          scene,
          SLOT(scalePlus()));
  connect(ui->actionMapScaleMinus,
          SIGNAL(triggered()),
          scene,
          SLOT(scaleMinus()));
  connect(ui->seeCarsCB, SIGNAL(toggled(bool)), scene, SLOT(setCarsVisible(bool)));
  connect(ui->seeRoadsCB, SIGNAL(toggled(bool)), scene, SLOT(setMapVisible(bool)));
  connect(ui->seeSensorsCB, SIGNAL(toggled(bool)), scene, SLOT(setSensorsVisible(bool)));
  connect(ui->seePedestriansCB, SIGNAL(toggled(bool)), scene, SLOT(setPedestriansVisible(bool)));
  ui->view2D->setRenderHints(QPainter::Antialiasing
                             | QPainter::SmoothPixmapTransform);
  ui->view2D->setScene(scene);
}

void SimCityWindow::updateMoveable()
{
  //TODO count fps
  MapScene* scene = dynamic_cast<MapScene*>(ui->view2D->scene());
  if(!scene)
    return;
  scene->showNewMovable(qtUnspaghetti_.getSnapshots());
}

void SimCityWindow::setSpeed(int speed)
{
  double endSpeed;
  if(speed < 5)
    endSpeed = 1/pow(2.0, 5.0-speed);
  else
    endSpeed = speed-4;

  QString text = QString("x") + QString::number(endSpeed);
  speedCounter_->setText(text);
  qtUnspaghetti_.setSimulationSpeed(endSpeed);
}

}//namespace View
}//namespace SimCity
