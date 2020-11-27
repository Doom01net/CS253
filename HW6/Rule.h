#ifndef Rule_H
#define Rule_H
#include <iostream>

class Rule{

    public:

    void conway();
    void golly(std::string s);
    std::string golly();
    bool eval(char nw, char n,char ne, char w,char me, char e,char sw, char s,char se);
    
};

#endif