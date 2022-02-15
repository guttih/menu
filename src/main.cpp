// build params: gcc main.cpp -o main -lncursesw -lstdc++
// sudo yum install ncurses-devel
#include "include/MenuMaker.h"
#include "include/ArgumentParser.h"
#include "include/TerminalOutput.h"

// see also https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
// tutorial https://www.youtube.com/watch?v=2tWN6ntNo4w
// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/keys.html
int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");
    ArgumentParser parser(argv, argc);
    if (!parser.isValid())
    {
        TerminalOutput::println("Error: Invalid argument: \"", parser.errorString(), "\".");
        return 255;
    }
    else if (parser.isPrintHelp())
    {
        TerminalOutput::printHelp(argv[0]);
        return 0;
    }

    MenuMaker menu(parser.getMenuOptions(), parser.getAlignment());
    if (parser.isSelectSymbol())
        menu.setSurroundingSymbols(parser.getSelectSymbol(true), parser.getSelectSymbol(false));
    menu.setShowBox(parser.isBox());
    menu.setMenuColor(parser.getMenuColor());
    menu.setSelectionColor(parser.getSelectedColor());

    int ret = menu.askUser(1);
    if (!parser.isQuiet())
        cout << ret << endl;
    return ret + 1;
}