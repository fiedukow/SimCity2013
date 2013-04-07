#include <QApplication>

#include <iostream>
#include <boost/thread/thread.hpp>

#include "View/SimCityWindow.h"
#include "Model/StaticBaseDriver.h"
#include "Model/Model.h"
#include "Model/World.h"
#include "Model/ObjectManager.h"
#include "Controller/QtUnspaghetti.h"
#include "Controller/Controller.h"

using namespace SimCity;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Model::Model model;
  Controller::Events::EventQueue eq;
  Controller::QtUnspaghetti qtUn(eq);
  Controller::Controller controller(qtUn, eq, model);
  SimCityWindow w(qtUn);
  w.show();

  model.addSimulationPart(Model::SimulationPartPtr(new Model::World("simcity",
                                                                    "simcity",
                                                                    "simcity")));
  model.addSimulationPart(Model::SimulationPartPtr(new Model::ObjectManager()));

  int result = a.exec();
  model.stop();
  return result;
}
