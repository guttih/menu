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

            _menuItems.push_back(it->c_str());
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
            return;
        }
         else if (*it == "-q" || *it == "-quiet")
        {
            _optQuiet=true;
        }
        else if (*it == "--align")
        {
            it++;
            if (it == _arguments.end() || (*it != "left" && *it != "center" && *it != "right"))
            {
                _optInvalid = true;
                _errorString = "--align must be followed by one of these keywords left, center or right.";
                return;
            }
            if (*it == "right")
                _alignment = RIGHT;
            else
                _alignment = *it == "center" ? CENTER : LEFT;
        } // else if (*it == "--align")
        else if (*it == "-c")
        {
            it++;
            _optSelectSymbol=true;
            if (it->length() != 1)
            {
                _optInvalid = true;
                _errorString = "-c must be followed by a character";
                return;
            }
            _selectSymbolEnd = _selectSymbolFront = it->at(0);
            it++;
            if (it->length() == 1){
                _selectSymbolEnd=it->at(0);
            } else {
                //No end symbol, will be using same in front and back
                it--;
            }
        }
        else if (*it == "-cq")
        {
            _optSelectSymbol=true;
            _selectSymbolEnd = _selectSymbolFront=' ';
        }
        else if (*it == "-highlight")
        {
            _optSelectHighlight=true;
        }
        else if (*it == "-box")
        {
            _optBox=true;
        }
        else
        {
            _optInvalid = true;
            _errorString = *it;
            return;
        }
    }
    if (_arguments.size() == 0 && !foundMenuOption)
    {
        _optInvalid = true;
        _errorString = "No arguments provided";
    }
    else if (_menuItems.size() == 0)
    {
        _optInvalid = true;
        _errorString = "No menu option provided";
    }
}
ArgumentParser::~ArgumentParser()
{
}

vector<string> ArgumentParser::getMenuOptions()
{
    return _menuItems;
}

/**
 * @brief Get Invalid pargument
 *
 * @return const char* The invalid argument, if no invalid argument NULL is returned
 */
const char *ArgumentParser::errorString()
{
    return _optInvalid ? _errorString.c_str() : NULL;
}

/**
 * @brief Get the symbol that represents selected menu string.
 * 
 * @param frontSymbol - true if front symbol, false if end symbol
 * @return char 
 */
char ArgumentParser::getSelectSymbol(bool frontSymbol)
{
    return frontSymbol ? _selectSymbolFront : _selectSymbolEnd;
}