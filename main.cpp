#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#define MAX 100
using namespace std;

// Global variables 
vector<string> lines(0);
string arr[100];
int index = 0;

string split(string &line ,int length);
void read_file(string filename);


#include "Assembler.cpp"

int main(){
	read_file("src.txt");
	cout<<lines.size();
	
	Assembler ass;
return 0;	
}

////////////////////////////////////////////////////////////////////////	
string split(string &line ,int length){
	
	string token = line.substr(0,length);
	line = line.substr(length , line.capacity());
	
	
	return token;	
}

////////////////////////////////////////////////////////////////////////
void read_file(string filename){
	
	std::ifstream file(filename);
	if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
        lines.push_back(line);
        //lines[index] = line;
        arr[index++] = line;
        cout<<"ananaa\n";    
    }
    
    file.close();
	
	}
}

////////////////////////////////////////////////////////////////////////
