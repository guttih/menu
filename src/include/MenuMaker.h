#ifndef MENUMAKER_H
#define MENUMAKER_H

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ncurses.h>

#pragma once

using namespace std;

struct POINT {
    int x;
    int y;
};

enum HORIZONTAL_ALIGNMENT
{
    LEFT,
    CENTER,
    RIGHT
};
enum VERTICAL_ALIGNMENT
{
    TOP,
    MIDDLE,
    BOTTOM
};

struct SCREEN_ALIGNMENT
{
    VERTICAL_ALIGNMENT vertical;
    HORIZONTAL_ALIGNMENT horizontal;
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
    int _width=0;
    int _descriptionHeight=1;
    int _itemDisplayWidth = 0;
    char _selectionSymbolFront='>';
    char _selectionSymbolEnd  ='<';
    bool _selectWallSymbol=false;
    vector<string> _titles;
    vector<string> _descriptions;
    bool _showBox=false;
    POINT _margin={0,0};
    POINT _menuMargin={0,0};
    WINDOW *_window = NULL;
    COLORPAIR _colorSelected = { -1, -1 }; 
    COLORPAIR _colorMenu     = { -1, -1 }; 
    HORIZONTAL_ALIGNMENT _align=CENTER;
    SCREEN_ALIGNMENT _screenPosition={TOP, LEFT };
    void surroundItemClear(int itemIndex);
    void surroundItemWith(int itemIndex, char front, char back);
    void showItem(unsigned int itemIndex, bool addSpaces);
    int getAlignIndex(string source, int desiredLength, HORIZONTAL_ALIGNMENT align, bool oddAlignmentSpaceInFront);
    static string addSpaces(string source, int desiredLength, HORIZONTAL_ALIGNMENT align);
    static int strDisplayLen(const char *p);
    void rectangle(int y1, int x1, int y2, int x2);
    void showTitle();
    void paintBackground(int height, int width);
    void showDescription(int itemIndex);
    void showMenu();
    void showSelection(int index);
    POINT calculateMenuPosition(POINT maxXY, POINT menuWidthHeight);
    vector<string> adjustDescriptionWidths(vector<string> strings, int width);
    int getMenuMinimumDisplayWidth();
    
public:
    MenuMaker(vector<string>options, HORIZONTAL_ALIGNMENT align);
    ~MenuMaker();
    int askUser(int startSelection);
    void addItem(string);
    int addItems(vector<string> options, HORIZONTAL_ALIGNMENT align);
    void setTitle(vector<string>  titleStrings);
    void setDescriptions(vector<string>  itemDescriptions);
    void setSurroundingSymbols(char front, char end){  _selectionSymbolFront=front; _selectionSymbolEnd=end; }
    void setSelectWallSymbol(bool activate=true){_selectWallSymbol=activate;setSurroundingSymbols(' ', ' ');}
    void setShowBox(bool show)                      { _showBox=show; }
    void setMenuColor(COLORPAIR pair);
    void setSelectionColor(COLORPAIR pair);
    void setAlignment(HORIZONTAL_ALIGNMENT align){ _align=align;}
    void setPosition(SCREEN_ALIGNMENT screenAlignment){ _screenPosition.horizontal=screenAlignment.horizontal; _screenPosition.vertical = screenAlignment.vertical;}
    void setMargin(POINT margin){_margin.x=margin.x; _margin.y=margin.y;};
    void setWidth(int width);
};



#endif