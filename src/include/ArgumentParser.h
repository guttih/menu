#ifndef ARGUMENTPARSER_H
#define ARGUMENTPARSER_H

#include <string>
#include <vector>

using namespace std;

class ArgumentParser
{
private:
    vector<string> menuItems;
public:
    
    ArgumentParser(char const *items[], int itemCount);
    vector<string> getOptions();
    ~ArgumentParser();
};


#endif