// A simple struct to hold character code string and english meaning.
// Useful for debugging

class Chr_code
{
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

  void reset()
  {
    // Reset the search index and set it possible once more
    this->still_possible = true;
    this->search_index = 0;
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
      if (search_index == code.length())
      {
	// The word has failed, return false
	still_possible = false;
	return false;
      }

      // Enter char matching conditions since the index is valid
      char considered_char = code[search_index];
      
      // Test to see if character matches search_index
      if(considered_char == c)
      {
	// Character matches final char and code matches!
	if(search_index == code.length() -1)
	{
	  still_possible = false;
	  return true;
	}
	// The character matches but the search is not yet complete, iterate
	search_index++;
	return false;
      }
      else
      {
	// The word has failed, return false
	still_possible = false;
	return false;
      }
    }
    else
    {
      return false;
    }
  }

private:
  std::string code;     // Holds escape code to be searched for
  std::string desc;     // English description of code for debugging
  bool still_possible;  // Marker to  keep searching against string_code
  bool contains_number; // Special processing required
  bool search_index;

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
  // Strange bug the lines starting with [? get ignored...
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

  codes.push_back(Chr_code("[<v>;<v>r", 
			   "Set top and bottom line #s of a window", true));

  codes.push_back(Chr_code("[<n>A", "Move cursor up n lines", true));
  codes.push_back(Chr_code("[<n>B", "Move cursor down n lines", true));
  codes.push_back(Chr_code("[<n>C", "Move cursor right n lines", true));
  codes.push_back(Chr_code("[<n>D", "Move cursor left n lines", true));
  codes.push_back(Chr_code("[H", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[;H", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[<v>;<h>H", "Move cursor to screen location v,h",
			   true));
  codes.push_back(Chr_code("[f", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[;f", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[<v>;<h>f", "Move cursor to screen location v,h",
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
  codes.push_back(Chr_code("[<v>;<h>R", "Response: cursor is at v,h", true));

  codes.push_back(Chr_code("[c", "Identify what terminal type"));
  codes.push_back(Chr_code("[0c", "Identify what terminal type (another)"));
  codes.push_back(Chr_code("[?1;<n>0c", "Response: terminal type code n", 
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

  // All codes below are for use in VT52 compatibility mode.

  codes.push_back(Chr_code("[<", "Enter/exit ANSI mode (VT52)"));

  codes.push_back(Chr_code("[=", "Enter alternate keypad mode"));
  codes.push_back(Chr_code("[>", "Exit alternate keypad mode"));

  codes.push_back(Chr_code("[F", "Use special graphics character set"));
  codes.push_back(Chr_code("[G", "Use normal US/UK character set"));

  codes.push_back(Chr_code("[A", "Move cursor up one line"));
  codes.push_back(Chr_code("[B", "Move cursor down one line"));
  codes.push_back(Chr_code("[C", "Move cursor right one char"));
  codes.push_back(Chr_code("[D", "Move cursor left one char"));
  codes.push_back(Chr_code("[H", "Move cursor to upper left corner"));
  codes.push_back(Chr_code("[<v><h>", "Move cursor to v,h location", true));
  codes.push_back(Chr_code("[I", "Generate a reverse line-feed"));

  codes.push_back(Chr_code("[K", "Erase to end of current line"));
  codes.push_back(Chr_code("[J", "Erase to end of screen"));

  codes.push_back(Chr_code("[Z", "Identify what the terminal is"));
  codes.push_back(Chr_code("[/Z", "Correct response to ident"));
}

void scan_letter(char c)
{

  // Scans through all possible strings, 
  // if one does not match sets still_possible to false
  // if the last searched positon = last position set still_possible to false
  // if the char matches, and is the end of a pattern, return pattern
  //   reset all items and pattern_compleation_mode = false
  std::vector<Chr_code>::iterator i;
  
  if(c == char(27))
  {
    // Escape found, set pattern_completion mode, reset all codes
    pattern_compleation_mode = true;
    reset_codes();
    return;
  }

  // If currently inside a pattern, process the patterns
  if(pattern_compleation_mode)
  {
    for(i = codes.begin(); i != codes.end(); ++i)
    {
      if(i->still_valid())
      {
	if(i->now_matches(c))
	{
	  std::cout << "FOUND ONE!" << "Code is: " << i->get_code()
	            << " Description is: " << i->get_desc() << std::endl;
	  // Now reset the state
	  pattern_compleation_mode = false;
	  reset_codes();
	}
      }
    }
  }
}
