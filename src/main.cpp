#include <QApplication>

#include "View/SimCityWindow.h"
#include "Model/StaticBaseDriver.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SimCityWindow w;
  w.show();
  /*
   * DBConnection
   */
  StaticBaseDriver dbDriver("dbname=simcity "
                            "user=simcity "
                            "password=ssimcity");

  return a.exec();
}
