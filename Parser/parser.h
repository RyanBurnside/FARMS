/*
Algorithm overview
input string
table of matches to look through

0. Make two lists, one for linear matches and one for regular expression 
matches (linear table should be searched first)
1. find the position of the first ESC character if exists
2. consult the linear matches table and regex matches table
3. if a code is found, call the proper function, modify buffer
4. move the search cursor after the found term
5. if it is not found print the character sequence to screen
 */

// A simple struct to hold character code string and english meaning.
// Useful for debugging

class chr_code
{
public:
  std::string code;
  std::string desc;

  chr_code(std::string code = "", std::string desc = "")
  {
    this->code = code;
    this->desc = desc;
  }

};





