#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#pragma once

#include "MenuMaker.h"
#include <string>
#include <vector>

using namespace std;

const int ERROR_VALUE = -1;

enum COLOR_OPTIONS
{
    FG,
    BG,
    FG_SEL,
    BG_SEL
};

enum ALIGNMENT_CHECK{
    HORIZONTAL_KEYWORD,
    VERTICAL_KEYWORD
};

class ArgumentParser
{
private:
    vector<string> _arguments;
    vector<string> _menuItems;
    vector<string> _titles;
    vector<string> _itemDescription;
    bool _optHelp = false;
    bool _optInvalid = false;
    bool _optSelectSymbol = false;
    bool _optQuiet = false;
    bool _optBox=false;
    HORIZONTAL_ALIGNMENT _alignment = LEFT;
    SCREEN_ALIGNMENT _optPos={TOP, LEFT };
    POINT _optMargin={0,0};
    string _errorString;
    char _selectSymbolFront = '*';
    char _selectSymbolEnd   = '*';
    COLORPAIR _colorMenu     = { -1, -1 }; 
    COLORPAIR _colorSelected = { -1, -1 }; 
    void parseArguments();
    bool getColorOptionColor(COLOR_OPTIONS cOption, string color);
    int getAlignKeywordValue(string option, ALIGNMENT_CHECK check);
    int getNumberValue(string option);
public:
    bool isValid() { return !_optInvalid; }
    bool isSelectSymbol() { return _optSelectSymbol; }
    char getSelectSymbol(bool frontSymbol);
    vector<string> getTitle(){return _titles; }
    vector<string> getMenuOptionsDescription(){return _itemDescription; }
    COLORPAIR getMenuColor()    { return _colorMenu;     }
    COLORPAIR getSelectedColor(){ return _colorSelected;}
    POINT getMargin(){return _optMargin;}
    bool isPrintHelp() { return _optHelp; }
    bool isQuiet() { return _optQuiet; }
    bool isBox() { return _optBox; }
    const char *errorString();
    ArgumentParser(char const *items[], int itemCount);
    HORIZONTAL_ALIGNMENT getAlignment(){return _alignment;};
    SCREEN_ALIGNMENT getPosition(){return _optPos;};
    
    vector<string> getMenuOptions();
    ~ArgumentParser();
};

#endif