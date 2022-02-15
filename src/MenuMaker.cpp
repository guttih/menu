#include "include/MenuMaker.h"

#define COLOR_PAIR_SEL 1
#define COLOR_PAIR_MENU 2

MenuMaker::MenuMaker(vector<string> options, ALIGNMENT align)
{
    addItems(options, align);
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
int MenuMaker::addItems(vector<string> options, ALIGNMENT align)
{
    int added = 0;
    this->_align = align;
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
int MenuMaker::getAlignIndex(string source, int desiredLength, ALIGNMENT align, bool oddAlignmentSpaceInFront)
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

void MenuMaker::showItem(unsigned int itemIndex)
{
    const char *str = _menuItems.at(itemIndex).c_str();
    int offset = getAlignIndex(str, _itemDisplayWidth, _align, true);
    if (_window)
        mvwprintw(_window, 1 + itemIndex, 2 + offset, "%s", str);
    else
        mvprintw(itemIndex, 1 + offset, "%s", str);
}
void MenuMaker::showMenu()
{
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    for (unsigned int i = 0; i < _menuItems.size(); i++)
    {
        showItem(i);
    }
}

void MenuMaker::surroundItemClear(int itemIndex)
{
    char clear = ' ';
    if (_window)
    {
        mvwprintw(_window, 1 + itemIndex, 1, "%c", clear);
        mvwprintw(_window, 1 + itemIndex, _itemDisplayWidth + 2, "%c", clear);
    }
    else
    {
        mvprintw(itemIndex, 0, "%c", clear);
        mvprintw(itemIndex, _itemDisplayWidth + 1, "%c", clear);
    }
}
void MenuMaker::surroundItemWith(int itemIndex, char front, char back)
{
    if (_window)
    {
        wattron(_window, COLOR_PAIR(COLOR_PAIR_SEL));
        showItem(itemIndex);
        wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
        mvwprintw(_window, 1 + itemIndex, 1, "%c", front);
        mvwprintw(_window, 1 + itemIndex, _itemDisplayWidth + 2, "%c", back);
    }
    else
    {
        mvprintw(itemIndex, 0, "%c", front);
        mvprintw(itemIndex, _itemDisplayWidth + 1, "%c", back);
    }
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

int MenuMaker::askUser(int startSelection)
{

    bool useStandardScreen = false;
    // https://techlister.com/linux/creating-menu-with-ncurses-in-c/
    int height = _menuItems.size() + 2,
        width = _itemDisplayWidth + 4;
    initscr();
    use_default_colors();
    start_color();
    init_pair(COLOR_PAIR_SEL, _colorSelected.foreground, _colorSelected.background);
    init_pair(COLOR_PAIR_MENU,_colorMenu.foreground, _colorMenu.background);

    _window = useStandardScreen ? stdscr : newwin(height, width, 1, 1);
    // clear();
    noecho();
    curs_set(0);
    keypad(_window, true);
    wattron(_window, COLOR_PAIR(COLOR_PAIR_MENU));
    if (_showBox)
        box(_window, 0, 0);
    wrefresh(_window);
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