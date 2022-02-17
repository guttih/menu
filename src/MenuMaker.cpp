#include "include/MenuMaker.h"

#define COLOR_PAIR_SEL 1
#define COLOR_PAIR_MENU 2

MenuMaker::MenuMaker(vector<string> options, HORIZONTAL_ALIGNMENT align)
{
    addItems(options, align);
}
void MenuMaker::setTitle(vector<string> titleStrings)
{
    _titles = titleStrings;
    int displayLen;
    for (vector<string>::iterator it = _titles.begin(); it != _titles.end(); it++)
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
        return 0;

    if (align == RIGHT)
        return spaces;
    else
    {
        // CENTER
        bool isOdd = (spaces % 2 != 0);
        spaces /= 2;
        return spaces + (isOdd & oddAlignmentSpaceInFront);
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
        temp = addSpaces(_menuItems.at(itemIndex), _itemDisplayWidth + (_margin.x * 2), _align);
        offset = 0;
    }
    else
    {
        temp = _menuItems.at(itemIndex);
        offset = getAlignIndex(temp.c_str(), _itemDisplayWidth + (_margin.x * 2), _align, false);
    }

    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, 2 + offset, "%s", temp.c_str());
}
void MenuMaker::showMenu()
{
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    for (unsigned int i = 0; i < _menuItems.size(); i++)
    {
        surroundItemClear(i);
        showItem(i, true);
    }
}

void MenuMaker::showTitle()
{
    if (_titles.size() > 0)
    {
        for (size_t i = 0; i < _titles.size(); i++)
        {
            mvwprintw(_window, 1 + i + _margin.y, 1 + _margin.x, "%s", addSpaces(_titles.at(i), _itemDisplayWidth+2, LEFT).c_str());
        }
        if (_showBox)
        {
            //Adding title line seperator 
            int width = getmaxx(_window);
            int y = 1 + _titles.size() + _margin.y,
                x1 = _margin.x,
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
    showItem(itemIndex, true);
    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, 1 + _margin.x, "%c", clear);
    mvwprintw(_window, 1 + itemIndex + _menuMargin.y + _margin.y, _itemDisplayWidth + 2 + _margin.x, "%c", clear);
}
void MenuMaker::surroundItemWith(int itemIndex, char front, char back)
{
    wattron(_window, COLOR_PAIR(COLOR_PAIR_SEL));
    showItem(itemIndex, false);
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
        size_t longest = 0;
        for (vector<string>::iterator it = _titles.begin(); it != _titles.end(); it++)
        {
            if ((*it).length() > longest)
                longest = (*it).length();
        }
        if (menuWidth < (int)longest)
            width += longest - menuWidth;
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
    if (_showBox)
        rectangle(0, 0, height - 1, width - 1);
    // box(_window, 0, 0);
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