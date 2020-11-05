#include "Lexan.h"
#include "Lexan.h"      // I meant to do that.
#include <iostream>
 
using namespace std;
 
int main() {
    const auto prog = R"(
        n  = a n += b C/=123 # z=zz
 
        ifn≤3returN1FI)";
 
    const Lexan lex(prog);
    for (size_t i=0; i<lex.size(); i++)
        cout << lex[i] << '\n';
    cout << lex << endl;
    
    return 0;
}
