#include "TextUI.h"

TextUI::TextUI()
{
    std::string cmd;
    std::string text="";
    text+=ansiEsc::bold;
    text+="Text User Interface (test)\n";
    text+=ansiEsc::reset;
    text+="Test interface.\n";
    text+="To help him type " + ansiEsc::bold + "RUN" + ansiEsc::reset;
    text+=", " + ansiEsc::bold + "run" + ansiEsc::reset;
    text+=" or " + ansiEsc::bold + "start" + ansiEsc::reset;
    text+=" to begin.\n";
    text+="type " + ansiEsc::bold + "help" + ansiEsc::reset + " to get more commands.";
    text+="\n" ;   
    printText(text);
    
    while(true){
        std::cout << ">>> ";
        std::cin >> cmd;
        if (cmd=="quit" || cmd == "quit") break;
        else runCommand(cmd);
    }
    
}

TextUI::~TextUI()
{
    std::string text="";
    text+="This program was written by Artur Wrona (donarturo11)\n";
    text+="If do you have any suggestions,\nsend me message by e-mail:\n";
    text+=ansiEsc::bold;
    text+="artur";
    text+="wrona";
    text+="91";
    text+="@";
    text+="gmail.com";
    text+=ansiEsc::reset;
    text+=".";
    text+="\n"+ansiEsc::reset;
    printText(text);
}

void TextUI::printText(std::string text)
{
    std::cout << text;
}

void TextUI::runCommand(std::string cmd)
{
    if (cmd=="help") helpCmd();
    else wrongCmd();
}

void TextUI::helpCmd()
{
    std::string text="Help";
    printText(text);
}

void TextUI::wrongCmd()
{
    printText(ansiEsc::bold + "Wrong command\n" + ansiEsc::reset);
}




