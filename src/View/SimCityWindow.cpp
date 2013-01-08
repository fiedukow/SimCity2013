#include "SimCityWindow.h"
#include "ui_SimCityWindow.h"
#include "OgreWidget.h"
#include <QLine>
#include <QTimer>

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
  QTimer* timer = new QTimer(this);
  timer->setInterval(30);
  connect(timer, SIGNAL(timeout()), ogre, SLOT(repaint()));
  connect(ui->actionPlay,SIGNAL(triggered()), ogre, SLOT(goForward()));
  connect(ui->actionPause,SIGNAL(triggered()), ogre, SLOT(goBackward()));
  timer->start();
}

SimCityWindow::~SimCityWindow()
{
  delete ui;
}
