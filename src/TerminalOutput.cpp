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
    println("Usage: ", str.c_str(), " [OPTIONS]...  -menu <menustring>...");
    println("Usage: ", str.c_str(), " [--align ( <left> | <center> | <right> )] [OPTIONS]...  -menu <menustring>...");
    println("Usage: ", str.c_str(), " [-c ( <c1> | <c1> <c2> )]  [OPTIONS]... -menu <menustring>...");
    println("Usage: ", str.c_str(), " [-fg <color> | -bg <color> | -fg_sel <color> | -bg_sel <color>]...  [OPTIONS]... -menu <menustring>...");
    println("  Ask the user to select between options");
    println();
    println("OPTIONS       Option description");
    println("  -help       Prints this help page");
    println(" --align      Alignment of menustrings this option must be followed by one");
    println("              these words left, center or right.  Default is left.");
    println("  -fg         Set forground color of the menu. This option must be follwed by a color argument.");
    println("  -bg         Set background color of the menu. This option must be follwed by a color argument.");
    println("  -fg_sel     Set forground color of the selected item.  This option must be follwed by a color argument.");
    println("  -bg_sel     Set background color of the selected item.  This option must be follwed by a color argument.");
    println("  -c          Must be followed by one or two characters which will be added.");
    println("  -cq         No selection characters will be displayed in front and at end selected text.");
    println("  -q          Do not print selection number");
    println("  -box        Surround menu with a box.");
    println
    ();
    println("COMMANDS      Command description");
    println("  -menu       This command must be followed by one or more menustring");
    println();
    println("ARGUMENTS     Argument description");
    println("  c1          Character in front of or surrounding selected menustring.");
    println("  c2          Character at end of the selected menustring.");
    println("  color       Must be one of the following keywords: black,red,green,yellow,blue,magenta,cyan,white.");
    println("  menustring  Must be a double quoted string.");
    println();
}