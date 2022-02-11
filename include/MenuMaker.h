#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ncurses.h>
using namespace std;
enum ALIGNMENT
{
    LEFT,
    CENTER,
    RIGHT
};

class MenuMaker
{
private:
    vector<string> menuItems;
    int selected = -1;
    void surroundItemWith(int itemIndex, char front, char back);
    int itemDisplayWidth = 0;

public:
    MenuMaker(char const *items[], int itemCount, ALIGNMENT align, bool skipFirstItem = true);
    ~MenuMaker();
    static string addSpaces(string source, int desiredLength, ALIGNMENT align);
    static int strDisplayLen(const char *p);
    void showMenu();
    void showSelection(int index);
    int askUser(int startSelection);
};

MenuMaker::MenuMaker(char const *items[], int itemCount, ALIGNMENT align, bool skipFirstItem)
{
    int longestText = 0;
    for (int i = skipFirstItem; i < itemCount; i++)
    {
        menuItems.push_back(items[i]);
        if (menuItems.at(i - 1).length() > longestText)
            longestText = menuItems.at(i - 1).length();
    }
    for (int i = 0; i < menuItems.size(); i++)
    {
        menuItems.at(i) = addSpaces(menuItems.at(i), longestText, align);
    }
    itemDisplayWidth = longestText;
}

MenuMaker::~MenuMaker()
{
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
string MenuMaker::addSpaces(string source, int desiredLength, ALIGNMENT align)
{
    int len = strDisplayLen(source.c_str());
    int spaces = desiredLength - len;
    int margin;
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

void MenuMaker::showMenu()
{
    for (unsigned int i = 0; i < menuItems.size(); i++)
    {
        mvprintw(1 + i, 0, "%s", menuItems.at(i).c_str());
    }
}

/**
 * @brief Reports the display length of a utf-8 encoded string
 * * @return int
 *
 */
int MenuMaker::strDisplayLen(const char *s)
{
    int len = 0;
    while (*s)
        len += (*s++ & 0xc0) != 0x80;
    return len;
}

void MenuMaker::surroundItemWith(int itemIndex, char front, char back)
{
    mvprintw(1 + itemIndex, 0, "%c", front);
    mvprintw(1 + itemIndex, itemDisplayWidth, "%c", back);
}
void MenuMaker::showSelection(int index)
{
    static int lastIndex = -1;
    if (lastIndex > -1)
    {
        surroundItemWith(lastIndex, ' ', ' ');
    }
    lastIndex = index;
    surroundItemWith(index, '>', '<');
}
int MenuMaker::askUser(int startSelection)
{
    // WINDOW *menu_win;
    initscr();
    // raw();
    clear();
    noecho();
    cbreak();
    // menu_win = newwin((menuItems.size() > 30 ? menuItems.size() + 2 : 32), itemDisplayWidth + 4, 0, 0);
    keypad(stdscr, true);
    mvprintw(0, 0, "Use arrow keys to select");
    refresh();
    showMenu();
    showSelection(0);
    refresh();
    // refresh();
    int maxPos = this->menuItems.size() - 1;
    int pos = 0;

    int selected = -1;
    int ch = ' ';
    while (ch != 'q' && ch != 27 && selected == -1 )
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
    // while ((ch = getch()) != 27 && ch != 10 ) /* 27 = Esc key 10 = Return key */
    // {
    //     if (getch() == '\033')
    //     { // if the first value is esc
    //         ch = getch();
    //         printf("second %c:%d\n", ch, ch);
    //         getch();getch();getch();
    //         if (ch == '[')
    //         {
    //             switch (getch())
    //             {         // the real value
    //             case 'A': // arrow up
    //                 pos = pos > 1 ? pos - 1 : 0;
    //                 break;
    //             case 'B': // arrow down
    //                 pos = pos < maxPos ? pos + 1 : maxPos;
    //                 printf("b %c:%d\n", ch, ch);
    //                 break;
    //             case 'C': // arrow right
    //                 pos = maxPos;
    //                 break;
    //             case 'D': // arrow left
    //                 pos = 0;
    //                 break;
    //             }
    //         }
    //         showSelection(pos);
    //     }
    // }

    clrtoeol();
    move(0,0);
    refresh();
    endwin();
    return selected;
}

#endif