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
        return 0;
    }
    else if (parser.isPrintHelp())
    {
        TerminalOutput::printHelp(argv[0]);
        return 0;
    }

    MenuMaker menu(parser.getMenuOptions(), parser.getAlignment());
    if (parser.isSelectSymbol())
        menu.setSurroundingSymbols(parser.getSelectSymbol(true), parser.getSelectSymbol(false));
    if (parser.isSelectWallSymbol())
    {
        menu.setSelectWallSymbol();
    }
    menu.setShowBox(parser.isBox());
    menu.setMenuColor(parser.getMenuColor());
    menu.setSelectionColor(parser.getSelectedColor());
    menu.setAlignment(parser.getAlignment());
    menu.setPosition(parser.getPosition());
    menu.setMargin(parser.getMargin());
    menu.setTitle(parser.getTitle());
    menu.setDescriptions(parser.getMenuOptionsDescription());
    if (parser.getDescriptionTitle().length() > 0)
    {
        menu.setDescriptionTitle(parser.getDescriptionTitle());
        menu.setDescriptionTitleOffsetX(parser.getDescriptionTitleOffsetX());
    }
    menu.setWidth(parser.getWidth());

    int selectedItem = menu.askUser(1);
    if (!parser.isQuiet() && selectedItem > -1)
        cout << menu.getItem(selectedItem) << endl;
    return selectedItem + 1;
}