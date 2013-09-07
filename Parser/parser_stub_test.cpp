#include <iostream>
#include<vector>
#include<string>
#include "parser.h"

int main(int argc, char* argv[])
{
  set_codes();

  std::string test_string = "";
  // now create a real test string
  for(int i = 0; i < codes.size(); ++i)
  {
    test_string += char(27);
    test_string += (codes[i].get_code());
  }

  std::cout << "Currently, many codes are skipped, no idea why" << std::endl;

  for(int i = 0; i < test_string.length(); ++i)
  {
    scan_letter(test_string[i]);
  }
  
  return 0;
}
