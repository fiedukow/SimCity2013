#include <QApplication>

#include <iostream>
#include <boost/thread/thread.hpp>

#include "View/SimCityWindow.h"
#include "Model/StaticBaseDriver.h"
#include "Model/Model.h"

using namespace SimCity::Model;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  SimCityWindow w;
  w.show();
  /*
   * DBConnection
   */
//  StaticBaseDriver dbDriver("dbname=simcity "
//                            "user=simcity "
//                            "password=simcity");

//  Map map = dbDriver.getMap();
//  for(const Street& street : map.edges)
//  {
//    std::cout << "FROM: ( "
//              << street.first->lat
//              << ", "
//              << street.first->lon
//              << " )    \tTO: ( "
//              << street.second->lat
//              << ", "
//              << street.second->lon
//              << " )" << std::endl;
//  }

  Model m;
  boost::thread th(boost::ref(m));

  int result = a.exec();
  m.stopAllThreads();
  th.join();
  return result;
}
