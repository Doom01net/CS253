#include "Board.h"
#include <fstream>
#include <string>
using namespace std;
// namespace game_l
// {
//     char dead = '.';
//     char alive = 'O';
// } // namespace game_l

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

std::ostream &operator<<(std::ostream &os, const Board &b)
{

    for (vector<char> row : b.in)
    {
        for (char c : row)
        {
            os << c << "";
        }
        os << "\n";
    }

    return os;
}

void error_check_matrix(vector<vector<char>> &v)
{

    if (v.size() < 2)
    {
        throw runtime_error("There must be at least 2 lines. Program ");
    }

    for (vector<char> c : v)
        if (c.size() < 2)
        {
            throw runtime_error("There must be at least 2 cells. Program ");
        }

    size_t row_size = v[0].size();
    for (vector<char> row : v)
    {
        if (row_size != row.size())
        {
            throw runtime_error("All rows must be the same length");
        }
    }
}

Board &Board::operator++()
{
    vector<vector<char>> phonyIn;
    char phony_dead = 'D';
    char phony_alive = 'A';

    phonyIn = in;

    for (int i = 0; i < static_cast<int>(in.size()); i++)
    {
        for (int j = 0; j < static_cast<int>(in[i].size()); j++)
        {
            if (in[i][j] == this_dead_char)
            {
                phonyIn[i][j] = phony_dead;
            }
            else if (in[i][j] == this_live_char)
            {
                phonyIn[i][j] = phony_alive;
            }
            else
            {

                string error = "Unexpected char in the matrix that is in the file ";
                error.push_back(in[i][j]);
                error.push_back('<');
                throw runtime_error(error);
            }
        }
    }

    //cout << "Phony In Looks like this: \n" << phonyIn << endl;
    out = in;
    int r = (in.size());
    int c = (in[0].size());
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            //TO-DO set neigbors

            char nw = phonyIn[(i - 1 + r) % r][(j - 1 + c) % c]; //
            char n = phonyIn[(i - 1 + r) % r][j];
            char ne = phonyIn[(i - 1 + r) % r][(j + 1 + c) % c];
            char w = phonyIn[i][(j - 1 + c) % c];
            char e = phonyIn[i][(j + 1 + c) % c];
            char sw = phonyIn[(i + 1 + r) % r][(j - 1 + c) % c];
            char s = phonyIn[(i + 1 + r) % r][j];
            char se = phonyIn[(i + 1 + r) % r][(j + 1 + c) % c];
            char curr = phonyIn[i][j];

            //(char nw, char n,char ne, char w,char me, char e,char sw, char s,char se){
            if (my_rule.eval(nw, n, ne, w, curr, e, sw, s, se))
            {
                out[i][j] = this_live_char;
            }
            else
            {
                out[i][j] = this_dead_char;
            }
        }
    }

    in = out;
    return *this;
}

Board::Board(string filename, Rule rule)
{
    ifstream file(filename);

    if (file.fail())
    {
        throw runtime_error("File doesn't exist, Board.cc"s + filename);
    }
    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        in.push_back(row);
    }

    error_check_matrix(in);
    //cout << "Matrix no errors\n";
    //cout << in << endl;
    my_rule = rule;
}

Board::Board(std::string filename, char live, char dead)
{
    ifstream file(filename);

    if (file.fail())
    {
        throw runtime_error("File doesn't exist, Board.cc"s + filename);
    }
    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        in.push_back(row);
    }

    error_check_matrix(in);
    //cout << "Matrix no errors\n";
    //cout << in << endl;
    my_rule = Rule();
    this_dead_char = dead;
    this_live_char = live;
}

Board::Board(string filename, char live, char dead, Rule rule)
{
    ifstream file(filename);

    if (file.fail())
    {
        throw runtime_error("File doesn't exist, Board.cc"s + filename);
    }
    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        in.push_back(row);
    }

    error_check_matrix(in);
    //cout << "Matrix no errors\n";
    //cout << in << endl;
    my_rule = rule;
    this_dead_char = dead;
    this_live_char = live;
}

Board::Board(std::string filename, Rule rule, char live, char dead)
{

    fstream file(filename);

    if (file.fail())
    {
        throw runtime_error("File doesn't exist, Board.cc"s + filename);
    }
    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        in.push_back(row);
    }

    error_check_matrix(in);
    //cout << "Matrix no errors\n";
    //cout << in << endl;
    my_rule = rule;
    this_dead_char = dead;
    this_live_char = live;
}

Board::Board(string filename)
{
    ifstream file(filename);

    if (file.fail())
    {
        throw runtime_error("File doesn't exist, Board.cc"s + filename);
    }
    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        in.push_back(row);
    }

    error_check_matrix(in);
    //cout << "Matrix no errors\n";
    //cout << in << endl;
    my_rule = Rule();
}
