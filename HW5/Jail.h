#ifndef Jail_H
#define Jail_H
#include "Lexan.h"
#include <string>

#include <iostream>


class Jail{

    public:
        Jail() = delete;
        Jail(std::string s);
        Jail(const Jail &o);
        Jail &operator=(const Jail &);
        std::vector<std::vector<std::string>> getLexan() const;
        std::vector<long>getVars() const;
        ~Jail();

        long run(long a = 0L, long b = 0L,
                 long c = 0L, long d  = 0L, 
                 long e = 0L, long f = 0L, 
                 long g = 0L, long h = 0L, 
                 long i = 0L, long j = 0L);


    private:
    std::vector<std::vector<std::string>> lexan;
    std::vector<long> vars;

};


#endif