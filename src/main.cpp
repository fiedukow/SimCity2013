#include <QApplication>

#include <iostream>

#include "View/SimCityWindow.h"
#include "Model/StaticBaseDriver.h"

using namespace SimCity::Model;

int main(int argc, char *argv[])
{
//  QApplication a(argc, argv);
//  SimCityWindow w;
//  w.show();
  /*
   * DBConnection
   */
  StaticBaseDriver dbDriver("dbname=simcity "
                            "user=simcity "
                            "password=simcity");
  std::vector<StreetNode> nodes = dbDriver.getStreetNodes();
  for(const StreetNode& node : nodes)
    std::cout << node.nodeId << " "
              << node.lat << " "
              << node.lon << " "
              << node.mos << std::endl;

//  return a.exec();
}
