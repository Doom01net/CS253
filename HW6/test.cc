#include "Board.h"
#include "Rule.h"
#include "Board.h"
#include "Rule.h"
#include <iostream>
#include <cassert>
 
using namespace std;
 
int main(int, char* argv[]) {
    Rule r;
    assert(r.golly() == "B3/S23");
    
    
    // Board g1("CS253", r, '@', '`');
    
    Board b(argv[1]);
    cout << b << '\n';
    cout << ++b << '\n';
    cout << ++b << '\n';
    // cout << g1 << '\n';
    // cout << ++g1 << '\n';
    // cout << ++g1 << "\n\n";
 
    // r.conway();
    // assert(r.golly() == "B3/S23");
    // Board g2("blinker", r);
    // cout << g2 << '\n';
    // cout << ++g2 << '\n';
    // cout << ++g2 << "\n\n";
 
    // Board g3("/s/bach/a/class/cs253/pub/Life/r");
    // for (int i=0; i<500; i++)
    //     ++g3;
    // cout << g3;
}