#include "Board.h"
#include <fstream>
using namespace std;
namespace game_l{
    char dead = '.';
    char alive = 'O';
}
void error_check_matrix(vector<vector<char>> &v)
{
    

    if (v.size() < 2)
    {
        throw runtime_error("There must be at least 2 lines. Program " );
        
    }

    for (vector<char> c : v)
        if (c.size() < 2)
        {
            throw runtime_error("There must be at least 2 cells. Program " );
        }

    size_t row_size = v[0].size();
    for (vector<char> row : v)
    {
        if (row_size != row.size())
        {
            throw runtime_error("All rows must be the same length" );
        }
    }
}

Board& Board::operator++(){
    vector<vector<char>> phonyIn;
    char phony_dead = 'D';
    char phony_alive = 'A';

    for(int i = 0; i < static_cast<int>(in.size()); i++){
        for(int j = 0; j < static_cast<int>(in[i].size()); j++){
            if(in[i][j] == game_l::dead)
                phonyIn[i][j]= 'D';
            if(in[i][j] == game_l::alive)
                phonyIn[i][j] = 'A';
        }
    }
    for(int i = 0; i < static_cast<int>(phonyIn.size()); i++){
        for(int j = 0; j < static_cast<int>(phonyIn[i].size()); j++){
            //TO-DO set neigbors
            if(r.eval()){
                //SETALIVE
            }else {//SETDEAD}
        }
    }
    return *this;
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
    r = Rule();
}

