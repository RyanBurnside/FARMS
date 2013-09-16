// A simple struct to hold character code string and english meaning.
// Useful for debugging

#include<string>
#include<vector>
#include<iostream>

class Chr_code
{
private:
  std::string code;           // Holds escape code to be searched for
  std::string desc;           // English description of code for debugging
  bool still_possible;        // Marker to  keep searching against string_code
  bool contains_number;       // Special processing required
  unsigned int search_index;  // The current letter to be searched against

  std::vector<std::string> arguments; // Holds a list of string arguments
  unsigned int current_parameter;  // Holds the current parameter to fill
  static unsigned int num_invalid;  // Holds number of invalid codes
  static bool pattern_compleation_mode;
  static std::vector<Chr_code> codes;

public:
  Chr_code(std::string code = "", std::string desc = "", 
	   bool contains_number = false);
  std::string get_code();
  std::string get_desc();
  unsigned int get_num_arguments();
  std::string get_argument(unsigned int index);
  void reset();
  bool still_valid();
  bool now_matches(char c);

  // Static functions
  static void reset_codes();
  static void scan_letter(char c);
  static void set_codes();
};
