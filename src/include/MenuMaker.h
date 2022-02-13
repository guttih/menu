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



#endif