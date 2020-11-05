#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set> 
#include <iterator> 
using namespace std;
//23280674821737
int main()
{

    // vector<int> v = {};
    // int a;
    // cin >> a;
    // if (a == 0)
    // {

    //     return 1;
    // }
    // while (a != 0)
    // {
    //     v.push_back(a);
    //     cin >> a;
    // }

    // for (size_t i = 0; i < v.size(); i++)
    //     cout << v[i] << ' ';
    // cout << "\n";

    string chars = "";
    string line;
    ifstream f("/etc/resolv.conf");


    //I assume all characters don't count \n 
    if (f.is_open())
    {
        while (getline(f, line))
        {
            for (char c: line){

                chars.push_back(c);
            }
        }
        f.close();
    }
    else {
        cout << "error" << endl;
    }
   
    //cout << chars << endl;

    multiset<char> ms;
    for (char c : chars){

        ms.insert(c);
    }

    set<char> s;
    for (char c: ms) {

        s.insert(c);
    }

    cout << "chars size " <<  chars.size() << "\n";

    for(char c: chars){
        cout << c << " ";

    }
    cout << "\n";

    cout << "set size " <<  s.size() << "\n";

    for(char c: s){
        cout << c << " ";

    }
    cout << "\n";
    
    cout << "multiset size " <<  ms.size() << "\n";

    for(char c: ms){
        cout << c << " ";

    }
    cout << "\n";
    

    //QUESTION 7
    // String contains all chars in the file /etc/resolv.conf. So does the MultiSet, since it allows duplicated. Hence the size is the same
    // The set doesn't allow duplicated, so it only has the chars form the file /etc/resolv.conf, but if there are 18 A's, the set will only have one. As it doesn't allow dupes.
    return 0;

}