#include <iostream>
#include <string>
#include "parser.h"


int main(int argc, char* argv[])
{
  if(argc > 1)
    std::cout << argv[1];

  std::cout << char(27) << "[E" << "Hello world";
}
