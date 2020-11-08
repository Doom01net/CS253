#include "Jail.h"
#include <cctype>
#include <regex>
#include <string>
using namespace std;

ostream &operator<<(ostream &os, const vector<vector<string>> &vec)
{
    for (vector<string> v : vec)
    {
        os << "[" << v.at(0) << "," << v.at(1) << "] ";
    }
    os << "\n";
    return os;
}
ostream &operator<<(ostream &os, const vector<long> &vec)
{
    for (long v : vec)
    {
        os << "[ " << v << " ],";
    }
    os << "\n";
    return os;
}
Jail::Jail(string s)
{
    Lexan lex(s);

    for (size_t i = 0; i < lex.size(); i++)
    {
        //cout << lex[i] << '\n';
        // arr [type] [token]
        regex r("[0-9]+");
        regex var("([a-z])");
        if (lex[i] == "return")
        {
            vector<string> v;
            v.push_back("COMM");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (lex[i] == "print")
        {
            vector<string> v;
            v.push_back("COMM");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (lex[i] == "if")
        {
            vector<string> v;
            v.push_back("IFS");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (lex[i] == "fi")
        {
            vector<string> v;
            v.push_back("IFE");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }

        else if (lex[i] == "nwl")
        {
            // vector<string> v;
            // v.push_back("NL");
            // v.push_back(lex[i]);
            // Jail::lexan.push_back(v);
            continue;
        }

        else if (regex_match(lex[i], r))
        {
            vector<string> v;
            v.push_back("NUM");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (lex[i] == "-=" || lex[i] == "+=" || lex[i] == "*=" ||
                 lex[i] == "/=")
        {
            vector<string> v;
            v.push_back("OP");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (lex[i] == "≠" || lex[i] == "≤" || lex[i] == "≥" ||
                 lex[i] == "<" || lex[i] == ">")
        {
            vector<string> v;
            v.push_back("LOGIC");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (lex[i] == "=")
        {
            vector<string> v;
            v.push_back("EA");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else if (regex_match(lex[i], var))
        {
            vector<string> v;
            v.push_back("VAR");
            v.push_back(lex[i]);
            Jail::lexan.push_back(v);
        }
        else
        {
            cerr << "Error recognizing token " << lex[i] << endl;
            exit(1);
        }
        // if(lex[i]){
        //     vector<string> v;
        //     v.push_back("COMM");
        //     v.push_back(lex[i]);
        //     Jail::lexan.push_back(v);

        //     Jail::lexan.push_back({"NUM", lex[i]});
        // }
    }

    //cout << lexan << endl;
}
void analize()
{
}
long Jail::run(long a, long b, long c,
               long d, long e, long f,
               long g, long h, long i,
               long j)
{
    for (size_t k = 0; k < 26; k++)
    {
        vars.push_back(0);
    }
    vars[0] = a;
    vars[1] = b;
    vars[2] = c;
    vars[3] = d;
    vars[4] = e;
    vars[5] = f;
    vars[6] = g;
    vars[7] = h;
    vars[8] = i;
    vars[9] = j;

   

    for (size_t k = 10; k < 26; k++)
    {
        vars.push_back(0);
    }
    //cout << "A =  " << vars.at(0) << endl;
   // cout << "Size of lexan is " << lexan.size() << endl;
   // cout << "Size of vars is " << vars.size() << endl;
    int ifs_amount = 0;
    int ife_amount = 0;
    bool ifs_open = false;
    // bool ife_closed = false;

    for (int z = 0; static_cast<size_t>(z) < lexan.size(); z++)
    {
        // cout  << "Parse+1. Currently on symbol " << lexan.at(z).at(1) << endl;
        // cout << "A =  " << vars.at(0) << endl;
        // cout << "F =  " << vars.at(5) << endl;
        // cout << "Z =  " << vars.at(25) << endl;
        //bool ignore = false;
        // cout << "Z is " << z << endl;

        if (lexan.at(z).at(0) == "OP")
        {

            if (z == 0)
            {
                throw runtime_error("Syntax error in the beginning. Operator without a var");
            }
            if (lexan.at(z - 1).at(0) == "VAR")
            {
                if (static_cast<size_t>(z) >= lexan.size() - 1)
                {
                    throw runtime_error("Var OP end_of_file");
                }

                if (lexan.at(z + 1).at(0) == "VAR")
                {

                    int l_var_num = lexan.at(z - 1).at(1)[0] - 'a';
                    int r_var_num = lexan.at(z + 1).at(1)[0] - 'a';
                    if (lexan.at(z).at(1) == "*=")
                    {

                        vars[l_var_num] *= vars.at(r_var_num);
                    }
                    else if (lexan.at(z).at(1) == "-=")
                    {
                        vars[l_var_num] *= vars.at(r_var_num);
                    }
                    else if (lexan.at(z).at(1) == "+=")
                    {
                        vars[l_var_num] *= vars.at(r_var_num);
                    }
                    else if (lexan.at(z).at(1) == "/=")
                    {
                        vars[l_var_num] *= vars.at(r_var_num);
                    }
                }
                else if (lexan.at(z + 1).at(0) == "NUM")
                {

                    int l_var_num = lexan.at(z - 1).at(1)[0] - 'a';
                    //cout << "the number of var about to be OP to a num is " << l_var_num << endl;

                    if (lexan.at(z).at(1) == "*=")
                    {

                        vars[l_var_num] *= stol(lexan.at(z + 1).at(1));
                    }
                    else if (lexan.at(z).at(1) == "-=")
                    {
                        vars[l_var_num] -= stol(lexan.at(z + 1).at(1));
                    }
                    else if (lexan.at(z).at(1) == "+=")
                    {
                        vars[l_var_num] += stol(lexan.at(z + 1).at(1));
                    }
                    else if (lexan.at(z).at(1) == "/=")
                    {
                        vars[l_var_num] /= stol(lexan.at(z + 1).at(1));
                    }
                }
                else
                {
                    throw runtime_error("VAR " + lexan.at(z - 1).at(1) + " " + lexan.at(z).at(1) + " " + lexan.at(z + 1).at(1));
                }
            }
            else
            {
                runtime_error("There must be var before operator symbol" + lexan.at(z - 1).at(1) + " " + lexan.at(z).at(1));
            }
        }
        else if (lexan.at(z).at(0) == "EA")
        {

            if (z == 0)
            {
                throw runtime_error("Syntax error in the beginning. Operator without a var");
            }
            if (static_cast<size_t>(z) >= lexan.size() - 1)
                {
                    throw runtime_error("= at the end of file. Bad");
                }
            if (lexan.at(z - 1).at(0) == "VAR")
            {
                

                if (lexan.at(z + 1).at(0) == "VAR")
                {
                    
                    int l_var_num = lexan.at(z - 1).at(1)[0] - 'a';
                    int r_var_num = lexan.at(z + 1).at(1)[0] - 'a';
                    vars[l_var_num] = vars.at(r_var_num);
                    //cout << "Updated var. Now var at " << l_var_num << " is " << r_var_num << endl;
                }
                else if (lexan.at(z + 1).at(0) == "NUM")
                {

                    int l_var_num = lexan.at(z - 1).at(1)[0] - 'a';
                    vars[l_var_num] = stol(lexan.at(z + 1).at(1));
                    //cout << "Updated var. Now var at " << l_var_num << " is " << stol(lexan.at(z + 1).at(1)) << endl;
                }

                else
                {
                    throw runtime_error("Err. VAR " + lexan.at(z - 1).at(1) + " " + lexan.at(z).at(1) + " " + lexan.at(z + 1).at(1));
                }
            }
            else
            {
                runtime_error("There must be var before = symbol" + lexan.at(z - 1).at(1) + " " + lexan.at(z).at(1));
            }
        }
        else if (lexan.at(z).at(0) == "COMM")
        {
            if (lexan.at(z).at(1) == "return")
            {
                // cout << "Got to return" << endl;
                if (static_cast<size_t>(z) >= lexan.size() - 1)
                {
                    throw runtime_error("return, end of file. Error");
                }
                if (lexan.at(z + 1).at(0) == "VAR")
                {
                    if ((ifs_amount - ife_amount) != 0)
                    {
                        throw runtime_error("IFs and FIs don't match");
                    }
                    int l_var_num = lexan.at(z + 1).at(1)[0] - 'a';
                    long ret_val = vars[l_var_num];
                    fill(vars.begin(), vars.end(), 0);
                    return ret_val;
                    // cout << "WRONG!" << endl;
                }
                else if (lexan.at(z + 1).at(0) == "NUM")
                {
                    if ((ifs_amount - ife_amount) != 0)
                    {
                        throw runtime_error("IFs and FIs don't match");
                    }
                    long ret_val = stol(lexan.at(z + 1).at(1));
                    fill(vars.begin(), vars.end(), 0);
                    return ret_val;
                    // cout << "WRONG!" << endl;
                }
                else
                {
                    throw runtime_error("Oops! rater retern there is an illegal token");
                }
            }
            if (lexan.at(z).at(1) == "print")
            {
                //cout << "print" << endl;
                if (static_cast<size_t>(z) >= lexan.size() - 1)
                {
                    throw runtime_error("print, end of file. Error");
                }
                if (lexan.at(z + 1).at(0) == "VAR")
                {
                    int l_var_num = lexan.at(z + 1).at(1)[0] - 'a';
                    cout << vars[l_var_num] << "\n";
                }
                else if (lexan.at(z + 1).at(0) == "NUM")
                {
                    cout << stol(lexan.at(z + 1).at(1)) << "\n";
                }
                else
                {
                    throw runtime_error("Oops! rater retern there is an illegal token");
                }
            }
        }
        else if (lexan.at(z).at(0) == "IFS")
        {
            if (static_cast<size_t>(z + 4) >= lexan.size())
            {
                throw runtime_error("No FI after IF. EOF reached");
            }
            ifs_open = true;
            ifs_amount++;
            //cout << "ifs amount " << ifs_amount << endl;
            if ((lexan.at(z + 1).at(0) == "NUM" || lexan.at(z + 1).at(0) == "VAR") &&
                (lexan.at(z + 2).at(0) == "LOGIC" || lexan.at(z + 2).at(0) == "EA") &&
                (lexan.at(z + 3).at(0) == "NUM" || lexan.at(z + 3).at(0) == "VAR"))
            {

                //check is statement is true
                if (lexan.at(z + 2).at(0) == "EA")
                {

                    long lhs = (lexan.at(z + 1).at(0) == "NUM") ? stol(lexan.at(z + 1).at(1)) : vars[(lexan.at(z + 1).at(1)[0] - 'a')];
                    long rhs = (lexan.at(z + 3).at(0) == "NUM") ? stol(lexan.at(z + 3).at(1)) : vars[(lexan.at(z + 3).at(1)[0] - 'a')];
                    if (lhs == rhs)
                    {
                        continue;
                    }
                    else
                    {

                        if (lexan.at(z + 4).at(0) == "IFE")
                        {
                            //cout << "ifE amount " << ifs_amount << endl;
                            
                            continue;
                        }
                        else if (lexan.at(z + 4).at(0) == "COMM")
                        {
                            z += 5;
                            continue;
                            
                        }
                        else
                        {
                            z += 6;
                        }
                    }
                }
                else if (lexan.at(z + 2).at(0) == "LOGIC")
                {
                    long lhs = (lexan.at(z + 1).at(0) == "NUM") ? stol(lexan.at(z + 1).at(1)) : vars[(lexan.at(z + 1).at(1)[0] - 'a')];
                    long rhs = (lexan.at(z + 3).at(0) == "NUM") ? stol(lexan.at(z + 3).at(1)) : vars[(lexan.at(z + 3).at(1)[0] - 'a')];

                    if (lexan.at(z + 2).at(1) == "≤")
                    {
                        if (lhs <= rhs)
                        {
                            continue;
                        }
                        else
                        {
                            if (lexan.at(z + 4).at(0) == "IFE")
                            {
                                
                                continue;
                            }
                            else if (lexan.at(z + 4).at(0) == "COMM")
                            {
                                z += 5;
                                continue;
                            }
                            else
                            {
                                z += 6;
                            }
                        }
                    }
                    else if (lexan.at(z + 2).at(1) == "≥")
                    {
                        if (lhs >= rhs)
                        {
                            continue;
                        }
                        else
                        {
                            if (lexan.at(z + 4).at(0) == "IFE")
                            {
                                
                                continue;
                            }
                            else if (lexan.at(z + 4).at(0) == "COMM")
                            {
                                z += 5;
                                continue;
                            }
                            else
                            {
                                z += 6;
                            }
                        }
                    }
                    else if (lexan.at(z + 2).at(1) == "≠")
                    {
                        if (lhs != rhs)
                        {
                            continue;
                        }
                        else
                        {
                            if (lexan.at(z + 4).at(0) == "IFE")
                            {
                               
                                continue;
                            }
                            else if (lexan.at(z + 4).at(0) == "COMM")
                            {
                                z += 5;
                                continue;
                            }
                            else
                            {
                                z += 6;
                            }
                        }
                    }
                    else if (lexan.at(z + 2).at(1) == "<")
                    {
                        if (lhs < rhs)
                        {
                            continue;
                        }
                        else
                        {
                            if (lexan.at(z + 4).at(0) == "IFE")
                            {
                                
                                continue;
                            }
                            else if (lexan.at(z + 4).at(0) == "COMM")
                            {
                                z += 5;
                                continue;
                            }
                            else
                            {
                                z += 6;
                            }
                        }
                    }
                    else if (lexan.at(z + 2).at(1) == ">")
                    {
                        if (lhs > rhs)
                        {
                            continue;
                        }
                        else
                        {
                            if (lexan.at(z + 4).at(0) == "IFE")
                            {
                                
                                continue;
                            }
                            else if (lexan.at(z + 4).at(0) == "COMM")
                            {
                                z += 5;
                                continue;
                            }
                            else
                            {
                                z += 6;
                            }
                        }
                    }
                }
            }
            else
            {
                throw runtime_error("If statement MUST have a a val LOGIC(or)= val after itself");
            }
        }
        else if (lexan.at(z).at(0) == "IFE")
        {
            if (ifs_open)
            {
                
                ife_amount++;
                
                continue;
            }
            else
            {
                throw runtime_error("FI without an IF! Error");
            }
        }
        else if (lexan.at(z).at(0) == "VAR"){
            //cout  << "Varible " << lexan.at(z).at(1)[0] << " encountered" << endl;
            
            continue;
        }
        else if (lexan.at(z).at(0) == "LOGIC"){
            continue;
        }
        else if (lexan.at(z).at(0) == "NUM"){
            continue;
        }
        else{
            throw runtime_error("Something very wrong happened");
        }
    }

    // cout << vars << endl;

    return 0;
}

std::vector<std::vector<std::string>> Jail::getLexan() const{
    return lexan;
}
std::vector<long> Jail::getVars() const{
    return vars;

}

Jail::Jail(const Jail &o){
    vars = o.getVars();
    lexan = o.getLexan();

}
Jail &Jail::operator=(const Jail& rhs){
    vars = rhs.getVars();
    lexan = rhs.getLexan();
    return *this;
}
Jail::~Jail()
{
    vars.clear();
    lexan.clear();
}
