#ifndef Lexan_H
#define Lexan_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <ostream>
class Lexan{

    
    // using string = std::string;
    // public:
    // vector<string> tokens;
    public:
    
    Lexan() = delete;
    Lexan(std::string s);
    Lexan(const Lexan &other);

    void line(std::string &in);
    std::vector<std::string> getTokens()const;
    size_t size()const;
    bool empty()const;
    void clear();
    std::string operator[](size_t index)const;
    ~Lexan();
    private:
    std::vector<std::string> tokens;
    
    
};
std::ostream &operator<<(std::ostream &os, const Lexan &lex);
#endif