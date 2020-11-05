#include <iostream>
#include <string>

using namespace std;
string program_name;

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

string analize_char(char c)
{
  if (isalpha(c))
    return "alpha";

  if (isdigit(c))
    return "digit";

  int is_token = 0;
  char symbols[] = {'+', '-', '=', '/', '!', '<', '>', '*'};

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

void add_to_output(string &o, string &l, int amount)
{
  for (int i = 0; i < amount; i++)
  {
    o += l[i];
  }
  o += "\n";
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

void line(istream &in)
{
  string out = "";
  for (string line; getline(in, line);)
  {

    trim_comment(line);

    if (is_space_line(line))
    {
      continue;
    }

    lower_string(line);
    //DEBUGcout << "Line " << line << "ENDL. Size is: "<< line.size() << endl; //Our Line

    while (line[0] != '\0')
    { //

      string char_type = analize_char(line[0]);

      if (char_type == "space")
      {
        rm_chars(1, line);
        continue;
      }

      if (char_type == "none")
      {
        cerr << "Program " << program_name << " had a bad token '" << line[0] << "' on line\n"
             << line << endl;
        exit(1);
      }
      if (char_type == "alpha")
      {

        //int crunch_alpha(line[0], out,)

        if (line[0] == 'p')
        {

          string tok = "";
          if ((tok + line[0] + line[1] + line[2] + line[3] + line[4]) == "print")
          {

            add_to_output(out, line, 5);
            rm_chars(5, line);
          }
          else
          {
            add_to_output(out, line, 1);
            rm_chars(1, line);
          }
        }
        else if (line[0] == 'f')
        {
          string tok = "";
          if ((tok + line[0] + line[1]) == "fi")
          {
            add_to_output(out, line, 2);
            rm_chars(2, line);
          }
          else
          {
            add_to_output(out, line, 1);
            rm_chars(1, line);
          }
        }
        else if (line[0] == 'i')
        {
          string tok = "";
          if ((tok + line[0] + line[1]) == "if")
          {
            add_to_output(out, line, 2);
            rm_chars(2, line);
          }
          else
          {
            add_to_output(out, line, 1);
            rm_chars(1, line);
          }
        }
        else if (line[0] == 'r')
        {
          string tok = "";
          if ((tok + line[0] + line[1] + line[2] + line[3] + line[4] + line[5]) == "return")
          {
            add_to_output(out, line, 6);
            rm_chars(6, line);
          }
          else
          {
            add_to_output(out, line, 1);
            rm_chars(1, line);
          }
        }

        else
        {
          add_to_output(out, line, 1);
          rm_chars(1, line);
        }
      }

      else if (char_type == "digit")
      {

        int counter = 1;
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
        }
        add_to_output(out, line, counter - 1);
        rm_chars(counter - 1, line);
      }
      else if (char_type == "token_start")
      {
        string tok = "";
        if((tok + line[0] + line[1]) == "=="){
          
         cerr << "Program " << program_name << " had a bad token '" << line[0] << line[1] << "' on line\n"
               << line << endl;
          exit(1); 

        }
        //cout << "The token is |" << tok << line[0] << line[1] <<"|" << endl;
        if (line[0] == '=')
        {
          add_to_output(out, line, 1);
          rm_chars(1, line);
        }
        


        else if ((((tok + line[0] + line[1]) == "+=") || ((tok + line[0] + line[1]) == "-=") ||
                  ((tok + line[0] + line[1]) == "*=") || ((tok + line[0] + line[1]) == "/=") ||
                  ((tok + line[0] + line[1]) == "!=") || ((tok + line[0] + line[1]) == "<=") ||
                  ((tok + line[0] + line[1]) == ">=")) &&
                  ((analize_char(line[2]) == "alpha") ||
                  ((analize_char(line[2]) == "digit")) || ((analize_char(line[2]) == "space")) || 
                  ((line[2] == '\n')) || ((line[2] == '\0'))))
        {
          add_to_output(out, line, 2);
          rm_chars(2, line);
        }
        else
        {
          cerr << "Program " << program_name << " had a bad token '" << line[0] << "' on line\n"
               << line << endl;
          exit(1);
          ;
        }

        //break;
      }
    }
  }
  out = out.substr(0, out.size() - 1);
  cout << out << endl;
}

int main(int, char *argv[])
{ // int cuz I don't use argc

  program_name = argv[0];

  //

  line(cin);
  return 0;
}
