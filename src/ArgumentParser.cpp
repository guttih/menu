#include "include/ArgumentParser.h"


ArgumentParser::ArgumentParser(char const *items[], int itemCount)
{
    for (int i = 1; i < itemCount; i++)
    {
        menuItems.push_back(items[i]);
    }
}

ArgumentParser::~ArgumentParser()
{
}

vector<string> ArgumentParser::getOptions(){
    return menuItems;
}

