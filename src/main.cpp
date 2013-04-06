#include <QApplication>

#include <iostream>
#include <boost/thread/thread.hpp>

#include "View/SimCityWindow.h"
#include "Model/StaticBaseDriver.h"
#include "Model/Model.h"
#include "Model/World.h"
#include "Model/ObjectManager.h"

using namespace SimCity::Model;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SimCityWindow w;
  w.show();

  Model m;
  m.addSimulationPart(SimulationPartPtr(new World("simcity",
                                                  "simcity",
                                                  "simcity")));
  m.addSimulationPart(SimulationPartPtr(new ObjectManager()));
  m.start();

  int result = a.exec();
  m.stop();
  return result;
}
