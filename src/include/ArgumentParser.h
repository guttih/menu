#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#pragma once

#include "MenuMaker.h"
#include <string>
#include <vector>

using namespace std;


enum COLOR_OPTIONS
{
    FG,
    BG,
    FG_SEL,
    BG_SEL
};


class ArgumentParser
{
private:
    vector<string> _arguments;
    vector<string> _menuItems;
    bool _optHelp = false;
    bool _optInvalid = false;
    bool _optSelectSymbol = false;
    bool _optQuiet = false;
    bool _optBox=false;
    ALIGNMENT _alignment = LEFT;
    string _errorString;
    char _selectSymbolFront = '*';
    char _selectSymbolEnd   = '*';
    COLORPAIR _colorMenu     = { -1, -1 }; 
    COLORPAIR _colorSelected = { -1, -1 }; 
    bool getColorOptionColor(COLOR_OPTIONS cOption, string color);
    void parseArguments();

public:
    bool isValid() { return !_optInvalid; }
    bool isSelectSymbol() { return _optSelectSymbol; }
    char getSelectSymbol(bool frontSymbol);
    COLORPAIR getMenuColor()    { return _colorMenu;     }
    COLORPAIR getSelectedColor(){ return _colorSelected;}
    bool isPrintHelp() { return _optHelp; }
    bool isQuiet() { return _optQuiet; }
    bool isBox() { return _optBox; }
    const char *errorString();
    ArgumentParser(char const *items[], int itemCount);
    ALIGNMENT getAlignment(){return _alignment;};
    vector<string> getMenuOptions();
    ~ArgumentParser();
};

#endif