// A simple struct to hold character code string and english meaning.
// Useful for debugging

class Chr_code
{
private:
  std::string code;           // Holds escape code to be searched for
  std::string desc;           // English description of code for debugging
  bool still_possible;        // Marker to  keep searching against string_code
  bool contains_number;       // Special processing required
  unsigned int search_index;  // The current letter to be searched against
  std::vector<std::string> arguments; // Holds a list of string arguments
  unsigned int current_parameter; // Holds the current parameter to fill
public:
  Chr_code(std::string code = "", std::string desc = "", 
	   bool contains_number = false)
  {
    this->code = code;
    this->desc = desc;
    this->still_possible = true;

    // Contains a number, requires special number argument processing
    this->contains_number = contains_number; 
    this->search_index = 0;

    // Count the number of * (numerical argument placeholders)
    // and make the strings to hold the args.
    if(contains_number)
    {
      for(int i = 0; i < code.size(); ++i)
      {
	if(code[i] == '*')
	{
	  this->arguments.push_back("");
	}
      }
    }
    this->current_parameter = 0;
  }

  std::string get_code()
  {
    // TODO make this pass by ref instead of copy
    return code;
  }

  std::string get_desc()
  {
    // TODO make this pass by ref instead of copy
    return desc;
  }

  unsigned int get_num_arguments()
  {
    return arguments.size();
  }

  std::string get_argument(unsigned int index)
  {
    return arguments[index];
  }

  void reset()
  {
    // Reset the search index and set it possible once more
    still_possible = true;
    search_index = 0;
    current_parameter = 0;
    // Clear the list of captured arguments
    for(unsigned int i = 0; i < arguments.size(); ++i)
    {
      arguments[i] = "";
    }
  }

  bool still_valid()
  {
    return still_possible;
  }

  bool now_matches(char c)
  {
    // This function returns true when the code has been matched fully
    // Each time a char is entered the pattern advances one letter until
    // the pattern matches or is rejected

    if(still_possible == true)
    {
      // Tests to see if index is still valid
      if(search_index == code.size())
      {
	// The word has failed, return false
	still_possible = false;
	return false;
      }

      // Enter char matching conditions since the index is valid
      char considered_char = code[search_index];

      // Test to see if character matches search_index
      if(contains_number && considered_char == '*')
      {
	if(c < 48 || c > 57) // Not a valid number, see if it maches the next
	{
	  if(search_index + 1 < code.size()) // Before than the last index?
	  {
	    if(code[search_index + 1] == c) // Matches next char?
	    {
	      std::cout << "Code: " << code << " Current Parameter: " << 
		current_parameter << std::endl;
	      std::cout << "Caught " << 
		arguments[current_parameter] << std::endl;
	      std::cout << "Moving to next parameter!" << std::endl;
		current_parameter++;
		search_index += 2;
		std::cout << "The seperator was: " << c << std::endl;
		if(search_index == code.size())
		{
		  still_possible = false;
		  return true;
		}
		return false;
	    }
	  }
	  still_possible = false;
	  return false;
	}
	// It is a digit and matches!
	else
	{
	  arguments[current_parameter] += c;
	  return false;
	}
      }
      
      // Found a match
      if(considered_char == c)
      {
	if(search_index == code.size() -1)
	{
	  std::cout << "Compleated term!" << std::endl;
	  still_possible = false;
	  return true;
	}
      }
            
      if(considered_char != c)
      {
	still_possible = false;
	return false;
      }

      if(search_index < code.size())
      {
	search_index++;
	return false;
      }
    }
    return false;
  }
};


bool pattern_compleation_mode;
std::vector<Chr_code> codes;

void reset_codes()
{
  // Resets all codes
  std::vector<Chr_code>::iterator i;
  for(i = codes.begin(); i != codes.end(); ++i)
  {
    i->reset();
  }
}

void set_codes()
{
  // ACHTUNG, ACHTUNG! IN MY CODES * MEANS AN ARGUMENT MUST BE DUG OUT OF THE
  // Chr_code's STRING. It is special syntax notation for this code only.

  pattern_compleation_mode = false;
  codes.push_back(Chr_code("[20h", "Set new line mode"));
  codes.push_back(Chr_code("[?1h", "Set cursor key to application"));
  
  codes.push_back(Chr_code("[?3h", "Set number of columns to 132"));
  codes.push_back(Chr_code("[?4h", "Set smooth scrolling"));
  codes.push_back(Chr_code("[?5h", "Set reverse video on screen"));
  codes.push_back(Chr_code("[?6h", "Set origin to relative"));
  codes.push_back(Chr_code("[?7h", "Set auto-wrap mode"));
  codes.push_back(Chr_code("[?8h", "Set auto-repeat mode"));
  codes.push_back(Chr_code("[?9h", "Set interlacing mode"));

  codes.push_back(Chr_code("[20l", "Set line feed mode"));
  codes.push_back(Chr_code("[?1l", "Set cursor key to cursor"));
  codes.push_back(Chr_code("[?2l", "Set VT52 (versus ANSI)"));
  codes.push_back(Chr_code("[?3l", "Set number of columns to 80"));
  codes.push_back(Chr_code("[?4l", "Set jump scrolling"));
  codes.push_back(Chr_code("[?5l", "Set normal video on screen"));
  codes.push_back(Chr_code("[?6l", "Set origin to absolute"));
  codes.push_back(Chr_code("[?7l", "Reset auto-wrap mode"));
  codes.push_back(Chr_code("[?8l", "Reset auto-repeat mode"));
  codes.push_back(Chr_code("[?9l", "Reset interlacing mode"));

  codes.push_back(Chr_code("[=", "Set alternate keypad mode"));
  codes.push_back(Chr_code("[>", "Set numeric keypad mode"));
  
  codes.push_back(Chr_code("[(A", "Set United Kingdom G0 character set"));
  codes.push_back(Chr_code("[)A", "Set United Kingdom G1 character set"));
  codes.push_back(Chr_code("[(B", "Set United States G0 character set"));
  codes.push_back(Chr_code("[)B", "Set United States G1 character set"));
  codes.push_back(Chr_code("[(0", "Set G0 special chars. & line set"));
  codes.push_back(Chr_code("[)0", "Set G1 special chars. & line set"));
  codes.push_back(Chr_code("[(1", "Set G0 alternate character ROM"));
  codes.push_back(Chr_code("[)1", "Set G1 alternate character ROM"));
  codes.push_back(Chr_code("[(2", "Set G0 alt char ROM and spec."));
  codes.push_back(Chr_code("[)2", "Set G1 alt char ROM and spec."));
  
  codes.push_back(Chr_code("[N", "Set single shift 2"));
  codes.push_back(Chr_code("[O", "Set single shift 3"));
  
  codes.push_back(Chr_code("[m", "Turn off character attributes"));
  codes.push_back(Chr_code("[0m", "Turn off character attributes"));
  codes.push_back(Chr_code("[1m", "Turn bold mode on"));
  codes.push_back(Chr_code("[2m", "Turn low intensity mode on"));
  codes.push_back(Chr_code("[4m", "Turn underline mode on"));
  codes.push_back(Chr_code("[5m", "Turn blinking mode on"));
  codes.push_back(Chr_code("[7m", "Turn reverse video on"));
  codes.push_back(Chr_code("[8m", "Turn invisible text mode on"));
  
  codes.push_back(Chr_code("[*;*r",
   "Set top and bottom line #s of a window", true));
  
  codes.push_back(Chr_code("[*A", "Move cursor up n lines", true));
  codes.push_back(Chr_code("[*B", "Move cursor down n lines", true));
  codes.push_back(Chr_code("[*C", "Move cursor right n lines", true));
  codes.push_back(Chr_code("[*D", "Move cursor left n lines", true));
  codes.push_back(Chr_code("[H", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[;H", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[*;*H", "Move cursor to screen location v,h",
   true));
  codes.push_back(Chr_code("[f", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[;f", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[*;*f", "Move cursor to screen location v,h",
   true));
  
  codes.push_back(Chr_code("[D", "Move/scroll window up one line"));
  codes.push_back(Chr_code("[M", "Move/scroll window down one line"));
  codes.push_back(Chr_code("[E", "Move to next line"));
  codes.push_back(Chr_code("[7", "Save cursor position and attributes"));
  codes.push_back(Chr_code("[8", "Restore cursor position and attributes"));
  
  codes.push_back(Chr_code("[H", "Set a tab at the current column"));
  codes.push_back(Chr_code("[g", "Clear a tab at the current column"));
  codes.push_back(Chr_code("[0g", "Clear a tab at the current column"));
  codes.push_back(Chr_code("[3g", "Clear all tabs"));
  
  codes.push_back(Chr_code("[#3", "Double-height letters, top half"));
  codes.push_back(Chr_code("[#4", "Double-height letters, bottom half"));
  codes.push_back(Chr_code("[#5", "Single width, single height letters"));
  codes.push_back(Chr_code("[#6", "Double width, single height letters"));
  
  codes.push_back(Chr_code("[K", "Clear line from cursor right"));
  codes.push_back(Chr_code("[0K", "Clear line from cursor right"));
  codes.push_back(Chr_code("[1K", "Clear line from cursor left"));
  codes.push_back(Chr_code("[2K", "Clear entire line"));
  
  codes.push_back(Chr_code("[J", "Clear screen from cursor down"));
  codes.push_back(Chr_code("[0J", "Clear screen from cursor down"));
  codes.push_back(Chr_code("[1J", "Clear screen from cursor up"));
  codes.push_back(Chr_code("[2J", "Clear entire screen"));
  
  codes.push_back(Chr_code("[5n", "Device status report"));
  codes.push_back(Chr_code("[0n", "Response: terminal is OK"));
  codes.push_back(Chr_code("[3n", "Response: terminal is not OK"));
  
  codes.push_back(Chr_code("[6n", "Get cursor position"));
  codes.push_back(Chr_code("[*;*R", "Response: cursor is at v,h", true));
  
  codes.push_back(Chr_code("[c", "Identify what terminal type"));
  codes.push_back(Chr_code("[0c", "Identify what terminal type (another)"));
  codes.push_back(Chr_code("[?1;*0c", "Response: terminal type code n",
   true));
  
  codes.push_back(Chr_code("[c", "Reset terminal to initial state"));
  
  codes.push_back(Chr_code("[#8", "Screen alignment display"));
  codes.push_back(Chr_code("[2;1y", "Confidence power up test"));
  codes.push_back(Chr_code("[2;2y", "Confidence loopback test"));
  codes.push_back(Chr_code("[2;9y", "Repeat power up test"));
  codes.push_back(Chr_code("[2;10y", "Repeat loopback test"));
  
  codes.push_back(Chr_code("[0q", "Turn off all four leds"));
  codes.push_back(Chr_code("[1q", "Turn on LED #1"));
  codes.push_back(Chr_code("[2q", "Turn on LED #2"));
  codes.push_back(Chr_code("[3q", "Turn on LED #3"));
  codes.push_back(Chr_code("[4q", "Turn on LED #4"));

  // Custom codes with regex * for number parameters

  // Attribute setting
  codes.push_back(Chr_code("[~P,*,*,*;", "set pen color (R, G, B)", true));
  codes.push_back(Chr_code("[~B,*,*,*;", "set brush color (R, G, B)", true)); 
  codes.push_back(Chr_code("[~W,*;", "set pen width (N)", true));         
  codes.push_back(Chr_code("[~F,*;", "set shape fill (0/1)", true));      
  codes.push_back(Chr_code("[~R,*,*;", "set resolution(x, y)", true));

  // Shape drawing
  codes.push_back(Chr_code("[~l,*,*,*,*;", "draw line (x, y, x2, y2)", true));
  codes.push_back(Chr_code("[~r,*,*,*,*;", "draw rectangle (x, y, x2, y2)",
			   true));           
  codes.push_back(Chr_code("[~t,*,*,*,*,*,*;", 
			   "draw triangle (x, y, x2, y2, x3, y3)", true));    
  codes.push_back(Chr_code("[~o,*,*,*,*;", "draw oval (x, y, x2, y2)", true));               
  codes.push_back(Chr_code("[~p,*,*;", "draw point (x, y)", true));       
  codes.push_back(Chr_code("[~c;", "clear screen with brush color ()", true));        
}

void scan_letter(char c)
{
  // Scans through all possible strings, 
  // if one does not match sets still_possible to false
  // if the last searched positon = last position set still_possible to false
  // if the char matches, and is the end of a pattern, return true

  std::vector<Chr_code>::iterator i;

  // If currently inside a pattern, process the patterns
  if(pattern_compleation_mode == true)
  {
    for(i = codes.begin(); i != codes.end(); ++i)
    {
      if(i->now_matches(c))
      {
	pattern_compleation_mode = false;
	  // CALL THE FUNCTION HERE THEN CLEAR ALL FUNCTIONS
	  // Testing here...
	std::cout << "Found code! " <<  i->get_code() << std::endl;
	for(int j = 0; j < i->get_num_arguments(); ++j)
	{
	  std::cout << i->get_num_arguments() << " arguments found.\n";
	  std::cout << "Argument: " << j <<
	    " is " << i->get_argument(j) << std::endl;
	}
	reset_codes();
	  return;
      }
    }
  }
  
  if(c == char(27))
  {
    // Escape found, set pattern_completion mode, reset all codes
    pattern_compleation_mode = true;
    reset_codes();
    return;
  }
}
