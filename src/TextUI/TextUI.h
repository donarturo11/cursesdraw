#ifndef TEXTUI_H 
#define TEXTUI_H


#include <iostream>
#include <map>
#include "ANSIEsc.h"

class TextUI {
  public:
      TextUI();
      ~TextUI();
      void runCommand(std::string command);
                  
   private:
      void greateUser();
      void run();
      void helpCmd();
      void wrongCmd();
      void printText(std::string text);
};

#endif
