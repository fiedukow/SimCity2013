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
  Model::WorldPtr world(new Model::World("simcity",
                                         "simcity",
                                         "simcity"));
  Model::Model model(world);
  Controller::Events::EventQueue eq;
  Controller::QtUnspaghetti qtUn(eq);
  Controller::Controller controller(qtUn, eq, model);

  model.addSimulationPart(std::dynamic_pointer_cast<Model::SimulationPart>(world));
  model.addSimulationPart(Model::SimulationPartPtr(new Model::ObjectManager()));

  View::SimCityWindow w(qtUn);
  w.show();

  int result = a.exec();
  model.stop();
  return result;
}
