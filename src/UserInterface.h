#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#ifdef _PDCURSES_
#include <pdcurses.h>
#else
#include <ncurses.h>
#endif
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <memory>
#include "CursorHandle.h"
#include "PropertiesTypes.h"

#if defined(_PDCURSES_) && defined(_WIN32)
#define CURSORPARAMS (A_BOLD | A_REVERSE)
#elif defined(_PDCURSES_) && defined(_SDL_) // to check
#define CURSORPARAMS A_BOLD
#else 
#define CURSORPARAMS A_BOLD 
#endif

class CursorHandle;

class UserInterface
{
    public:
        UserInterface();
        void setWindowProps(int width, int height, int x, int y);
        void printText(std::string text); 
        void beep(int freq, int length);
        void bindCommands();
        void start();
        void stop();
        void runCmd(std::string cmd);
        void refreshCursor();
        void printCursorPosition();
        void printCursorPositionShort();
        void clearScreen();
        void putChar(char c);
        void setAttr(int attr);
        char getAttr();
        void moveCursor(int x, int y);
        bool getRunningStatus();
        objectProps getWindowProperties();
        
    private:
        void init();
        void controlLoop();
    protected:
        WINDOW *win;
        CursorHandle *cursorhandle;
        objectProps windowProps;
        std::map<std::string, std::function<void()>> commandMap;
        bool running=0;
};

#endif
