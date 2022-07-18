#ifndef CURSORHANDLE_H
#define CURSORHANDLE_H
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "PropertiesTypes.h"
#include "UserInterface.h"

class UserInterface;

class CursorHandle
{
    public:
        CursorHandle(int width, int height);
        CursorHandle(UserInterface *ui);
        ~CursorHandle();
        void setRange(Range* range, int min, int max);
        std::string getParametersMsg();
        bool positionIsPossible();
        bool positionIsOnBorder();
        bool moveIsPossible();
        bool positionIsMoved();
        void move(int x, int y);
        void setCursorPosition(int x, int y);
        void setCursorPositionMsg(int x, int y);
        position getCursorPosition();
    protected:
        UserInterface *ui;
        Range positionX;
        Range positionY;
    private:
        position *cursorPosition;
        position *cursorPositionPrevious;
        
        
};
#endif
