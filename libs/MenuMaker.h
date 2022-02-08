#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
enum ALIGNMENT {LEFT, CENTER, RIGHT};

class MenuMaker
{
private:
    vector <string> menuItems;
public:
    MenuMaker(char const *items[], int itemCount, ALIGNMENT align, bool skipFirstItem=true);
    ~MenuMaker();
    static string addSpaces(string source, int desiredLength, ALIGNMENT align);
    void showMenu(int selectedOption);
};

MenuMaker::MenuMaker(char const *items[], int itemCount, ALIGNMENT align, bool skipFirstItem)
{
    int longestText=0;
    for(int i = skipFirstItem; i<itemCount; i++ ){
        menuItems.push_back(items[i]);
        if (menuItems.at(i-1).length() > longestText)
            longestText=menuItems.at(i-1).length();
    }
    for(int i = 0; i<menuItems.size(); i++ ){
        menuItems.at(i)=addSpaces(menuItems.at(i), longestText, align);
    }
    
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
string MenuMaker::addSpaces(string source, int desiredLength, ALIGNMENT align ) {
    string ret;
    ret="";
    int len = source.length();
    int spaces = desiredLength-len;
    int margin;
    if (spaces < 0)
        return source;  //no change, not  desired length not enough
    
    if (align == LEFT)
        return source + string(spaces, ' ');
    else if (align == RIGHT) 
        return string(spaces, ' ') + source;
    else {
        //CENTER
        bool isOdd = ( spaces % 2 != 0);
        spaces/=2;
        return string(spaces, ' ') + source + string(spaces + isOdd, ' ');

    }
}

void MenuMaker::showMenu(int selectedOption ) {
    for(int i = 0; i<menuItems.size(); i++ ){
        if (i==selectedOption)
            cout << "> "<<menuItems.at(i)<<" <" <<endl;
        else
            cout << "  "<<menuItems.at(i)<<"  " <<endl;
    }
}

#endif