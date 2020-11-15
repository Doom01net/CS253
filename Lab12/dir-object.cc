#include <iostream>
#include "Directory.h"

using namespace std;

int main() {
    Directory dir(".", "Ma");
    
    for (auto name : dir)
	cout << "Filename: " << name << '\n';
}
