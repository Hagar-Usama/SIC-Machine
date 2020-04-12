// io/read-file-sum.cpp - Read integers from file and print sum.
// Fred Swartz 2003-08-20

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    
    //ifstream file;
    
    std::ifstream file("src.txt");
if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
        // using printf() in all tests for consistency
        cout<<line<<endl;
        //printf("%s", line.c_str());
    }
    file.close();
}

   
   
    return 0;
}
