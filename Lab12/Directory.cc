#include "Directory.h"
#include <iostream>

using namespace std;

// The directory iterator pre-fetches the name.  That is, readdir()
// is called when you first create the iterator, and upon ++.
//
// An end() iterator is designated by a null pointer for its DIR *.
// When readdir() fails, we set our pointer to null.

DirectoryIterator::DirectoryIterator(DIR *dp_arg, const std::string w) : dp(dp_arg), match_word_i(w) //Fix #3
{
    ++*this; // get that first entry 
    //
}

bool DirectoryIterator::wanted()

{
    if(match_word_i == "any"){                     //Fix #2 //Fix #3
    if (name == ".")  // Stupid entry for current directory?
        return false; // Nobody wants that.
    if (name == "..") // Stupid entry for parent directory?
        return false;
    return true;
    }
    else{
    
    if(name.find(match_word_i) != string::npos){
        return true;
    }
    else{
        return false;
    }
    }
}

DirectoryIterator &DirectoryIterator::operator++()
{ // pre-increment
    while (auto p = readdir(dp))
    {                     // Read a directory entry.
        name = p->d_name; // C-string ⇒ C++ string
        if (!wanted())
        {
            continue;
        }

        return *this; // Everything else, I like!
    }
    dp = nullptr; // readdir failed; don’t try again.
    return *this;
}

string DirectoryIterator::operator*() const
{
    return name; // Fetched in a previous ++.
}

bool DirectoryIterator::operator!=(const DirectoryIterator &rhs) const
{
    return dp != rhs.dp;
}

//////////////// Directory methods

Directory::Directory(const char dirname[], std::string match ) //Fix #3
{
    match_word = match;

    if (opendir(dirname) == nullptr)
    {
        throw runtime_error("failed to read the directory name."); //Fix #1
    }
    else
    {
        dp = opendir(dirname);
    }

    if (opendir(dirname) == nullptr)
    {
        throw runtime_error("failed to read the directory name."); //Fix #1
    }
    else
    {
        dp = opendir(dirname);
    }
    
}

Directory::~Directory()
{
    if (dp)           // Only if opendir() succeeded:
        closedir(dp); //   should we close it.
}

Directory::iterator Directory::begin() const
{

    return iterator(dp, match_word); //Fix #3
}

Directory::iterator Directory::end() const
{
    return iterator();
}
