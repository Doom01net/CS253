#ifndef Lexan_H
#define Lexan_H
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;
class Lexan{

    
    // using string = std::string;
    // public:
    // vector<string> tokens;
    public:
    
    Lexan() = delete;
    Lexan(string s);
    Lexan(const Lexan &other);

    void line(string &in);
    vector<string> getTokens()const;
    size_t size()const;
    bool empty()const;
    void clear();
    string operator[](size_t index)const;
    ~Lexan();
    private:
    vector<string> tokens;
    
    
};
ostream &operator<<(ostream &os, const Lexan &lex);
#endif