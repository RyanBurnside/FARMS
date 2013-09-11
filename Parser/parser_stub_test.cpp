#include <iostream>
#include <vector>
#include <string>
#include "parser.h"

int main(int argc, char* argv[])
{
  set_codes();

  std::string test_string = "";
  // now create a real test string
  for(int i = 0; i < codes.size(); ++i)
  {
    test_string.append("\033");
    test_string.append(codes[i].get_code());
  }

  for(int i = 0; i < test_string.size(); ++i)
  {
    scan_letter(test_string[i]);
  }
  return 0;
}
