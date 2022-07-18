#include "CursorHandle.h"

CursorHandle::CursorHandle(int width, int height)
{
    setRange(&positionX, 0, width-1);
    setRange(&positionY, 0, height-1);
}

CursorHandle::CursorHandle(UserInterface *ui)
{
    this->ui=ui;
    int width = this->ui->getWindowProperties().width;
    int height = this->ui->getWindowProperties().height;
    setRange(&positionX, 0, width-1);
    setRange(&positionY, 0, height-1);
    cursorPosition = new position;
    cursorPositionPrevious = new position;
    this->setCursorPosition(0, 0);
}

CursorHandle::~CursorHandle()
{
    this->ui = nullptr;
}


void CursorHandle::setRange(Range* range, int min, int max)
{
    if (max<min)
        std::swap(min, max);
    range->min=min;
    range->max=max;
}

void CursorHandle::move(int x, int y)
{
    //this->cursorPositionPrevious.x=this->cursorPosition.x;
    //this->cursorPositionPrevious.y=this->cursorPosition.y;
    //this->cursorPosition.x+=x;
    //this->cursorPosition.y+=y;
    int curX=this->cursorPosition->x;
    int curY=this->cursorPosition->y;
    if (x!=0) curX++;
    if (y!=0) curY++;
    fprintf(stderr, "\fmove(%i, %i) = %i, %i\r\n", x, y, this->cursorPosition->x, this->cursorPosition->y);
    this->setCursorPosition(curX, curY);

}

void CursorHandle::setCursorPosition(int x, int y)
{
        
    fprintf(stderr, "setCursorPosition(%i, %i) = %i, %i\r\n", x, y, this->getCursorPosition().x, this->getCursorPosition().y);    
        //setCursorPositionMsg(x, y);
        
    /* Move to UserInterface
    //wmove(this->win, this->cursorPosition.y, this->cursorPosition.x);
    //wrefresh(this->win);
    //printCursorPosition();
    */ 
    this->cursorPosition->x=x;
    this->cursorPosition->y=y;
    
}

void CursorHandle::setCursorPositionMsg(int x, int y)
{
    std::stringstream ss;
    ss << "setCursorPosition(" << x << ", " << y << ")\n";
    ss << "Position is moved: " << this->positionIsMoved() << "\n";
    ss << "x: " << this->cursorPosition->x << "\n";
    ss << "y: " << this->cursorPosition->y << "\n";
    ui->printText(ss.str());
}

position CursorHandle::getCursorPosition()
{
    position curPos;
    curPos.x = this->cursorPosition->x;
    curPos.y = this->cursorPosition->y;
    return curPos;
}


std::string CursorHandle::getParametersMsg()
{
    std::stringstream ss;
    ss << "x (min) = " << this->positionX.min << "\n";
    ss << "x (max) = " << this->positionX.max << "\n";
    ss << "y (min) = " << this->positionY.min << "\n";
    ss << "y (max) = " << this->positionY.max << "\n";
    ss << "Cursor position\n";
    ss << "current:\n";
    ss << "x: " << this->getCursorPosition().x	<< "\n";
    ss << "y: " << this->getCursorPosition().y << "\n";
    //ss << "Previous:\n";
    //ss << "x: " << this->cursorPositionPrevious.x << "\n";
    //ss << "y: " << this->cursorPositionPrevious.y << "\n";
    return ss.str();
}

bool CursorHandle::positionIsPossible()
{
    bool maxCursorX = cursorPosition->x <= positionX.max;
    bool minCursorX = cursorPosition->x >= positionX.min;
    bool maxCursorY = cursorPosition->y <= positionY.max;
    bool minCursorY = cursorPosition->y >= positionY.min;
    return (maxCursorX && minCursorX && maxCursorY && minCursorY);
}

bool CursorHandle::positionIsOnBorder()
{
    bool borderlineX = (cursorPosition->x==positionX.max || cursorPosition->x==positionX.min);
    bool borderlineY = (cursorPosition->y==positionY.max || cursorPosition->y==positionY.min);
    return (borderlineX || borderlineY);
}

bool CursorHandle::positionIsMoved()
{
    bool positionXmoved = cursorPosition->x!=cursorPositionPrevious->x;
    bool positionYmoved = cursorPosition->y!=cursorPositionPrevious->y;
    return (positionXmoved || positionYmoved);
}

bool CursorHandle::moveIsPossible()
{
    return true;
}
