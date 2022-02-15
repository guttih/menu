#ifndef MENUMAKER_H
#define MENUMAKER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ncurses.h>

#pragma once

using namespace std;

enum ALIGNMENT
{
    LEFT,
    CENTER,
    RIGHT
};

struct COLORPAIR
{
    short foreground;
    short background;
};

class MenuMaker
{
private:
    vector<string> _menuItems;
    int _selected = -1;
    int _itemDisplayWidth = 0;
    char _selectionSymbolFront='>';
    char _selectionSymbolEnd  ='<';
    bool _showBox=false;
    WINDOW *_window = NULL;
    COLORPAIR _colorSelected = { -1, -1 }; 
    COLORPAIR _colorMenu     = { -1, -1 }; 
    void surroundItemClear(int itemIndex);
    void surroundItemWith(int itemIndex, char front, char back);
    void showItem(unsigned int itemIndex);
    int getAlignIndex(string source, int desiredLength, ALIGNMENT align, bool oddAlignmentSpaceInFront);
    static string addSpaces(string source, int desiredLength, ALIGNMENT align);
    static int strDisplayLen(const char *p);
    void showMenu();
    void showSelection(int index);

public:
    ALIGNMENT _align=CENTER;
    MenuMaker(vector<string>options, ALIGNMENT align);
    ~MenuMaker();
    int askUser(int startSelection);
    void addItem(string);
    int addItems(vector<string> options, ALIGNMENT align);
    void setSurroundingSymbols(char front, char end){  _selectionSymbolFront=front; _selectionSymbolEnd=end; }
    void setShowBox(bool show)                      { _showBox=show; }
    void setMenuColor(COLORPAIR pair);
    void setSelectionColor(COLORPAIR pair);
};



#endif