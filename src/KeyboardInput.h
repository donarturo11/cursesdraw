#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H
#include "UserInterface.h"
#include <map>


class KeyboardInput
{
    public:
        KeyboardInput(UserInterface* ui);
        ~KeyboardInput();
        bool isArrowPressed(int code);
    private:
        void initShortcuts();
        void keyboardControl(int code);
        void controlLoop();
        void commandLine();
        void arrowKey(int code);
    protected:
        UserInterface* ui;
        bool focus;
        std::map<int, std::string> shortcuts;
};
#endif
