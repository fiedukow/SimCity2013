#include "SimCityWindow.h"
#include "ui_SimCityWindow.h"
#include "OgreWidget.h"

#include <QLine>
#include <QLabel>
#include <QTimer>
#include <QSpinBox>

#include <cmath>

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
  QLayout* lay = new QHBoxLayout(ui->ogreFrame);
  ui->ogreFrame->setLayout(lay);
  lay->setContentsMargins(0, 0, 0, 0);
  OgreWidget* ogre = new OgreWidget(ui->ogreFrame);
  lay->addWidget(ogre);
  ogreSceneTimer = new QTimer(this);
  connect(ogreSceneTimer, SIGNAL(timeout()),   ogre, SLOT(repaint()));
  connect(ui->actionPlay, SIGNAL(triggered()), ogre, SLOT(goForward()));
  connect(ui->actionPause,SIGNAL(triggered()), ogre, SLOT(goBackward()));
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
  ogreSceneTimer->start();
}

SimCityWindow::~SimCityWindow()
{
  ogreSceneTimer->stop();
  delete ui;
}

void SimCityWindow::setFramerate(int frameRate)
{
  int interval = round(1000.0/(double)frameRate);
  ogreSceneTimer->setInterval(interval);
}
