#include "Rule.h"
#include <regex>
#define PROGRAM_NAME "Rule_CC"
using namespace std;

namespace game_of_life
{

    char alive = 'O';
    char dead = '.';
    string B_args = "3";
    string S_args = "23";
    bool inf = false;
} // namespace game_of_life
bool alive(const char &c)
{
    if (c == game_of_life::alive)
    {
        return true;
    }

    if (c == game_of_life::dead)
    {
        return false;
    }
    cerr << c << " is";
    throw runtime_error(" the unknown char.\n");
}
int get_n_amount(const string &s)
{
    int ret = 0;
    for (char c : s)
    {
        if (c == game_of_life::alive)
            ret++;
    }
    return ret;
}

bool Rule::eval(char nw, char n,char ne, char w,char me, char e,char sw, char s,char se){
            string sum;
            sum.push_back(nw);
            sum.push_back(n);
            sum.push_back(ne);
            sum.push_back(w);
            sum.push_back(e);
            sum.push_back(sw);
            sum.push_back(se);
            sum.push_back(s);
            const char element = me;
            
            if (alive(element))
            {
                if (game_of_life::S_args.size() == 0)
                {

                    if ((get_n_amount(sum) == 2) || (get_n_amount(sum) == 3))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    vector<int> ints;
                    for (char ch : game_of_life::S_args)
                    {
                        ints.push_back((ch - '0'));
                    }
                    auto neig = get_n_amount(sum);
                    auto res = find(begin(ints), end(ints), neig);
                    if (res != end(ints))
                    {
                        //found!
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

            // If a cell is dead, then it becomes alcive for the next generation iff it has exactly three neighbors.
            else if (!alive(element))
            {
                if (game_of_life::B_args.size() == 0)
                {
                    if ((get_n_amount(sum) == 3))
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    vector<int> ints;
                    for (char ch : game_of_life::B_args)
                    {
                        ints.push_back((ch - '0'));
                    }
                    auto neig = get_n_amount(sum);
                    auto res = find(begin(ints), end(ints), neig);
                    if (res != end(ints))
                    {
                        //found!
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }

    return false;
}

string Rule::golly(){
    string ret_str = "B";
    
    string B_part = game_of_life::B_args;
    string S_part = game_of_life::S_args;

    ret_str.append(B_part);
    ret_str.append("/S");
    ret_str.append(S_part);
    return ret_str;
    
}
void Rule::conway(){
    game_of_life::B_args = "3";
    game_of_life::S_args = "23";
}

void Rule::golly(string s){
    game_of_life::B_args = "";
    game_of_life::S_args = "";
    regex r("(B)[0-8]*(/)(S)[0-8]*");
                //check is the string looks like B###/S###
                if (regex_match(s, r))
                {

                    //Begin checking the B part
                    //if the there are more than 2 numbers in B part

                    if (s.find('/') >= 2)
                    {
                        game_of_life::B_args.push_back(s[1]);
                    }
                    if (s.find('/') > 2)
                    {
                        int biggest_num = s[1] - '0';
                        
                        for (size_t i = 2; i < s.find('/'); i++)
                        {

                            int c = s[i] - '0';
                            if (c <= biggest_num)
                            {
                                
                                throw runtime_error(s);
                            }
                            
                            game_of_life::B_args.push_back(s[i]);
                            biggest_num = c;
                        }
                    }

                    //Begin checkig the S part
                    size_t s_index = s.find('S');

                    if (((s.size() - s_index) - 1) == 1)
                    {
                        game_of_life::S_args.push_back(s[s_index + 1]);
                    }

                    // cout << "S numbers amount: " << ((my_option.size() - s_index)-1) << endl;
                    if (((s.size() - s_index) - 1) >= 2)
                    {
                        int biggest_num_s = s[s_index + 1] - '0';
                        
                        game_of_life::S_args.push_back(s[s_index + 1]);
                        
                        for (size_t i = (s_index + 2); i < s.size(); i++)
                        {

                            int c = s[i] - '0';

                            if (c <= biggest_num_s)
                            {
                                throw runtime_error(s);
                                
                            }
                            game_of_life::S_args.push_back(s[i]);
                            biggest_num_s = c;
                        }
                    }
                }


}