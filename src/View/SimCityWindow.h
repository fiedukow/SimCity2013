#ifndef SIMCITYWINDOW_H
#define SIMCITYWINDOW_H

#include <QMainWindow>
#include <View/OgreWidget.h>

namespace Ui {
class SimCityWindow;
}

class QTimer;
class QLabel;

class SimCityWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SimCityWindow(QWidget *parent = 0);
  ~SimCityWindow();

public slots:
  void setFramerate(int frameRate);

private:
  Ui::SimCityWindow *ui;
  QLabel* fpsCounter_;
  QLabel* speedCounter_;
  QTimer* ogreSceneTimer;
  uint currentFrameInterval;
};

#endif // SIMCITYWINDOW_H
