#ifndef TERMINALOUTPUT_H
#define TERMINALOUTPUT_H

#include <iostream>
#include <string>
using namespace std;

#pragma once

class TerminalOutput
{
public:
    TerminalOutput();
    ~TerminalOutput();
    static void println( const char *str1, const char *str2, const char *str3 );
    static void println( const char *str1, const char *str2 );
    static void println( const char *str );
    static void println();
    static void print( string str );
    static void print( const char *str );
    static void printHelp( const char *appName );
private:
};

#endif