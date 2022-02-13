#ifndef MENUMAKER_H
#define MENUMAKER_H

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
    vector<string> _menuItems;
    int _selected = -1;
    int _itemDisplayWidth = 0;
    void surroundItemWith(int itemIndex, char front, char back);
    int getAlignIndex(string source, int desiredLength, ALIGNMENT align, bool oddAlignmentSpaceInFront);

public:
    ALIGNMENT _align=CENTER;
    MenuMaker(vector<string>options, ALIGNMENT align);
    ~MenuMaker();
    static string addSpaces(string source, int desiredLength, ALIGNMENT align);
    static int strDisplayLen(const char *p);
    void showMenu();
    void showSelection(int index);
    int askUser(int startSelection);
    void addItem(string, ALIGNMENT align);
    int addItems(vector<string> options, ALIGNMENT align);
};



#endif