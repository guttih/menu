#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#pragma once

#include "MenuMaker.h"
#include <string>
#include <vector>

using namespace std;

class ArgumentParser
{
private:
    vector<string> _arguments;
    vector<string> _menuItems;
    bool _optHelp = false;
    bool _optInvalid = false;
    bool _optSelectSymbol = false;
    bool _optQuiet = false;
    ALIGNMENT _alignment = LEFT;
    string _errorString;
    char _selectSymbolFront = '*';
    char _selectSymbolEnd   = '*';

    void parseArguments();

public:
    bool isValid() { return !_optInvalid; }
    bool isSelectSymbol() { return _optSelectSymbol; }
    char getSelectSymbol(bool frontSymbol);
    bool isPrintHelp() { return _optHelp; }
    bool isQuiet() { return _optQuiet; }
    const char *errorString();
    ArgumentParser(char const *items[], int itemCount);
    ALIGNMENT getAlignment(){return _alignment;};
    vector<string> getMenuOptions();
    ~ArgumentParser();
};

#endif