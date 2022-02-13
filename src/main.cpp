// build params: gcc main.cpp -o main -lncursesw -lstdc++
//sudo yum install ncurses-devel
 #include "include/MenuMaker.h"
  #include "include/ArgumentParser.h"

// see also https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
// tutorial https://www.youtube.com/watch?v=2tWN6ntNo4w
// https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/keys.html
int main(int argc, char const *argv[])
{   
    setlocale(LC_ALL, "");
    ArgumentParser parser(argv, argc);
    MenuMaker menu(parser.getOptions(), RIGHT);

    int ret=menu.askUser(1);
   
    //cout<<"Selected option: "<<ret<<endl;
    return ret+1;
}