#include "UserInterface.h"
#include "KeyboardInput.h"


UserInterface::UserInterface()
{
    setWindowProps(40, 40, 0, 0);
    init();
    endwin();
}

void UserInterface::setWindowProps(int width, int height, int x, int y)
{
    this->windowProps.width=width;
    this->windowProps.height=height;
    this->windowProps.x=x;
    this->windowProps.y=y;

    //cursorhandle = std::make_unique<CursorHandle>(width, height);
    
}

void UserInterface::init()
{
    //newterm(NULL, stderr, stdin);
    initscr();
    clear();
    win = newwin(windowProps.width, windowProps.height, windowProps.x, windowProps.y);
    raw();
    noecho();
    cbreak();
    cursorhandle = new CursorHandle(this);
    this->bindCommands();
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
    this->commandMap["moveUP"]=std::bind(&CursorHandle::move, *cursorhandle, 0, -1);
    this->commandMap["moveDOWN"]=std::bind(&CursorHandle::move, *cursorhandle, 0, 1);
    this->commandMap["moveLEFT"]=std::bind(&CursorHandle::move, *cursorhandle, -1, 0);
    this->commandMap["moveRIGHT"]=std::bind(&CursorHandle::move, *cursorhandle, 1, 0);
}

void UserInterface::putChar(char c)
{
    wmove(this->win, cursorhandle->getCursorPosition().y, cursorhandle->getCursorPosition().x);
    if (c==winch(this->win)) c=' ';
    waddch(this->win, c);
    wmove(this->win, cursorhandle->getCursorPosition().y, cursorhandle->getCursorPosition().x);
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
    //setCursorPosition(cursorPosition.x, cursorPosition.y);
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
    ss << cursorhandle->getParametersMsg() << "\n";
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

void UserInterface::printCursorPosition()
{
    std::stringstream msg;
    msg << "Cursor parameters" << "\n";
    msg << cursorhandle->getParametersMsg() << "\n";
    msg << "PositionIsPossible: " << cursorhandle->positionIsPossible() << "\n";
    msg << "PositionIsOnBorder: " << cursorhandle->positionIsOnBorder() << "\n";
    msg << "PositionIsMoved: " << cursorhandle->positionIsMoved() << "\n";
    msg << "MoveIsPossible: " << cursorhandle->moveIsPossible() << "\n";
    printText(msg.str());
}

void UserInterface::printCursorPositionShort()
{
    std::stringstream ss;
    ss << "Cursor position:  ";
    ss << "x=" << cursorhandle->getCursorPosition().x << " | " << "y=" << cursorhandle->getCursorPosition().y;

    mvwprintw(this->win, windowProps.height-2, 1, "Cursor");
    wmove(this->win, cursorhandle->getCursorPosition().y, cursorhandle->getCursorPosition().x);
    wrefresh(this->win);
}

objectProps UserInterface::getWindowProperties()
{
    return this->windowProps;
}
