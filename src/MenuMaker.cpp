#include "include/MenuMaker.h"

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
    this->_align=align;
    for (vector<string>::iterator it = options.begin(); it != options.end(); it++)
    {
        this->addItem(*it);
        added++;
    }

    return added;
}

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

void MenuMaker::showMenu()
{
    int offset;
    const char *str;
    for (unsigned int i = 0; i < _menuItems.size(); i++)
    {
        str = _menuItems.at(i).c_str();
        offset = getAlignIndex(str, _itemDisplayWidth, _align, true);
        mvprintw(i, 1 + offset, "%s", str);
    }
}

void MenuMaker::surroundItemWith(int itemIndex, char front, char back)
{
    mvprintw(itemIndex, 0, "%c", front);
    mvprintw(itemIndex, _itemDisplayWidth + 1, "%c", back);
}
void MenuMaker::showSelection(int index)
{
    static int lastIndex = -1;
    if (lastIndex > -1)
    {
        surroundItemWith(lastIndex, ' ', ' ');
    }
    lastIndex = index;
    surroundItemWith(index, _selectionSymbolFront, _selectionSymbolEnd);
}
int MenuMaker::askUser(int startSelection)
{
    // WINDOW *menu_win;
    initscr();
    clear();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    refresh();
    showMenu();
    showSelection(0);
    refresh();
    int maxPos = this->_menuItems.size() - 1;
    int pos = 0;

    int selected = -1;
    int ch = ' ';
    while (ch != 'q' && ch != 27 && selected == -1)
    {
        ch = getch();
        switch (ch)
        {
        case KEY_UP:
            pos = pos > 1 ? pos - 1 : 0;
            showSelection(pos);
            refresh();
            break;
        case KEY_DOWN:
            pos = pos < maxPos ? pos + 1 : maxPos;
            showSelection(pos);
            refresh();
            break;
        case KEY_LEFT:
            pos = 0;
            showSelection(pos);
            refresh();
            break;
        case KEY_RIGHT:
            pos = maxPos;
            showSelection(pos);
            refresh();
            break;
        case 10:
            printw("end line");
            refresh();
            selected = pos;
            break;
        }
    }

    clrtoeol();
    move(0, 0);
    refresh();
    endwin();
    return selected;
}