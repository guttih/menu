#include "include/ArgumentParser.h"

ArgumentParser::ArgumentParser(char const *items[], int itemCount)
{

    for (int i = 1; i < itemCount; i++)
    {
        _arguments.push_back(items[i]);
    }
    parseArguments();
}
bool ArgumentParser::getColorOptionColor(COLOR_OPTIONS cOption, string color)
{
    short colorNum;
    if (color == "black")
    {
        colorNum = COLOR_BLACK;
    }
    else if (color == "red")
    {
        colorNum = COLOR_RED;
    }
    else if (color == "green")
    {
        colorNum = COLOR_GREEN;
    }
    else if (color == "yellow")
    {
        colorNum = COLOR_YELLOW;
    }
    else if (color == "blue")
    {
        colorNum = COLOR_BLUE;
    }
    else if (color == "magenta")
    {
        colorNum = COLOR_MAGENTA;
    }
    else if (color == "cyan")
    {
        colorNum = COLOR_CYAN;
    }
    else if (color == "white")
    {
        colorNum = COLOR_WHITE;
    }
    else
    {
        return false;
    }

    switch (cOption)
    {
    case COLOR_OPTIONS::FG:
        _colorMenu.foreground = colorNum;
        break;
    case COLOR_OPTIONS::BG:
        _colorMenu.background = colorNum;
        break;
    case COLOR_OPTIONS::FG_SEL:
        _colorSelected.foreground = colorNum;
        break;
    case COLOR_OPTIONS::BG_SEL:
        _colorSelected.background = colorNum;
        break;

    default:
        return false;
    }

    return true;
}

/**
 * @brief Checks if a string is a alignment keyword and returns it's value.
 *
 * @param option The keyword to check
 * @param check Should we check for horizontal keywords or vertical
 * @return int On success, the enum number of the keyword.  On error -1.
 */
int ArgumentParser::getAlignKeywordValue(string option, ALIGNMENT_CHECK check)
{

    if (check == HORIZONTAL_KEYWORD)
    {
        if (option == "left")
            return HORIZONTAL_ALIGNMENT::LEFT;
        if (option == "center")
            return HORIZONTAL_ALIGNMENT::CENTER;
        if (option == "right")
            return HORIZONTAL_ALIGNMENT::RIGHT;
    }
    if (check == VERTICAL_KEYWORD)
    {
        if (option == "top")
            return VERTICAL_ALIGNMENT::TOP;
        if (option == "middle")
            return VERTICAL_ALIGNMENT::MIDDLE;
        if (option == "bottom")
            return VERTICAL_ALIGNMENT::BOTTOM;
    }

    return ERROR_VALUE;
}

/**
 * @brief Converts a string to a number
 *
 * @param option - the string to be converted to a number.
 * @return int On success a non negative number is returned.  On fail, -1 is returned.
 */
int ArgumentParser::getNumberValue(string option)
{
    if (option.length() < 1 || option.length() > 5)
        return ERROR_VALUE;
    else if (option == "0")
        return 0;
    int i = std::atoi(option.c_str());
    if (i < 0)
        return -1;
    return i;
}
void ArgumentParser::parseArguments()
{
    bool foundMenuOption = false;
    for (vector<string>::iterator it = _arguments.begin(); it != _arguments.end(); it++)
    {
        if (foundMenuOption)
        {

            _menuItems.push_back(*it);
            _arguments.erase(it--);
        }
        else if (*it == "-lines")
        {
            _arguments.erase(it--);
            foundMenuOption = true;
        }
        else if (*it == "--help" || *it == "-help" || *it == "-h")
        {
            _optHelp = true;
            return;
        }
        else if (*it == "-title")
        {   _titles.clear();
            it++;
            if (it == _arguments.end() )
            {
                _optInvalid = true;
                _errorString = "title must be followed by a string";
                return;
            }
            _titles.push_back(*it);
            while ( (*(++it)).rfind("-") != 0 && it != _arguments.end() )
            {
                _titles.push_back(*it);
            }
            if (it != _arguments.end())
                it--; //We have an option we need to process.

        }
        else if (*it == "-descriptions")
        {   _itemDescription.clear();
            it++;
            if (it == _arguments.end() )
            {
                _optInvalid = true;
                _errorString = "descriptions must be followed by a string";
                return;
            }
            _itemDescription.push_back(*it);
            while ( (*(++it)).rfind("-") != 0 && it != _arguments.end() )
            {
                _itemDescription.push_back(*it);
            }
            if (it != _arguments.end())
                it--; //We have an option we need to process.

        }
        else if (*it == "-q" || *it == "-quiet")
        {
            _optQuiet = true;
        }
        else if (*it == "-align")
        {
            it++;
            int align;
            if (it == _arguments.end() || (align = getAlignKeywordValue(*it, HORIZONTAL_KEYWORD)) < 0)
            {
                _optInvalid = true;
                _errorString = "-align must be followed by one of these keywords left, center or right.";
                return;
            }
            _alignment = (HORIZONTAL_ALIGNMENT)align;
        } // else if (*it == "-align")
        else if (*it == "-pos")
        {
            it++;
            int align;
            if (it == _arguments.end() || (align = getAlignKeywordValue(*it, VERTICAL_KEYWORD)) < 0)
            {
                _optInvalid = true;
                _errorString = "-pos must be followed by one of these keywords top, middle or bottom.";
                return;
            }
            _optPos.vertical = (VERTICAL_ALIGNMENT)align;
            it++;
            if (it == _arguments.end() || (align = getAlignKeywordValue(*it, HORIZONTAL_KEYWORD)) < 0)
            {
                _optInvalid = true;
                _errorString = "-pos must be followed by one of these keywords left, center or right.";
                return;
            }
            _optPos.horizontal = (HORIZONTAL_ALIGNMENT)align;
        } // else if (*it == "-pos")
        else if (*it == "-margin")
        {
            it++;
            int margin;
            if (it == _arguments.end() || (margin = getNumberValue(*it)) < 0)
            {
                _optInvalid = true;
                _errorString = "-margin must be followed by a number.";
                return;
            }
            _optMargin.y = margin;
            it++;
            if (it == _arguments.end() || (margin = getNumberValue(*it)) < 0)
            {
                _optInvalid = true;
                _errorString = "-margin must be followed by two numbers.";
                return;
            }
            _optMargin.x = margin;
        } // else if (*it == "-margin")
        else if (*it == "-width")
        {
            it++;
            int width;
            if (it == _arguments.end() || (width = getNumberValue(*it)) < 0)
            {
                _optInvalid = true;
                _errorString = "-width must be followed by a number.";
                return;
            }
            _width = width;
        }
        else if (*it == "-s")
        {
            it++;
            _optSelectSymbol = true;
            if (it->length() != 1)
            {
                _optInvalid = true;
                _errorString = "-s must be followed by a character";
                return;
            }
            _selectSymbolEnd = _selectSymbolFront = it->at(0);
            it++;
            if (it->length() == 1)
            {
                _selectSymbolEnd = it->at(0);
            }
            else
            {
                // No end symbol, will be using same in front and back
                it--;
            }
        }
        else if (*it == "-sw")
        {
            _optSelectWallSymbol=true;
            _optSelectSymbol=false;
        }
        else if (*it == "-fg")
        {
            it++;
            if (!getColorOptionColor(COLOR_OPTIONS::FG, *it))
            {
                _optInvalid = true;
                _errorString = "fg must be followed by a color";
                return;
            }
        }
        else if (*it == "-bg")
        {
            it++;
            if (!getColorOptionColor(COLOR_OPTIONS::BG, *it))
            {
                _optInvalid = true;
                _errorString = "bg must be followed by a color";
                return;
            }
        }
        else if (*it == "-fg_sel")
        {
            it++;
            if (!getColorOptionColor(COLOR_OPTIONS::FG_SEL, *it))
            {
                _optInvalid = true;
                _errorString = "fg_sel must be followed by a color";
                return;
            }
        }
        else if (*it == "-bg_sel")
        {
            it++;
            if (!getColorOptionColor(COLOR_OPTIONS::BG_SEL, *it))
            {
                _optInvalid = true;
                _errorString = "bg_sel must be followed by a color";
                return;
            }
        }
        else if (*it == "-cq")
        {
            _optSelectSymbol = true;
            _selectSymbolEnd = _selectSymbolFront = ' ';
        }
        else if (*it == "-box")
        {
            _optBox = true;
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