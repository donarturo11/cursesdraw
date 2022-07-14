#ifndef ANSIESC_H
#define ANSIESC_H
#include <iostream>
#include <string>
inline namespace ansiEsc {
    static const std::string begin="\u001b";
    static const std::string reset=begin+"[0m";
    static const std::string bold=begin+"[1m";
    static const std::string italic=begin+"[3m";
    
    static const std::string redFill=begin+"[2;31;41m";
    static const std::string yellowFill=begin+"[2;33;43m";
    static const std::string greenFill=begin+"[2;32;42m";
    static const std::string yellowOnGreen=begin+"[2;33;42m";
    
}

#endif
