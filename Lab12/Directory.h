#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

#include <dirent.h>
#include <string>

// Normally, I’d have DirectoryIterator be a nested class, Directory::iterator,
// to avoid namespace pollution.  However, this is easier to read.

class DirectoryIterator {
  public:
    DirectoryIterator() = default;
    
    DirectoryIterator(DIR *, const std::string w);
    DirectoryIterator &operator++();
    std::string operator*() const;
    bool operator!=(const DirectoryIterator &) const;
    
    bool wanted(); //Fix #2
  private:
    DIR *dp = nullptr;
    std::string name;
  public: 
    std::string match_word_i;
    

};

class Directory {
  public:
    typedef DirectoryIterator iterator;
    Directory() = delete;		// not really necessary
    Directory(const char dirname[], std::string match = "any");
    
    ~Directory();
    iterator begin() const;
    iterator end() const;
    std::string match_word;
  private:
    DIR *dp;				// null if open failed
};

#endif /* DIRECTORY_H_INCLUDED */
