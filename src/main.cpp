#include <QApplication>
#include "View/SimCityWindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SimCityWindow w;
  w.show();

  return a.exec();
}