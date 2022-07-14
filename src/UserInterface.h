#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <ncurses.h>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <memory>
#include "CursorLimits.h"
#include "PropertiesTypes.h"


class UserInterface
{
    public:
        UserInterface();
        void setWindowProps(int width, int height, int x, int y);
        void setCursorPosition(int x, int y);
        void printText(std::string text);
        void beep(int freq, int length);
        void bindCommands();
        void start();
        void stop();
        void move(int x, int y);
        void runCmd(std::string cmd);
        void printCursorPosition();
        void printCursorPositionShort();
        void clearScreen();
        void putChar(char c);
        void setAttr(int attr);
        void getAttr();
        bool getRunningStatus();
        position getCursorPosition();
    private:
        void init();
        void controlLoop();
    protected:
        WINDOW *win;
        std::unique_ptr<CursorLimits> cursorlimits;
        objectProps windowProps;
        position cursorPosition;
        position cursorPositionPrevious;
        std::map<std::string, std::function<void()>> commandMap;
        bool running=0;
};

#endif
