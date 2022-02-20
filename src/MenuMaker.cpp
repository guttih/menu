#include "include/MenuMaker.h"

#define COLOR_PAIR_SEL 1
#define COLOR_PAIR_MENU 2

MenuMaker::MenuMaker(vector<string> options, HORIZONTAL_ALIGNMENT align)
{
    addItems(options, align);
}

string ReplaceAll(string str, const string &from, const string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}
vector<string> MenuMaker::adjustDescriptionWidths(vector<string> strings, int width)
{
    if (width == _width)
        return strings;

    vector<string> ret;
    int descriptionHeight = 1;
    size_t found;
    string whitespaces("\f\v\n\r"),
        longString = "",
        temp,
        newString;
    for (vector<string>::iterator it = strings.begin(); it != strings.end(); it++)
    {
        longString = *it;
        // replace all white spaces with space
        while ((found = longString.find_first_of(whitespaces)) != string::npos)
        {
            temp = "" + longString.at(found);
            longString = ReplaceAll(longString, temp, " ");
        }
        // remove all double spaces
        while (longString.find("  ") != string::npos)
            longString = ReplaceAll(longString, "  ", " ");

        // split to long lines into many lines if needed
        bool goOn = (strDisplayLen(longString.c_str()) > width);
        newString = "";
        int endLines = 0;
        while (goOn)
        {
            temp = longString.substr(0, width);
            found = temp.find_last_of(" ");
            string str = longString.substr(0, found);
            newString += str;
            longString = longString.substr(found + 1);
            goOn = (strDisplayLen(longString.c_str()) > width);
            endLines++;
            newString += '\n';
        }
        newString += longString;
        ret.push_back(newString);
        if (endLines + 1 > descriptionHeight)
            descriptionHeight = endLines + 1;
    }

    _descriptionHeight = descriptionHeight;

    return ret;
}

int MenuMaker::getMenuMinimumDisplayWidth(){
    int temp,minWidth = 0;
    for(vector<string>::iterator it=_titles.begin(); it!= _titles.end(); it++) {
        temp = strDisplayLen((*it).c_str());
        if (temp > minWidth)
            minWidth = temp;
    }
    for(vector<string>::iterator it=_menuItems.begin(); it!= _menuItems.end(); it++) {
        temp = strDisplayLen((*it).c_str());
        if (temp > minWidth)
            minWidth = temp;
    }
    return minWidth;
}
void MenuMaker::setWidth(int width)
{
    if (width != _width)
    {
        int minWidthAllowed=getMenuMinimumDisplayWidth();
        if (width < minWidthAllowed)
            width = minWidthAllowed;
        _descriptions = adjustDescriptionWidths(_descriptions, width);
        _itemDisplayWidth=width;
        _width = width+2;
    }
}
void MenuMaker::setTitle(vector<string> titleStrings)
{
    // TODO: allow perferred with on the menu,  If this allowed we need to allow linebreaks in the title which will increase the menu height.
    _titles = titleStrings;
    int displayLen;
    for (vector<string>::iterator it = _titles.begin(); it != _titles.end(); it++)
    {
        displayLen = strDisplayLen((*it).c_str());
        if (displayLen > _itemDisplayWidth)
            _itemDisplayWidth = displayLen;
    }
}

void MenuMaker::setDescriptions(vector<string> descriptions)
{
    // TODO: allow perferred with on the menu,  If this allowed we need to allow linebreaks in the description which will increase the menu height.
    _descriptions = descriptions;
    int displayLen;
    for (vector<string>::iterator it = _descriptions.begin(); it != _descriptions.end(); it++)
    {
        displayLen = strDisplayLen((*it).c_str());
        if (displayLen > _itemDisplayWidth)
            _itemDisplayWidth = displayLen;
    }
}

void MenuMaker::addItem(string item)
{
    int displayLen = strDisplayLen(item.c_str());
    if (displayLen > _itemDisplayWidth)
        _itemDisplayWidth = displayLen;

    _menuItems.push_back(item.c_str());
}

/**
 * @brief Adds menu options to the menu
 *
 * @param options collection of strings to add to the menu
 * @return int The number of items added
 */
int MenuMaker::addItems(vector<string> options, HORIZONTAL_ALIGNMENT align)
{
    int added = 0;
    for (vector<string>::iterator it = options.begin(); it != options.end(); it++)
    {
        this->addItem(*it);
        added++;
    }

    return added;
}

void MenuMaker::setMenuColor(COLORPAIR pair)
{
    _colorMenu.foreground = pair.foreground;
    _colorMenu.background = pair.background;
};
void MenuMaker::setSelectionColor(COLORPAIR pair)
{
    _colorSelected.foreground = pair.foreground;
    _colorSelected.background = pair.background;
};

MenuMaker::~MenuMaker()
{
}

void MenuMaker::rectangle(int y1, int x1, int y2, int x2)
{
    mvwhline(_window, y1, x1, 0, x2 - x1);
    mvwhline(_window, y2, x1, 0, x2 - x1);
    mvwvline(_window, y1, x1, 0, y2 - y1);
    mvwvline(_window, y1, x2, 0, y2 - y1);
    mvwaddch(_window, y1, x1, ACS_ULCORNER);
    mvwaddch(_window, y2, x1, ACS_LLCORNER);
    mvwaddch(_window, y1, x2, ACS_URCORNER);
    mvwaddch(_window, y2, x2, ACS_LRCORNER);
}

/**
 * @brief Calculates the offset of a text to be aligned.
 *
 * @param source                   - Text to be aligned.
 * @param desiredLength            - What is widest string this alignment should refer to.
 * @param align                    - Align to the LEFT, CENTER or RIGHT.
 * @param oddAlignmentSpaceInFront - When text is to be centered and there is one extra
 *                                   space, do you want it in front or back of the text?
 * @return int an integer representing the offset, where this string should be printed with.
 */
int MenuMaker::getAlignIndex(string source, int desiredLength, HORIZONTAL_ALIGNMENT align, bool oddAlignmentSpaceInFront)
{
    int len = strDisplayLen(source.c_str());
    int spaces = desiredLength - len;
    if (spaces < 0 || align == LEFT)
        return _margin.x;

    if (align == RIGHT)
        return spaces+_margin.x;
    else
    {
        // CENTER
        bool isOdd = (spaces % 2 != 0);
        spaces /= 2;
        return _margin.x+spaces + (isOdd & oddAlignmentSpaceInFront);
    }
}
/**
 * @brief Reports the display length of a utf-8 encoded string
 * * @return int
 *
 */
int MenuMaker::strDisplayLen(const char *s)
{
    // return 30;
    int len = 0;
    while (*s)
        len += (*s++ & 0xc0) != 0x80;
    return len;
}

void MenuMaker::showItem(unsigned int itemIndex, bool addSpacesAroundItem)
{
    int offset;
    string temp;
    if (addSpacesAroundItem)
    {
        temp = addSpaces(_menuItems.at(itemIndex), _itemDisplayWidth + (_margin.x *2), _align);
        offset = _margin.x;
    }
    else
    {
        temp = _menuItems.at(itemIndex);
        offset = getAlignIndex(temp.c_str(), _itemDisplayWidth, _align, false);
        offset+=0;//_margin.x;
    }

    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, 2 + offset, "%s", temp.c_str());
    wrefresh(_window);
}
void MenuMaker::showMenu()
{
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    for (unsigned int i = 0; i < _menuItems.size(); i++)
    {
        surroundItemClear(i);
        showItem(i, false);
        
    }
}

int countOccurrences(string s, char c)
{
    int count = 0;

    for (size_t i = 0; i < s.size(); i++)
        if (s[i] == c)
            count++;

    return count;
}
void MenuMaker::showDescription(int itemIndex)
{
    if (_descriptions.size() < 1)
        return;

    string temp, str = (itemIndex < (int)_descriptions.size())
                           ? _descriptions.at(itemIndex)
                           : "";

    POINT location;
    int width, height;
    size_t found;
    getmaxyx(_window, height, width);
    for (int i = 0; i < _descriptionHeight; i++)
    {
        found = str.find('\n');
        if (found != string::npos)
        {
            temp = str.substr(0, found);
            str = str.substr(found + 1);
        }
        else
        {
            temp = str;
            str = "";
        }
        location.y = height - _margin.y - 1 - (_descriptionHeight - i);
        location.x = _margin.x+1;
        mvwprintw(_window, location.y, location.x, "%s", addSpaces(temp, _itemDisplayWidth + 2, LEFT).c_str());
        wrefresh(_window);
    }
    if (_showBox)
    {
        int y = height - 2 - _descriptionHeight - _margin.y,
            x1 = _menuMargin.x,
            x2 = width - 2;
        mvwhline_set(_window, y, x1 + 1, WACS_HLINE, x2);
        wrefresh(_window);
        mvwadd_wch(_window, y, 0, WACS_LTEE);
        wrefresh(_window);
        mvwadd_wch(_window, y, 1 + x2, WACS_RTEE);
        wrefresh(_window);
    }
}
void MenuMaker::paintBackground(int height, int width) {
    for(int i = 0; i<height; i++)
    {
        mvwprintw(_window, i,0, "%s", addSpaces("", width,LEFT).c_str());
        wrefresh(_window);
    }
}
void MenuMaker::showTitle()
{
    if (_titles.size() > 0)
    {
        for (size_t i = 0; i < _titles.size(); i++)
        {
            mvwprintw(_window, 1 + i + _margin.y, 1 + _margin.x, "%s", addSpaces(_titles.at(i), _itemDisplayWidth + 2, LEFT).c_str());
        }
        if (_showBox)
        {
            // Adding title line seperator
            int width = getmaxx(_window);
            int y = 1 + _titles.size()+_margin.y,
                x1 = 0,
                x2 = width - 2;
            // mvwhline(_window, y, x1 + 1, 0, x2);
            // mvwaddch(_window, y, 1 + x2, ACS_RTEE);
            // whline(_window, WACS_HLINE, x2);
            mvwhline_set(_window, y, x1 + 1, WACS_HLINE, x2);
            mvwadd_wch(_window, y, 0, WACS_LTEE);
            mvwadd_wch(_window, y, 1 + x2, WACS_RTEE);
        }
    }
}

/**
 * @brief Changes the length of a string to disiredLength,
 *        by adding spaces in front of or/and at end of string.
 *
 * @param source The string to be changed
 * @param desiredLength How long should the string be after conversion
 * @param align should spaces be added in front of-, at end of- or both.
 * @return string (the changed string or if desiredLength is not enough the source string)
 */
string MenuMaker::addSpaces(string source, int desiredLength, HORIZONTAL_ALIGNMENT align)
{
    int len = strDisplayLen(source.c_str());
    int spaces = desiredLength - len;
    if (spaces < 0)
        return source; // no change, not  desired length not enough

    if (align == LEFT)
        return source + string(spaces, ' ');
    else if (align == RIGHT)
        return string(spaces, ' ') + source;
    else
    {
        // CENTER
        bool isOdd = (spaces % 2 != 0);
        spaces /= 2;
        return string(spaces, ' ') + source + string(spaces + isOdd, ' ');
    }
}

void MenuMaker::surroundItemClear(int itemIndex)
{
    char clear = ' ';
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    showItem(itemIndex, false);
    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, 1 + _margin.x, "%c", clear);
    wrefresh(_window);
    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, _itemDisplayWidth + 2 + _margin.x, "%c", clear);
    wrefresh(_window);
}
void MenuMaker::surroundItemWith(int itemIndex, char front, char back)
{
    wattron(_window, COLOR_PAIR(COLOR_PAIR_SEL));
    //showItem(itemIndex, false);
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, 1 + _margin.x, "%c", front);
    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, _itemDisplayWidth + 2 + _margin.x, "%c", back);
}
void MenuMaker::showSelection(int index)
{
    static int lastIndex = -1;

    if (lastIndex > -1)
    {
        surroundItemClear(lastIndex);
    }
    lastIndex = index;
    surroundItemWith(index, _selectionSymbolFront, _selectionSymbolEnd);
    wattron(_window, COLOR_PAIR(COLOR_PAIR_SEL));
    showItem(index, false);
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    showDescription(index);
}

POINT MenuMaker::calculateMenuPosition(POINT max, POINT menu)
{
    POINT ret;
    switch (_screenPosition.vertical)
    {
    case MIDDLE:
        ret.y = (max.y - menu.y) / 2;
        break;
    case BOTTOM:
        ret.y = (max.y - menu.y) - 1;
        break;

    default: // TOP
        ret.y = 1;
        break;
    }

    switch (_screenPosition.horizontal)
    {
    case CENTER:
        ret.x = (max.x - menu.x) / 2;
        break;
    case RIGHT:
        ret.x = (max.x - menu.x) - 1;
        break;

    default: // LEFT
        ret.x = 1;
        break;
    }
    return ret;
}

int MenuMaker::askUser(int startSelection)
{
    int yMax, xMax, menuWidth;
    // https://techlister.com/linux/creating-menu-with-ncurses-in-c/
    menuWidth = _itemDisplayWidth + 4;
    int height = (_menuItems.size() + 2) + (_margin.y * 2),
        width = (menuWidth) + (_margin.x * 2);
    if (_titles.size() > 0)
    {
        _menuMargin.y += _titles.size() + _showBox;
        height += _titles.size() + _showBox;
        // size_t longest = 0;
        // for (vector<string>::iterator it = _titles.begin(); it != _titles.end(); it++)
        // {
        //     if ((*it).length() > longest)
        //         longest = (*it).length();
        // }
        // if (menuWidth < (int)longest)
        //     width += longest - menuWidth;
    }
    if (_descriptions.size() > 0)
    {
        height += _descriptionHeight + _showBox;
    }
    initscr();

    getmaxyx(stdscr, yMax, xMax);
    POINT screenPos = calculateMenuPosition({xMax, yMax}, {width, height});
    use_default_colors();
    start_color();
    init_pair(COLOR_PAIR_SEL, _colorSelected.foreground, _colorSelected.background);
    init_pair(COLOR_PAIR_MENU, _colorMenu.foreground, _colorMenu.background);

    _window = newwin(height, width, screenPos.y, screenPos.x);
    noecho();
    curs_set(0);
    keypad(_window, true);
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    paintBackground(height, width);
    if (_showBox)
        rectangle(0, 0, height - 1, width - 1);
    wrefresh(_window);
    showTitle();
    showMenu();
    showSelection(0);
    // wattron( _window, A_STANDOUT ); /*highlights the first item.*/ wattroff( _window, A_STANDOUT );
    wrefresh(_window);
    int maxPos = this->_menuItems.size() - 1;
    int pos = 0;

    int selected = -1;
    int ch = ' ';
    while (ch != 'q' && ch != 'Q' && ch != 27 && selected == -1)
    {
        ch = wgetch(_window);
        switch (ch)
        {
        case KEY_UP:
            pos = pos > 1 ? pos - 1 : 0;
            showSelection(pos);
            wrefresh(_window);
            break;
        case KEY_DOWN:
            pos = pos < maxPos ? pos + 1 : maxPos;
            showSelection(pos);
            wrefresh(_window);
            break;
        case KEY_LEFT:
            pos = 0;
            showSelection(pos);
            wrefresh(_window);
            break;
        case KEY_RIGHT:
            pos = maxPos;
            showSelection(pos);
            wrefresh(_window);
            break;
        case 10:
            printw("end line");
            wrefresh(_window);
            selected = pos;
            break;
        }
    }

    // clrtoeol();
    delwin(_window);
    endwin();
    _window = NULL;
    return selected;
}