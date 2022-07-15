#ifndef CURSORLIMITS_H
#define CURSORLIMITS_H
#include <iostream>
#include <string>
#include <sstream>
#include "PropertiesTypes.h"

class CursorLimits
{
    public:
        CursorLimits(int width, int height);
        void setRange(Range* range, int min, int max);
        void updateCursorPosition(position* cursorPosition, position* cursorPositionPrevious);
        std::string getParametersMsg();
        bool positionIsPossible();
        bool positionIsOnBorder();
        bool moveIsPossible();
        bool positionIsMoved()
    protected:
        Range positionX;
        Range positionY;
        position* cursorPosition;
        position* cursorPositionPrevious;
        
};
#endif
