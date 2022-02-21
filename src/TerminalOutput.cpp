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
    //info about notation: https://www.youtube.com/watch?v=pXhcPJK5cMc (http://docopt.org/)
    //double dashes? https://youtu.be/pXhcPJK5cMc?t=959
    println("Usage: ", str.c_str(), " [OPTIONS]...  (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-align <hAlign>] [OPTIONS]...  (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-s ( <s1> | <s1> <s2> )]  [OPTIONS]... (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-fg <color> | -bg <color> | -fg_sel <color> | -bg_sel <color>]... [OPTIONS]... (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-pos <vAlign> <hAlign>] [OPTIONS]... (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-margin <vMargin> <hMargin>] [OPTIONS]... (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-title  <titleLine>...] [OPTIONS]... (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-descriptions  <descriptions>...] [OPTIONS]... (-lines <line>...)");
    println("Usage: ", str.c_str(), " [-width  <width_num>] [OPTIONS]... (-lines <line>...)");
    println("  Ask the user to select between options");
    println();
    println("OPTIONS     Option description");
    println("  -help     Prints this help page.");
    println("  -title    A title displayed above them menu.  This option must be followed by titleLine argument(s).");
    println("  -lineDes  Description for selected line.  This option must be followed by descriptions argument(s).");
    println(" -align     Alignment of each line. This option must be followed hAlign argument");
    println("  -fg       Set forground color of the menu. This option must be follwed by a color argument.");
    println("  -bg       Set background color of the menu. This option must be follwed by a color argument.");
    println("  -fg_sel   Set forground color of the selected item.  This option must be follwed by a color argument.");
    println("  -bg_sel   Set background color of the selected item.  This option must be follwed by a color argument.");
    println("  -s        Set a different symbol(s)/character(s) surrounding the selected text.");
    println("            This option must be followed by argument s1 or arguments s1 and s2.");
    println("  -cq       No selection characters will be displayed in front and at end selected text.");
    println("  -q        Do not print selection number");
    println("  -margin   Outer margin.  This option must be followed by a vMargin and hMargin arguments.");
    println("  -pos      Menu position on the screen. This option must be followed by a vAlign and hAlign arguments.");
    println("  -width    Set the total width of the menu.  This option must be followed by the with_num argument.");
    println("  -box      Surround menu with a box.");
    println
    ();
    println("COMMANDS    Command description");
    println("  -lines     This command must be followed by one or more line");
    println();
    println("ARGUMENTS    Argument description");
    println("  line       Text of each selectable item displayed in the menu.  Best to have this a double quoted text.");
    println("  titleLine  Text displayed above the menu.  Best to double quote and align by using spaces within quotes.");
    println("             Do not start a titleLine with the '-' character.");
    println("  descriptions   Text displayed below the menu.  Best to double quote and align by using spaces within quotes.");
    println("             No line is allowed to start with the character '-' because it will be considered a option.");
    println("             Do not start a descriptions with the '-' character.");
    println("             These arguments should have the same count as the line arguments.");
    println("  s1         Character in front of or surrounding selected line.");
    println("  s2         Character at end of the selected line.");
    println("  color      Must be one of the following keywords:");
    println("             black, red, green, yellow, blue, magenta, cyan and white.");
    println("  vAlign     Vertical alignment can be one of these keywords top, middle or bottom.");
    println("  hAlign     Horizontal alignment can be one of these keywords left, center or right.");
    println("  vMargin    A number representing the vertical margin of the menu.");
    println("  hMargin    A number representing the horizontal margin of the menu.");
    println("  width_num  A number representing the total width of the menu. Note that, this number will be ignored If ");
    println("             it is lower than the with needed to display the longest line.");
    
    println();
}