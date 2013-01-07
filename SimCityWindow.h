#ifndef SIMCITYWINDOW_H
#define SIMCITYWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class SimCityWindow;
}

class SimCityWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit SimCityWindow(QWidget *parent = 0);
  ~SimCityWindow();

private:
  Ui::SimCityWindow *ui;
  QLabel* fpsCounter_;
  QLabel* speedCounter_;
};

#endif // SIMCITYWINDOW_H
