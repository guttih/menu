#include "include/TerminalOutput.h"

TerminalOutput::TerminalOutput()
{
}

TerminalOutput::~TerminalOutput()
{
}

void TerminalOutput::print(const char *str)
{
    cout << str;
}
// void TerminalOutput::print(string str){
//     print(str.c_str());
// }

void TerminalOutput::println()
{
    cout << endl;
}
void TerminalOutput::println(const char *str)
{
    print(str);
    println();
}
void TerminalOutput::println(const char *str1, const char *str2)
{
    print(str1);
    print(str2);
    println();
}
void TerminalOutput::println(const char *str1, const char *str2, const char *str3)
{
    print(str1);
    print(str2);
    ;
    print(str3);
    println();
}

void TerminalOutput::printHelp(const char *appName)
{
    string str = appName;
    size_t i = str.find_last_of('/');
    if (i != string::npos && str.length() > 1 && i < (str.length()-2 ))
    {
        str = str.substr(i + 1);
    }
    //TODO: Add hMargin and vMargin.
    //info about notation: https://www.youtube.com/watch?v=pXhcPJK5cMc (http://docopt.org/)
    println("Usage: ", str.c_str(), " [OPTIONS]...  -menu <menuLine>...");
    println("Usage: ", str.c_str(), " [-align <hAlign>] [OPTIONS]...  -menu <menuLine>...");
    println("Usage: ", str.c_str(), " [-c ( <c1> | <c1> <c2> )]  [OPTIONS]... -menu <menuLine>...");
    println("Usage: ", str.c_str(), " [-fg <color> | -bg <color> | -fg_sel <color> | -bg_sel <color>]...  [OPTIONS]... -menu <menuLine>...");
    println("Usage: ", str.c_str(), " [-pos <vAlign> <hAlign> ] [OPTIONS]... -menu <menuLine>...");
    println("Usage: ", str.c_str(), " [-margin <vMargin> <hMargin> ] [OPTIONS]... -menu <menuLine>...");
    println("Usage: ", str.c_str(), " [-title  <titleLine>... ] [OPTIONS]... -menu <menuLine>...");
    println("  Ask the user to select between options");
    println();
    println("OPTIONS     Option description");
    println("  -help     Prints this help page");
    println("  -title    A title displayed above them menu.  This option must be followed by a string argument.");
    println(" -align     Alignment of each menuLine. This option must be followed hAlign argument");
    println("  -fg       Set forground color of the menu. This option must be follwed by a color argument.");
    println("  -bg       Set background color of the menu. This option must be follwed by a color argument.");
    println("  -fg_sel   Set forground color of the selected item.  This option must be follwed by a color argument.");
    println("  -bg_sel   Set background color of the selected item.  This option must be follwed by a color argument.");
    println("  -c        Select the character(s) surrounding the selected string");
    println("            This option must be followed by argument c1 or arguments c1 and c2.");
    println("  -cq       No selection characters will be displayed in front and at end selected text.");
    println("  -q        Do not print selection number");
    println("  -margin   Outer margin.  This option must be followed by a vMargin and hMargin arguments.");
    println("  -pos      Menu position on the screen. This option must be followed by a vAlign and hAlign arguments.");
    println("  -box      Surround menu with a box.");
    println
    ();
    println("COMMANDS    Command description");
    println("  -menu     This command must be followed by one or more menuLine");
    println();
    println("ARGUMENTS    Argument description");
    println("  menuLine   Text of each selectable item displayed in the menu.  Best to have this a double quoted string.");
    println("  titleLine  Text displayed above the menu.  Best to double quote and align by using spaces within quotes.");
    println("             No line is allowed to start with the character '-' because it will be considered a option.");
    println("  c1         Character in front of or surrounding selected menuLine.");
    println("  c2         Character at end of the selected menuLine.");
    println("  color      Must be one of the following keywords:");
    println("             black, red, green, yellow, blue, magenta, cyan and white.");
    println("  vAlign     Vertical alignment can be one of these keywords top, middle or bottom.");
    println("  hAlign     Horizontal alignment can be one of these keywords left, center or right.");
    println("  vMargin    A number representing the vertical margin of the menu.");
    println("  hMargin    A number representing the horizontal margin of the menu.");
    println();
}