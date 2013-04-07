#ifndef SIMCITYWINDOW_H
#define SIMCITYWINDOW_H

#include <QMainWindow>
#include <Model/DBDataStructures.h>

namespace Ui {
class SimCityWindow;
}

class QTimer;
class QLabel;

namespace SimCity
{

namespace Controller
{
class QtUnspaghetti;
}

namespace View
{

class SimCityWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SimCityWindow(Controller::QtUnspaghetti& qtUnspaghetti,
                         QWidget *parent = 0);
  ~SimCityWindow();

public slots:
  void setFramerate(int frameRate);
  void drawMap();

signals:
  void requestNewMapSnapshot();

private:
  Ui::SimCityWindow *ui;
  QLabel* fpsCounter_;
  QLabel* speedCounter_;
  QTimer* sceneTimer;
  uint currentFrameInterval;
  Controller::QtUnspaghetti& qtUnspaghetti_;
};

}//namespace View
}//namespace SimCity

#endif // SIMCITYWINDOW_H
