// build params: gcc main.cpp -o main -lncursesw -lstdc++
//sudo yum install ncurses-devel
 #include "include/MenuMaker.h"
#include <stdio.h>
#include "vector"
#include "wchar.h"
#include <iostream>
#include <string>
#include <ncurses.h>
#include <locale.h>
using namespace std;
// struct COORD
// {
//     int x = 0;
//     int y = 0;
// };

// void setCursorPos(COORD pos)
// {
//     printf("\033[%d;%dH", pos.y + 1, pos.x + 1);
// }
// void setCursorPos(int XPos, int YPos)
// {
//     COORD pos = {XPos, YPos};
//     setCursorPos(pos);
// }
// COORD orgPos;

// see also https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
// tutorial https://www.youtube.com/watch?v=2tWN6ntNo4w
// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/keys.html
int main(int argc, char const *argv[])
{   
    setlocale(LC_ALL, "");
    MenuMaker menu(argv, argc, LEFT, true);

    int ret=menu.askUser(1);
   
    cout<<"Þetta er ekki bilað: "<<ret<<endl;
 
 
    std::wstring widestr = L"Þroskahefta þrumrúnkugúrkur Þá";
    printf("2 %ls %lu\n", widestr.c_str(), widestr.length());
    wprintf(L"4 %ls \n", widestr.c_str());
    wprintf(L"4 %s \n", widestr.c_str());
    return 0;
}