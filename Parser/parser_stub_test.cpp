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
    test_string.append("\33");
    test_string.append(codes[i].get_code());
  }
  std::cout << "If you can see this you need to be reading it from a hex" <<
    "editor and not a terminal, ensure that no NULL \0 or odd characters" <<
    "are being written to the string!" << std::endl;
  for(int i = 0; i < test_string.length(); ++i)
  {
    scan_letter(test_string[i]);
  }
  return 0;
}
