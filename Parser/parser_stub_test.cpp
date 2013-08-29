#include <iostream>
#include <string>
#include "parser.h"


int main(int argc, char* argv[])
{
  chr_code a("fake-code", "Does stuff with the things");
  std::cout << "a's code is: " << a.code << "\na's desc is: " << a.desc 
	    << std::endl;
}
