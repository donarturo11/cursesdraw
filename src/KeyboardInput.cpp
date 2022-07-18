#include "KeyboardInput.h"

KeyboardInput::KeyboardInput(UserInterface* ui)
{
    this->ui=ui;
    this->initShortcuts();
    keypad(stdscr, true);
    controlLoop();
}

KeyboardInput::~KeyboardInput()
{
    this->ui=nullptr;
}

void KeyboardInput::controlLoop()
{
    ui->runCmd("clear");
    this->focus=true;
    int keyCode;
    while (this->focus){
        keyCode=getch();
        if (keyCode=='\e') break;
        if (keyCode=='/') {
            break;
        }
        keyboardControl(keyCode);    
        }
    if (keyCode=='/') commandLine();
}

void KeyboardInput::commandLine()
{
    // to implement or move to another class    
}

void KeyboardInput::initShortcuts()
{
    this->shortcuts['a']="beep";
    this->shortcuts['s']="start";
    this->shortcuts['c']="clear";
    this->shortcuts['x']="addX";
    this->shortcuts['p']="printCursorPosition";
    this->shortcuts['b']="bold";
    this->shortcuts['n']="normal";
    this->shortcuts['?']="getAttributes";
    this->shortcuts[KEY_UP]="moveUP";
    this->shortcuts[KEY_DOWN]="moveDOWN";
    this->shortcuts[KEY_LEFT]="moveLEFT";
    this->shortcuts[KEY_RIGHT]="moveRIGHT";
}

void KeyboardInput::keyboardControl(int code)
{
    if (isArrowPressed(code)) arrowKey(code);
    else ui->runCmd(this->shortcuts[code]);
}

bool KeyboardInput::isArrowPressed(int code)
{
    return (code==KEY_UP || code==KEY_DOWN || code==KEY_RIGHT || code==KEY_LEFT);
}

void KeyboardInput::arrowKey(int code)
{
    ui->runCmd(this->shortcuts[code]);
}
