#ifndef Board_H
#define Board_H
#include <vector>
#include <string>
#include <iostream>
#include "Rule.h"
class Board
{
public:
    Board(std::string filename, Rule rule, char live, char dead);
    Board(std::string filename, char live, char dead, Rule rule);
    Board(std::string filename, char live, char dead);
    Board(std::string filename, Rule rule);
    Board(std::string filename);
    Board& operator++();
    Rule my_rule;
    
    std::vector<std::vector<char>> in;
private:
    
    char this_dead_char = '.';
    char this_live_char = 'O';
    std::vector<std::vector<char>> out;

};
std::ostream &operator<<(std::ostream &os, const Board &b);

#endif