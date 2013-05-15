#include <QApplication>

#include <iostream>
#include <boost/thread/thread.hpp>

#include "View/SimCityWindow.h"
#include "Model/StaticBaseDriver.h"
#include "Model/Model.h"
#include "Model/World.h"
#include "Model/Exceptions.h"
#include "Model/ObjectManager.h"
#include "Controller/QtUnspaghetti.h"
#include "Controller/Controller.h"

using namespace SimCity;

struct Params
{
  std::string dbName;
  std::string dbUserName;
  std::string dbUserPassword;
};

Params getParams(int argc, char* argv[]);
void showUsage(char* progName);

int main(int argc, char *argv[])
{
  Params params = getParams(argc, argv);
  QApplication a(argc, argv);
  Model::Model model(params.dbName, params.dbUserName, params.dbUserPassword);
  Controller::Events::EventQueue eq;
  Controller::QtUnspaghetti qtUn(eq);
  Controller::Controller controller(qtUn, eq, model);

  View::SimCityWindow w(qtUn);
  w.show();

  int result = a.exec();
  model.stop();
  return result;
}

Params getParams(int argc, char* argv[])
{
  if(argc < 4)
  {
    showUsage(argv[0]);
    exit(1);
  }

  Params result = { argv[1], argv[2], argv[3] };
  return result;
}

void showUsage(char* progName)
{
  std::cout << "Usage: "
            << progName
            << " <dbName> <dbUserName> <dbPassword>"
            << std::endl;
}
