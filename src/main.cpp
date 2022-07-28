#include <iostream>
#include "UserInterface.h"

void printOption(std::string opt, bool b);
std::string enableText(bool b);

int main() 
{
    // test
#ifdef _TEST_
#  ifdef _PDCURSES_
      printOption("PDCurses", true);
#  endif // PD_CURSES
#  ifdef _SDL_
      printOption("SDL", true);
#  endif // SDL
printf("Print any key to continue: ");
std::cin.get();
#endif // test
    UserInterface interface;
    return 0;
}


void printOption(std::string opt, bool b)
{
    std::cout << "==> " << opt << ":" << enableText(b) << std::endl;
}

std::string enableText(bool b)
{
    return b ? " enabled " : " disabled ";
}
