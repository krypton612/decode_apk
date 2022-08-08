#include <iostream>
#include <curses.h>


std::string getstring(WINDOW *inputmen)
{   
    //(altura recomendada), (tamaño a lo horizontal), (posicionamiento en y de la ventana), (posicionamiento en x de la ventana)
    // WINDOW *inputwin = newwin(3, 100, 10, 10); requiere este tipo de ventana

    int yMax, xMax, yBeg, xBeg; 
    getbegyx(inputmen, yBeg, xBeg);

    std::string input;
    box(inputmen, 0, 0);
    wrefresh(inputmen);
    move(yBeg + 1, xBeg + 1);
    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }

    // restore your cbreak / echo settings here
    wclear(inputmen);
    wrefresh(inputmen);
    return input;
}

//
// int main (int argc, char *argv[])
// {
//   initscr();
//   
//   box(stdscr, 0, 0);
//   WINDOW *inputwin = newwin(3, 100, 10, 10);
//   
//
//   wrefresh(stdscr);
//   std::string data = getstring(inputwin);
//   mvprintw(10, 10, data.c_str());
//
//   getch();
//   endwin();
//   return 0;
// }
