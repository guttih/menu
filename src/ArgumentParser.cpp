#include "include/ArgumentParser.h"

ArgumentParser::ArgumentParser(char const *items[], int itemCount)
{

    for (int i = 1; i < itemCount; i++)
    {
        _arguments.push_back(items[i]);
    }
    parseArguments();
}

void ArgumentParser::parseArguments()
{
    bool foundMenuOption = false;
    for (vector<string>::iterator it = _arguments.begin(); it != _arguments.end(); it++)
    {
        if (foundMenuOption)
        {
            menuItems.push_back(it->c_str());
            _arguments.erase(it--);
        }
        else if (*it == "-menu")
        {
            _arguments.erase(it--);
            foundMenuOption = true;
        }
        else if (*it == "--help" || *it == "-help" || *it == "-h")
        {
            _optHelp = true;
        }
        else
        {
            _optInvalid = true;
            _errorString=*it;
        }
    }
    if (_arguments.size() == 0 && !foundMenuOption) {
        _optInvalid = true;
        _errorString="No arguments provided";
    } else if (menuItems.size() == 0 ) {
        _optInvalid = true;
        _errorString="No menu option provided";
    }
}
ArgumentParser::~ArgumentParser()
{
}

vector<string> ArgumentParser::getOptions()
{
    return menuItems;
}

/**
 * @brief Get Invalid pargument
 * 
 * @return const char* The invalid argument, if no invalid argument NULL is returned
 */
const char * ArgumentParser::errorString()
{
    return _optInvalid ? _errorString.c_str() : NULL;
}
