#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>
#include <getopt.h>
#include <regex>
#include <algorithm>
using namespace std;
string program_name;

namespace game_of_life
{

    char alive = 'O';
    char dead = '.';
    string B_args = "";
    string S_args = "";
    bool inf = false;
} // namespace game_of_life
void debug(const string &s) { cout << "DEBUG: " << s << endl; }

ostream &operator<<(ostream &os, const vector<vector<char>> &vec)
{
    for (vector<char> v : vec)
    {
        for (char c : v)
            os << c << "";
        os << endl;
    }
    return os;
}

void fill_from_file(string f, vector<vector<char>> &v)
{
    ifstream file(f);

    if (file.fail())
    {
        cerr << "File doesn't exist. Err in program " << program_name << endl;
        exit(1);
    }
    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        v.push_back(row);
    }
}
void fill_from_cin(istream &in, vector<vector<char>> &v)
{
cout << "Got to fill from cin: " <<endl;
    for (string line; getline(in, line);)
    {
        cout << "Line: "<< line <<endl;
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        v.push_back(row);
    }
}

void error_check_matrix(vector<vector<char>> &v)
{
    cout<< "vector: " << v << endl;

    if (v.size() < 2)
    {
        cerr << "There must be at least 2 lines. Program " << program_name << endl;
        exit(1);
    }

    for (vector<char> c : v)
        if (c.size() < 2)
        {
            cerr << "There must be at least 2 cells. Program " << program_name << endl;
            exit(1);
        }
    size_t row_size = v[0].size();
    for (vector<char> row : v)
    {
        if (row_size != row.size())
        {
            cerr << "All rows must be same length. Program " << program_name << endl;
            exit(1);
        }
    }
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

    cerr << "Found a char: " << c << " That doesn't match in program " << program_name << endl;
    exit(1);
}

bool dead(const char &c)
{
    return !(alive(c));
}

void update_generation(vector<vector<char>> &in, vector<vector<char>> &out)
{
    // debug("Begin DEBUG of Update generation");
    int r = (in.size());
    int c = (in[0].size());
    //cout << "B args: " << game_of_life::B_args << "size: " << game_of_life::B_args.size() << endl;
    //cout << "S args: " << game_of_life::S_args << "size: " << game_of_life::S_args.size() << endl;

    for (int i = 0; i < r; i++)
    {

        for (int j = 0; j < c; j++)
        {

            char up_left = in[(i - 1 + r) % r][(j - 1 + c) % c]; //
            char up = in[(i - 1 + r) % r][j];
            char up_right = in[(i - 1 + r) % r][(j + 1 + c) % c];
            char left = in[i][(j - 1 + c) % c];
            char right = in[i][(j + 1 + c) % c];
            char d_left = in[(i + 1 + r) % r][(j - 1 + c) % c];
            char down = in[(i + 1 + r) % r][j];
            char d_right = in[(i + 1 + r) % r][(j + 1 + c) % c];

            string sum;
            sum.push_back(up_left);
            sum.push_back(up);
            sum.push_back(up_right);
            sum.push_back(left);
            sum.push_back(right);
            sum.push_back(d_left);
            sum.push_back(d_right);
            sum.push_back(down);

            // If a cell is alive, then it stays alive for the next generation iff it has exactly two or three neighbors.
            if (alive(in[i][j]))
            {
                if (game_of_life::S_args.size() == 0)
                {

                    if ((get_n_amount(sum) == 2) || (get_n_amount(sum) == 3))
                    {
                        out[i][j] = game_of_life::alive;
                    }
                    else
                    {
                        out[i][j] = game_of_life::dead;
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
                        out[i][j] = game_of_life::alive;
                    }
                    else
                    {
                        out[i][j] = game_of_life::dead;
                    }
                }
            }

            // If a cell is dead, then it becomes alcive for the next generation iff it has exactly three neighbors.
            else if (dead(in[i][j]))
            {
                if (game_of_life::B_args.size() == 0)
                {
                    if ((get_n_amount(sum) == 3))
                    {
                        out[i][j] = 'O';
                    }
                    else
                    {
                        out[i][j] = '.';
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
                        out[i][j] = game_of_life::alive;
                    }
                    else
                    {
                        out[i][j] = game_of_life::dead;
                    }
                }
            }
        }
    }
}

// void parse_options(){
//     int option;
//     while ((option = ))

// }

void run(int argc, char *argv[])
{
    cout << "Optintd" << optind << endl; // how many options
    cout << "argc" << argc << endl; // how many options
    vector<vector<char>> matrix_in;
    vector<vector<char>> matrix_out;

    if(optind + 1 < argc){
        cerr << "options error " << program_name << endl;
        exit(1);
    }
    if ((argc - optind) >= 2)
    {
        cerr << "only 1 file allowed " << program_name << endl;
        exit(1);
    }

    // if (argc-1 !=){

    // }
    if ((optind + 1) == argc)
    {
       
        fill_from_file(argv[argc-1], matrix_in);
        matrix_out = matrix_in;
    }
    

    

    if (argc == optind)
    {
        cout<<"got here"<< endl;
        fill_from_cin(cin, matrix_in);
        matrix_out = matrix_in;
    }

    error_check_matrix(matrix_in);

    update_generation(matrix_in, matrix_out);

    cout << matrix_out;

    if (game_of_life::inf)
    {
        while (1)
        {
            cout << "\n";

            vector<vector<char>> matrix_temp;
            matrix_temp = matrix_in;
            matrix_in = matrix_out;
            matrix_out = matrix_temp;
            update_generation(matrix_in, matrix_out);
            cout << matrix_out;
        }
    }
}

void parse_options(int argc, char *argv[])
{
    string born_rule = "";
    string survive_rule = "";

    ;

    int gflags = 0;
    int lflags = 0;
    int dflags = 0;
    int iflags = 0;
    char option;
    while ((option = getopt(argc, argv, "l:d:ig:")) != -1)
    {
        switch (option)
        {

        case 'g':
        {
            //golly rule.

            if (!gflags)
            {
                string my_option = optarg;
                regex r("(B)[0-8]*(/)(S)[0-8]*");
                //check is the string looks like B###/S###
                if (regex_match(my_option, r))
                {

                    //Begin checking the B part
                    //if the there are more than 2 numbers in B part

                    if (my_option.find('/') >= 2)
                    {
                        game_of_life::B_args.push_back(my_option[1]);
                    }
                    if (my_option.find('/') > 2)
                    {
                        int biggest_num = my_option[1] - '0';

                        for (size_t i = 2; i < my_option.find('/'); i++)
                        {

                            int c = my_option[i] - '0';
                            if (c <= biggest_num)
                            {
                                cerr << "B part of -g tag in not in strictly ascending order" << program_name << endl;
                                exit(1);
                            }
                            game_of_life::B_args.push_back(my_option[i]);
                            biggest_num = c;
                        }
                    }

                    //Begin checkig the S part
                    size_t s_index = my_option.find('S');

                    if (((my_option.size() - s_index) - 1) == 1)
                    {
                        game_of_life::S_args.push_back(my_option[s_index + 1]);
                    }

                    // cout << "S numbers amount: " << ((my_option.size() - s_index)-1) << endl;
                    if (((my_option.size() - s_index) - 1) >= 2)
                    {
                        int biggest_num_s = my_option[s_index + 1] - '0';

                        game_of_life::S_args.push_back(my_option[s_index + 1]);

                        for (size_t i = (s_index + 2); i < my_option.size(); i++)
                        {

                            int c = my_option[i] - '0';

                            if (c <= biggest_num_s)
                            {
                                cerr << "S part of -g tag in not in strictly ascending order" << program_name << endl;
                                exit(1);
                            }
                            game_of_life::S_args.push_back(my_option[i]);
                            biggest_num_s = c;
                        }
                    }
                }

                else
                {
                    cerr << "Bad format of -g tag" << program_name << endl;
                    exit(1);
                }

                gflags++;
                
                //At this point the g tag is nice and toit!
                // cout << "-g ready" << endl;

                
                
                //cout << my_option << endl;
            }
            else
            {
                cerr << "-g tag appears twice. Terminating" << program_name << endl;
                exit(1);
            }
            break;
        }
        case 'l':
        {
            char live_char = '~';
            if (!lflags)
            {
                // cout << "We got to the l tag yee!" << endl;
                string my_option = optarg;
                regex r("(.)");
                if (regex_match(my_option, r) && (my_option.size() == 1))
                {
                    live_char = my_option[0];
                }
                else
                {
                    cerr << "-l tag wrong arg. Terminating" << program_name << endl;
                    exit(1);
                }
                //This is the live-char
            }
            else
            {
                cerr << "-l tag appears twice. Terminating" << program_name << endl;
                exit(1);
            }
            game_of_life::alive = live_char;
            lflags++;
            
            break;
        }
        case 'd':
        {
            char dead_char = '~';
            if (!dflags)
            {
                // cout << "We got to the d tag yee!" << endl;
                string my_option = optarg;
                regex r("(.)");
                if (regex_match(my_option, r) && (my_option.size() == 1))
                {
                    dead_char = my_option[0];
                    game_of_life::dead = dead_char;
                }
                else
                {
                    cerr << "-d tag wrong arg. Terminating" << program_name << endl;
                    exit(1);
                }
                //This is the live-char
            }
            else
            {
                cerr << "-d tag appears twice. Terminating" << program_name << endl;
                exit(1);
            }

            dflags++;
            
            break;
        }
        case 'i':
        {
            if (!iflags)
            {
                game_of_life::inf = true;
            }

            else
            {
                cerr << "-i tag appears twice. Terminating" << program_name << endl;
                exit(1);
            }
            iflags++;
            
            break;
        }
        default:
        {
            cerr << "Unknown option Terminating" << program_name << endl;
            exit(1);
            break;
        }
        }
    }

    
}

int main(int argc, char *argv[])

{
    //TO-DO have to implement forbidding filename before options
    program_name = argv[0];

    parse_options(argc, argv);
    

    // cout << "file name index" << file_name_index << endl; //amount of args and filename
    // cout << "arg amount" << argc << endl;

    // for (int i = 0; i < argc; i++)
    // {
    //     cout << argv[i] << endl;
    // }

    run(argc, argv);

    return 0;
}
