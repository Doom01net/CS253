#include "Lexan.h"


using namespace std;


string analize_char(char c)
{
    
  if (isalpha(c))
    return "alpha";

  if (isdigit(c))
    return "digit";

  int is_token = 0;
  ///u8"\u0444
  wchar_t symbols[] = {'+', '-', '=', '/', '!', '<', '>', '*'};

  for (int i = 0; i < 8; i++)
  {
    if (symbols[i] == c)
    {
      is_token = 1;
      break;
    }
  }

  if (is_token)
    return "token_start";

  if (isspace(c))
    return "space";

  return "none";
}

void rm_chars(int index, string &s)
{
  s = s.substr(index, s.size() - (index));
}

// void add_to_output(string &v, string &l, int amount)
// {
//   for (int i = 0; i < amount; i++)
//   {
//     o += l[i];
//   }
//   o += "\n";
// }

bool is_space_line(string s)
{

  size_t count = 0;
  for (size_t i = 0; i < s.size(); i++)
  {
    if (s[i] == ' ')
      count++;
  }
  if (count == s.size())
  {

    return true;
  }
  return false;
}

void add_to_output(vector<string> &v, string &l, int amount)
{

    string o = "";
    for (int i = 0; i < amount; i++)
    {
        o += l[i];
    }
   // cout << "adding to v: " << o << endl;
    v.push_back(o);
}

void trim_comment(string &s)
{

  size_t pos = s.find('#');

  if (pos != std::string::npos)
  {
    s.resize(pos);
  }
  for (size_t i = 0; i < s.size(); i++)
  {

    if (s[i] == '#')
    {
      s.substr(0, i - 1);
    }
  }
}

void lower_string(string &s)
{

  for (size_t c = 0; c < s.size(); c++)
  {
    if (isalpha(s[c]))
    {
      s[c] = tolower(s[c]);
    }
  }
}

void Lexan::line(string &in){
    istringstream iss(in);
    for (string line; getline(iss, line);)
  {
    trim_comment(line);
    if (is_space_line(line))
    {
      continue;
    }
    lower_string(line);

    //cout <<"Line: " << line << endl;

    while (line[0] != '\0')
    { //

      string char_type = analize_char(line[0]);

      if (char_type == "space")
      {
        rm_chars(1, line);
        continue;
      }
    
    
    if(line.substr(0,3) == "≤" ||line.substr(0,3) == "≠" ||line.substr(0,3) == "≥"){

        if (      ((analize_char(line[3]) == "alpha") ||
                  ((analize_char(line[3]) == "digit")) || ((analize_char(line[3]) == "space")) || 
                  ((line[3] == '\n')) || ((line[3] == '\0'))) ) {
       // cout << "found it!" << endl;
        add_to_output(tokens, line, 3);
        rm_chars(3, line);
        
        continue;
                  }else{
                      throw runtime_error("Bad token combination");
                  }
      }
      if (char_type == "none")
      {
        throw runtime_error("invalid token starting with \"" + line +"\"");
        
      }
      
      if (char_type == "alpha")
      {

        //int crunch_alpha(line[0], out,)

        if (line[0] == 'p')
        {

          string tok = "";
          if ((tok + line[0] + line[1] + line[2] + line[3] + line[4]) == "print")
          {

            add_to_output(tokens, line, 5);
            rm_chars(5, line);
          }
          else
          {
            add_to_output(tokens, line, 1);
            rm_chars(1, line);
          }
        }
        else if (line[0] == 'f')
        {
          string tok = "";
          if ((tok + line[0] + line[1]) == "fi")
          {
            add_to_output(tokens, line, 2);
            rm_chars(2, line);
          }
          else
          {
            add_to_output(tokens, line, 1);
            rm_chars(1, line);
          }
        }
        else if (line[0] == 'i')
        {
          string tok = "";
          if ((tok + line[0] + line[1]) == "if")
          {
            add_to_output(tokens, line, 2);
            rm_chars(2, line);
          }
          else
          {
            add_to_output(tokens, line, 1);
            rm_chars(1, line);
          }
        }
        else if (line[0] == 'r')
        {
          string tok = "";
          if ((tok + line[0] + line[1] + line[2] + line[3] + line[4] + line[5]) == "return")
          {
            add_to_output(tokens, line, 6);
            rm_chars(6, line);
          }
          else
          {
            add_to_output(tokens, line, 1);
            rm_chars(1, line);
          }
        }

        else
        {
          add_to_output(tokens, line, 1);
          rm_chars(1, line);
        }
      }

      else if (char_type == "digit")
      {

        int counter = 0;
        for (size_t i = 0; i < line.size(); i++)
        {
          if (isdigit(line[i]))
          {
            counter++;
          }
          else
          {
            break;
          }
        } //15
        if(counter > 15 ){
          cerr << "number is more than 15 " << endl;
          exit(1); 
        }
        add_to_output(tokens, line, counter );
        rm_chars(counter, line);
      }
      else if (char_type == "token_start")
      {
        string tok = "";
        if((tok + line[0] + line[1]) == "=="){
          
         throw runtime_error("Bad token ==");
           

        }
        //cout << "The token is |" << tok << line[0] << line[1] <<"|" << endl;
        if (line[0] == '=')
        {
          add_to_output(tokens, line, 1);
          rm_chars(1, line);
        }
        


       else if ((((tok + line[0] + line[1]) == "+=") || ((tok + line[0] + line[1]) == "-=") ||
                  ((tok + line[0] + line[1]) == "*=") || ((tok + line[0] + line[1]) == "/=")) &&
                  ((analize_char(line[2]) == "alpha") ||
                  ((analize_char(line[2]) == "digit")) || ((analize_char(line[2]) == "space")) || 
                  ((line[2] == '\n')) || ((line[2] == '\0'))))
        {
          add_to_output(tokens, line, 2);
          rm_chars(2, line);
        }
        else
        {
          throw runtime_error("Reached the end and didn't resolve token.");
          
          ;
        }

        //break;
      }
    }
    string nl = "nwl";
    add_to_output(tokens, nl, 3);
    
  }

}
  
size_t Lexan::size()const{
    return tokens.size();
}
vector<string> Lexan::getTokens()const{
    return tokens;
}
bool Lexan::empty()const{

    if(tokens.size() == 0)
        return true;
    return false;
}
ostream &operator<<(ostream &os, const Lexan &lex){

    for(size_t a = 0; a < lex.getTokens().size()-1; a++ )
        os << lex.getTokens().at(a) << ",";
        

    
    os << lex.getTokens().at(lex.getTokens().size() -1);
    

    return os;
}
void Lexan::clear(){
    tokens.clear();
}
string Lexan::operator[](size_t index)const{
    if(index >= tokens.size())
        throw  out_of_range("Out of range");
    return tokens.at(index);

}
Lexan::~Lexan(){
    clear();
} 

Lexan::Lexan(const Lexan &other){
    tokens = other.getTokens();
}
Lexan::Lexan(string s){
    //Lexan::tokens.push_back("hasdasdasdasdasdasdello");
    //cout << s << endl;
    line(s);
}