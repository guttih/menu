// build params: gcc main.cpp -o main -lstdc++

#include "libs/MenuMaker.h"
#include <stdio.h>
#include "vector"
using namespace std;
struct COORD
{
    int x = 0;
    int y = 0;
};

void setCursorPos(COORD pos)
{
    printf("\033[%d;%dH", pos.y + 1, pos.x + 1);
}
void setCursorPos(int XPos, int YPos)
{
    COORD pos = {XPos, YPos};
    setCursorPos(pos);
}
COORD orgPos;

// see also https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
int main(int argc, char const *argv[])
{   
    MenuMaker menu(argv, argc, CENTER, true);
    printf("Parameters\n");
    for(int i = 1; i< argc; i++){
        cout<<"\""<<argv[i]<<"\""<<endl;
    }
    printf("menu\n");

    menu.showMenu(1);

    return 0;
}