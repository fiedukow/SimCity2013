#ifndef SIMCITYWINDOW_H
#define SIMCITYWINDOW_H

#include <QMainWindow>

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
};

#endif // SIMCITYWINDOW_H
