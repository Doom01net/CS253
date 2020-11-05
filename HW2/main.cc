#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string>

using namespace std;
string program_name;

void debug(const string &s){ cout << "DEBUG: " <<  s << endl;}

ostream& operator<<(ostream& os, const vector<vector<char>>& vec)
{   
    for(vector<char> v: vec){
        for(char c: v)
            os << c << "";
        os << endl;
    }
    return os;
}

void fill_from_file( string f,  vector<vector<char>> &v)
{
    ifstream file(f);

    if (!(file.good()))
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

    for (string line; getline(in, line);)
    {
        vector<char> row;
        for (char c : line)
            row.push_back(c);
        v.push_back(row);
    }

}

void error_check_matrix(vector<vector<char>> &v)
{   

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
        if (row_size != row.size()){
            cerr << "All rows must be same length. Program " << program_name << endl;
        exit(1);
        }
    }
}
int get_n_amount(const string &s){
    int ret = 0;
    for (char c: s){
        if(c == 'O')
            ret++;
    }
    return ret;
}
bool alive(const char &c)
{
    if (c == 'O')
        return true;
    if (c == '.')
        return false;
    else
    {
        cerr << "Found a char " << c << "That doesn't match in program " << program_name << endl;
        exit(1);
    }
}

bool dead(const char &c)
{
    return !(alive(c));
}

void update_generation(vector<vector<char>> &in,  vector<vector<char>> &out)
{
   // debug("Begin DEBUG of Update generation");
    int r =  (in.size());
    int c = (in[0].size());
   // debug("Matrix sized " + to_string(r) + ' ' + to_string(c));
    
    for (int i = 0; i < r; i++)
    {
        
        for (int j = 0; j < c; j++)
        {
          
            char up_left = in[(i-1+r)%r][ (j-1+c)%c]; // 
            char up = in[(i-1+r)%r][j];
            char up_right = in[(i-1+r)%r][ (j+1+c)%c];
            char left = in[i][(j-1+c)%c];
            char right = in[i][(j+1+c)%c];
            char d_left = in[(i+1+r)%r][(j-1+c)%c];
            char down = in[(i+1+r)%r][j];
            char d_right = in [(i+1+r)%r][ (j+1+c)%c];
            
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
                if( (get_n_amount(sum) == 2) || (get_n_amount(sum) == 3)) {
                    out[i][j]='O';
                } else{
                    out[i][j]='.';
                }
            }
            // If a cell is dead, then it becomes alive for the next generation iff it has exactly three neighbors.
            else if(dead(in[i][j]))
            {
                if( (get_n_amount(sum) == 3) ) {
                    out[i][j]='O';
                }else {
                    out[i][j]='.';
                }
            }
        }
    }
}




int main( int argc,  char *argv[])

{

    program_name = argv[0];

    vector<vector<char>> matrix_in;
    vector<vector<char>> matrix_out;


    
    if (argc == 2)
    {

        fill_from_file(argv[1], matrix_in);
        matrix_out = matrix_in;
    }

    if (argc == 1)
    {

        fill_from_cin(cin, matrix_in);
        matrix_out = matrix_in;
    }

    error_check_matrix(matrix_in);


    update_generation(matrix_in, matrix_out);

      


    
    cout << matrix_out;
      return 0;
}
