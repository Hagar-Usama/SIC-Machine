#include <iostream>
#include <queue>
#include <map>
#include <string>
//#include <iomanip>
#include <fstream>
//#include <sstream>

//#include <bits/stsc++.h>
using namespace std;

//std::vector<T>
//std::queue<T>
//std::dequeue<T>
//std::set<T>
//std::map<T>
//std::multiset<T>
//std::multimap<T>

string arr[100];
int index = 0;


string split(string &line ,int length);
void read_file(string filename);


int main(){

//////////////////// mapping ////////////////
map<string , float> ss;

ss["a"] = 2000;
ss["dd"] = 3000;
ss["ed"] = 4000;

///////////////////////////////////////////////
 read_file("src.txt");
 cout<<arr[2]<<endl;
string line = arr[1];
cout<<line<<endl;
string label = split(line , 8);
cout<<label<<endl;

string mnemonic = split(line , 9);
cout<<mnemonic<<endl;

string operand = split(line , 18);
cout<<operand<<endl;
cout<<line<<endl;
/////////////////// mapping and pair //////////
/*
pair <string ,int> xz;
xz.first = "aaa";
xz.second = 5;
ss.insert(xz);
cout<<ss["aaa"]<<endl;
*/
////////////////////////////////////////////////
/*
string str("0123456789asdf");
string str2("ss");
str2 = split(str, 5);
cout<<str2<<endl;
cout<<str<<endl;
*/
///////////////////////////////////////////////



/*
queue<int> myQ;
for(int i=0 ; i<10;i++){
	cout<<"enQ"<<endl;
	myQ.push(i);
	}
	
	
int k=0;	
for(int i=0 ; i<10;i++){
	cout<<"deQ"<<endl;
	k = myQ.front();
	cout<<k<<endl;
	myQ.pop();


	}
*/
return 0;
}

	
string split(string &line ,int length){
	
	string token = line.substr(0,length);
	line = line.substr(length , line.capacity());
	//cout <<line.substr(0,length)<<endl;
	
	return token;	
}



void read_file(string filename){
	
	std::ifstream file(filename);
	if (file.is_open()) {
    std::string line;
    while (getline(file, line)) {
        //cout<<line<<endl;
        arr[index++] = line;    
    }
    
    file.close();
	
	}
}
