#ifndef Board_H
#define Board_H
#include "Rule.h"
class Board{
    public: 
    Board(std::string filename, Rule rule, char live, char dead);
    Board(std::string filename, char live, char dead, Rule rule);
    Board(std::string filename, char live, char dead);
    Board(std::string filename, Rule rule);
    Board(std::string filename);
    Board operator++();
};
#endif