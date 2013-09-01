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

/*
TODO
("EscLineColumn", "Move cursor to v,h location")
none 	Set ANSI (versus VT52) 	DECANM
*/

class chr_code
{
public:
  std::string code;    // Holds escape code to be searched for
  std::string desc;    // English description of code for debugging
  bool still_possible; // Marker to  keep searching against string_code

  chr_code(std::string code = "", std::string desc = "")
  {
    this->code = code;
    this->desc = desc;
    this->still_possible = true;
  }
};

chr_code chr_codes[] =
{
  // Note, this assumes that you've found the esc char in the search string
  // This all start with esc and therefore it is not stored here in the matches

chr_code("[20h", "Set new line mode"),
chr_code("[?1h", "Set cursor key to application"),

chr_code("[?3h", "Set number of columns to 132"),
chr_code("[?4h", "Set smooth scrolling"),
chr_code("[?5h", "Set reverse video on screen"),
chr_code("[?6h", "Set origin to relative"),
chr_code("[?7h", "Set auto-wrap mode"),
chr_code("[?8h", "Set auto-repeat mode"),
chr_code("[?9h", "Set interlacing mode"),

chr_code("[20l", "Set line feed mode"),
chr_code("[?1l", "Set cursor key to cursor"),
chr_code("[?2l", "Set VT52 (versus ANSI)"),
chr_code("[?3l", "Set number of columns to 80"),
chr_code("[?4l", "Set jump scrolling"),
chr_code("[?5l", "Set normal video on screen"),
chr_code("[?6l", "Set origin to absolute"),
chr_code("[?7l", "Reset auto-wrap mode"),
chr_code("[?8l", "Reset auto-repeat mode"),
chr_code("[?9l", "Reset interlacing mode"),

chr_code("[=", "Set alternate keypad mode"),
chr_code("[>", "Set numeric keypad mode"),

chr_code("[(A", "Set United Kingdom G0 character set"),
chr_code("[)A", "Set United Kingdom G1 character set"),
chr_code("[(B", "Set United States G0 character set"),
chr_code("[)B", "Set United States G1 character set"),
chr_code("[(0", "Set G0 special chars. & line set"),
chr_code("[)0", "Set G1 special chars. & line set"),
chr_code("[(1", "Set G0 alternate character ROM"),
chr_code("[)1", "Set G1 alternate character ROM"),
chr_code("[(2", "Set G0 alt char ROM and spec."),
chr_code("[)2", "Set G1 alt char ROM and spec."), 

chr_code("[N", "Set single shift 2"),
chr_code("[O", "Set single shift 3"),

chr_code("[m", "Turn off character attributes"),
chr_code("[0m", "Turn off character attributes"),
chr_code("[1m", "Turn bold mode on"),
chr_code("[2m", "Turn low intensity mode on"),
chr_code("[4m", "Turn underline mode on"),
chr_code("[5m", "Turn blinking mode on"),
chr_code("[7m", "Turn reverse video on"),
chr_code("[8m", "Turn invisible text mode on"),

chr_code("[<v>;<v>r", "Set top and bottom line#s of a window"),

chr_code("[<n>A", "Move cursor up n lines"),
chr_code("[<n>B", "Move cursor down n lines"),
chr_code("[<n>C", "Move cursor right n lines"),
chr_code("[<n>D", "Move cursor left n lines"),
chr_code("[H", "Move cursor to upper left corner"),
chr_code("[;H", "Move cursor to upper left corner"),
chr_code("[<v>;<h>H", "Move cursor to screen location v,h"),
chr_code("[f", "Move cursor to upper left corner"),
chr_code("[;f", "Move cursor to upper left corner"),
chr_code("[<v>;<h>f", "Move cursor to screen location v,h"),
chr_code("[D", "Move/scroll window up one line"),
chr_code("[M", "Move/scroll window down one line"),
chr_code("[E", "Move to next line"),
chr_code("[7", "Save cursor position and attributes"),
chr_code("[8", "Restore cursor position and attributes"),

chr_code("[H", "Set a tab at the current column"),
chr_code("[g", "Clear a tab at the current column"),
chr_code("[0g", "Clear a tab at the current column"),
chr_code("[3g", "Clear all tabs"),

chr_code("[#3", "Double-height letters, top half"),
chr_code("[#4", "Double-height letters, bottom half"),
chr_code("[#5", "Single width, single height letters"),
chr_code("[#6", "Double width, single height letters"),

chr_code("[K", "Clear line from cursor right"),
chr_code("[0K", "Clear line from cursor right"),
chr_code("[1K", "Clear line from cursor left"),
chr_code("[2K", "Clear entire line"),

chr_code("[J", "Clear screen from cursor down"),
chr_code("[0J", "Clear screen from cursor down"),
chr_code("[1J", "Clear screen from cursor up"),
chr_code("[2J", "Clear entire screen"),

chr_code("[5n", "Device status report"),
chr_code("[0n", "Response: terminal is OK"),
chr_code("[3n", "Response: terminal is not OK"),

chr_code("[6n", "Get cursor position"),
chr_code("[<v>;<h>R", "Response: cursor is at v,h"),

chr_code("[c", "Identify what terminal type"),
chr_code("[0c", "Identify what terminal type (another)"),
chr_code("[?1;<n>0c", "Response: terminal type code n"),

chr_code("[c", "Reset terminal to initial state"),

chr_code("[#8", "Screen alignment display"),
chr_code("[2;1y", "Confidence power up test"),
chr_code("[2;2y", "Confidence loopback test"),
chr_code("[2;9y", "Repeat power up test"),
chr_code("[2;10y", "Repeat loopback test"),

chr_code("[0q", "Turn off all four leds"),
chr_code("[1q", "Turn on LED #1"),
chr_code("[2q", "Turn on LED #2"),
chr_code("[3q", "Turn on LED #3"),
chr_code("[4q", "Turn on LED #4"),

// All codes below are for use in VT52 compatibility mode.

chr_code("[<", "Enter/exit ANSI mode (VT52)"),

chr_code("[=", "Enter alternate keypad mode"),
chr_code("[>", "Exit alternate keypad mode"),

chr_code("[F", "Use special graphics character set"),
chr_code("[G", "Use normal US/UK character set"),

chr_code("[A", "Move cursor up one line"),
chr_code("[B", "Move cursor down one line"),
chr_code("[C", "Move cursor right one char"),
chr_code("[D", "Move cursor left one char"),
chr_code("[H", "Move cursor to upper left corner"),
chr_code("[<v><h>", "Move cursor to v,h location"),
chr_code("[I", "Generate a reverse line-feed"),

chr_code("[K", "Erase to end of current line"),
chr_code("[J", "Erase to end of screen"),

chr_code("[Z", "Identify what the terminal is"),
chr_code("[/Z", "Correct response to ident")
};

