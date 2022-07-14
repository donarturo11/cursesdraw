#include "CursorLimits.h"

CursorLimits::CursorLimits(int width, int height)
{
    setRange(&positionX, 0, width-1);
    setRange(&positionY, 0, height-1);
}

void CursorLimits::setRange(Range* range, int min, int max)
{
    if (max<min)
        std::swap(min, max);
    range->min=min;
    range->max=max;
}

void CursorLimits::updateCursorPosition(position* cursorPosition, position* cursorPositionPrevious)
{
    this->cursorPosition=cursorPosition;
    this->cursorPositionPrevious=cursorPositionPrevious;
}

std::string CursorLimits::getParametersMsg()
{
    std::stringstream ss;
    ss << "x (min) = " << this->positionX.min << "\n";
    ss << "x (max) = " << this->positionX.max << "\n";
    ss << "y (min) = " << this->positionY.min << "\n";
    ss << "y (max) = " << this->positionY.max << "\n";
    ss << "Cursor position\n";
    ss << "current:\n";
    ss << "x: " << this->cursorPosition->x << "\n"; 
    ss << "y: " << this->cursorPosition->y << "\n"; 
    ss << "Previous:\n";
    ss << "x: " << this->cursorPositionPrevious->x << "\n"; 
    ss << "y: " << this->cursorPositionPrevious->y << "\n"; 
    return ss.str();
}

bool CursorLimits::positionIsPossible()
{
    bool maxCursorX = cursorPosition->x <= positionX.max;
    bool minCursorX = cursorPosition->x >= positionX.min;
    bool maxCursorY = cursorPosition->y <= positionY.max;
    bool minCursorY = cursorPosition->y >= positionY.min;
    return (maxCursorX && minCursorX && maxCursorY && minCursorY);
}

bool CursorLimits::positionIsOnBorder()
{
    bool borderlineX = (cursorPosition->x==positionX.max || cursorPosition->x==positionX.min);
    bool borderlineY = (cursorPosition->y==positionY.max || cursorPosition->y==positionY.min);
    return (borderlineX || borderlineY);
}

bool CursorLimits::moveIsPossible()
{
    
    return true;
}
