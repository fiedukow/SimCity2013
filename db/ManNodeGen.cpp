#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
  std::cerr << "argv[1] = ilosc_przecznic\n"
            << "argv[2] = odleglosc_miedzy_przecznicami\n"
            << "argv[3] = punkt_startowy_przecznic_x\n"
            << "argv[4] = punkt startowy_przecznic_y\n";

  int    n = atoi(argv[1]);
  double d = atof(argv[2]);
  double x = atof(argv[3]);
  double y = atof(argv[4]); 

  std::cout << "BEGIN;" << std::endl;
  std::cout << "INSERT INTO StreetNodes (streetNodeId, lat, lon)" << std::endl;
  std::cout << "VALUES" << std::endl;
  int id = 0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      std::cout << "(" << id++ << ", " << x+(i*d) << ", " << y+(j*d) << ")" 
                << ((i!=n-1 || j!=n-1) ? "," : ";") << std::endl;


  std::cout << "INSERT INTO Streets (firstNode, secondNode)" << std::endl;
  std::cout << "VALUES" << std::endl;

  id = 0;
  for(int i = 0; i < n-1; ++i)
  {
    for(int j = 0; j < n-1; ++j)
    {      
      std::cout << "(" << id << ", " << id+n << ")," << std::endl;   
      std::cout << "(" << id << ", " << id+1 << ")," << std::endl;
      ++id;
    }
    ++id;
  }

  id = n*(n-1);
  for(int i = 0; i < n-1; ++i)
  {
    std::cout << "(" << id;
    std::cout << ", " << ++id << ")," << std::endl;
  }
  
  id = n-1;
  for(int i = 0; i < n-1; ++i)
  {
    std::cout << "(" << id << ", ";
    id += n;
    std::cout << id << ")"
              << ((i != n-2) ? "," : ";") << std::endl;            
  }

  std::cout << "INSERT INTO Sensors (typeid, lon, lat, mos, range)" << std::endl;
  std::cout << "VALUES" << std::endl;

  id = 0;
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      std::cout << "(0" << ", " << x+(i*d) << ", " << y+(j*d) << ", 0, 80)" 
                << ((i!=n-1 || j!=n-1) ? "," : ";") << std::endl;



  std::cout << "END;" << std::endl;
}
