#include "Chr_code.h"


int main(int argc, char* argv[])
{
  Chr_code::set_codes();

  std::string test_string = "";
  test_string.append("\033");
  test_string.append("[~P,0,128,255;");
  
  for(int i = 0; i < test_string.size(); ++i)
  {
    Chr_code::scan_letter(test_string[i]);
  }
  return 0;
}
