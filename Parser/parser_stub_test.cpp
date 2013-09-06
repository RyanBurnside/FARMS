#include <iostream>
#include<vector>
#include<string>
#include "parser.h"

int main(int argc, char* argv[])
{
  set_codes();
 
  if(argc > 1)
  {
    std::cout << "Got test string: " << argv[1] << std::endl;
    for(int i = 0; i < std::string(argv[1]).length(); ++i)
    {
      scan_letter(argv[1][i]);
    }
  }
  return 0;
}
