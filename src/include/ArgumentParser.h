#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#pragma once

#include <string>
#include <vector>

using namespace std;

class ArgumentParser
{
private:
    vector<string> _arguments;
    vector<string> menuItems;
    bool _optHelp=false;
    bool _optInvalid=false;
    string _errorString;
    
    void parseArguments();
public:
    bool isValid() {return !_optInvalid; }
    bool isPrintHelp() {return _optHelp; }
    const char * errorString();
    ArgumentParser(char const *items[], int itemCount);
    vector<string> getOptions();
    ~ArgumentParser();
};


#endif