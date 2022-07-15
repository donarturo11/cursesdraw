#include "UserInterface.h"
#include "KeyboardInput.h"


UserInterface::UserInterface()
{
    setWindowProps(40, 40, 0, 0);
    cursorlimits->updateCursorPosition(&cursorPosition, &cursorPositionPrevious);
    setCursorPosition(0, 0);
    init();
    endwin();
}

void UserInterface::setWindowProps(int width, int height, int x, int y)
{
    this->windowProps.width=width;
    this->windowProps.height=height;
    this->windowProps.x=x;
    this->windowProps.y=y;
    //cursorlimits = std::make_unique<CursorLimits>(x, y);
    cursorlimits = std::make_unique<CursorLimits>(width, height);
}



void UserInterface::init()
{
    //newterm(NULL, stderr, stdin);
    initscr();
    clear();
    win = newwin(windowProps.width, windowProps.height, windowProps.x, windowProps.y);
    this->bindCommands();
    raw();
    noecho();
    cbreak();
    KeyboardInput keyboard(this);
}

void UserInterface::runCmd(std::string cmd)
{
    std::string msg="Command " + cmd + " ";
    if (this->commandMap[cmd]){
       this->commandMap[cmd]();
       msg+="is defined";
    } else {
       msg+="is not defined";
       this->printText(msg);
   }
   //this->printText(msg);
}

void UserInterface::bindCommands()
{
    //this->commandMap["start"]=[this](){this->printText("Start");};
    this->commandMap["start"]=std::bind(&UserInterface::start, this);
    this->commandMap["clear"]=std::bind(&UserInterface::clearScreen, this);
    this->commandMap["addX"]=std::bind( &UserInterface::putChar, this, 'x');
    this->commandMap["bold"]=std::bind( &UserInterface::setAttr, this, A_BOLD | A_REVERSE);
    this->commandMap["normal"]=std::bind( &UserInterface::setAttr, this, A_NORMAL);
    this->commandMap["getAttributes"]=std::bind( &UserInterface::getAttr, this);
    this->commandMap["printCursorPosition"]=std::bind(&UserInterface::printCursorPosition, this);
    this->commandMap["moveUP"]=std::bind(&UserInterface::move, this, 0, -1);
    this->commandMap["moveDOWN"]=std::bind(&UserInterface::move, this, 0, 1);
    this->commandMap["moveLEFT"]=std::bind(&UserInterface::move, this, -1, 0);
    this->commandMap["moveRIGHT"]=std::bind(&UserInterface::move, this, 1, 0);
}

void UserInterface::move(int x, int y)
{
    x+=this->cursorPosition.x;
    y+=this->cursorPosition.y;
    setCursorPosition(x, y);
}

void UserInterface::setCursorPosition(int x, int y)
{
    this->cursorPositionPrevious.x=this->cursorPosition.x;
    this->cursorPositionPrevious.y=this->cursorPosition.y;
    if (cursorlimits->positionIsPossible()){
        this->cursorPosition.x=x;
        this->cursorPosition.y=y;
    } else {
        this->cursorPosition.x=this->cursorPositionPrevious.x;
        this->cursorPosition.y=this->cursorPositionPrevious.y;
    }
    //wmove(this->win, this->cursorPosition.y, this->cursorPosition.x);
    //wrefresh(this->win);
    //printCursorPosition();
}


void UserInterface::putChar(char c)
{
    wmove(this->win, this->cursorPosition.y, this->cursorPosition.x);
    if (c==winch(this->win)) c=' ';
    waddch(this->win, c);
    wmove(this->win, this->cursorPosition.y, this->cursorPosition.x);
    wrefresh(this->win);
}
void UserInterface::setAttr(int attr)
{
    wattrset(this->win, attr);
    wrefresh(this->win);
}

void UserInterface::getAttr()
{
    std::stringstream ss;
    ss << "winch: " << (char) winch(this->win);
    printText(ss.str());
}

void UserInterface::clearScreen()
{
    wclear(this->win);
    wrefresh(this->win);
}

void UserInterface::printText(std::string text)
{
    wclear(this->win);
    mvwprintw(this->win, 0, 0, "%s", text.c_str());
    setCursorPosition(cursorPosition.x, cursorPosition.y);
    wrefresh(this->win);

}

void UserInterface::beep(int freq, int length)
{
    fprintf(stderr, "\a");
}

void UserInterface::start()
{
    std::stringstream ss;
    ss << "UserInterface started" << "\n";
    ss << cursorlimits->getParametersMsg() << "\n";
    ss << "\a";
    printText(ss.str());
    //this->running = true;
}

void UserInterface::stop()
{
    printText("Stopped");
    this->running = false;
}

bool UserInterface::getRunningStatus()
{
    return this->running;
}

position UserInterface::getCursorPosition()
{
    return this->cursorPosition;
}


void UserInterface::printCursorPosition()
{
    std::stringstream msg;
    msg << "Cursor position\n";
    //msg << "Position is on border: " << positionIsOnBorder() << "\n";
    //msg << "Position is possible: " << positionIsPossible() << "\n";
    msg << "x = " << cursorPosition.x << "\n";
    msg << "y = " << cursorPosition.y << "\n";
    msg << "Cursor parameters" << "\n";
    msg << cursorlimits->getParametersMsg() << "\n";
    msg << "PositionIsPossible: " << cursorlimits->positionIsPossible() << "\n";
    msg << "PositionIsOnBorder: " << cursorlimits->positionIsOnBorder() << "\n";
    msg << "PositionIsMoved: " << cursorlimits->positionIsMoved() << "\n";
    msg << "MoveIsPossible: " << cursorlimits->moveIsPossible() << "\n";
    printText(msg.str());
}

void UserInterface::printCursorPositionShort()
{
    std::stringstream ss;
    ss << "Cursor position:  ";
    ss << "x=" << cursorPosition.x << " | " << "y=" << cursorPosition.y;

    mvwprintw(this->win, windowProps.height-2, 1, "Cursor");
    wmove(this->win, cursorPosition.y, cursorPosition.x);
    wrefresh(this->win);
}
