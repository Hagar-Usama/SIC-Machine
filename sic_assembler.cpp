#include <iostream>
#include <queue>
#include <map>
#include <string>
//#include <bits/stsc++.h>
using namespace std;

//std::vector<T>
//std::queue<T>
//std::dequeue<T>
//std::set<T>
//std::map<T>
//std::multiset<T>
//std::multimap<T>

string sub_line(string line ,int length);
string split(string &line ,int length);
void edit(string& s) {
    s[1] = 'A';
}


int main(){

//////////////////// mapping ////////////////
map<string , float> ss;

ss["a"] = 2000;
ss["dd"] = 3000;
ss["ed"] = 4000;

///////////////////////////////////////////////

/////////////////// mapping and pair //////////
pair <string ,int> xz;
xz.first = "aaa";
xz.second = 5;
ss.insert(xz);
cout<<ss["aaa"]<<endl;
////////////////////////////////////////////////

string str("0123456789asdf");
string str2("ss");
str2 = split(str, 5);
cout<<str2<<endl;
cout<<str<<endl;

/*
for (unsigned i = 0; i < str.length(); i += 4) {
    cout << str.substr(i, 4) << endl;
}
*/

/*

std::string s = "scott>=tiger";
    std::string delim = ">=";

    auto start = 0U;
    auto end = s.find(delim);
    while (end != std::string::npos)
    {
        std::cout << s.substr(start, end - start) << std::endl;
        start = end + delim.length();
        end = s.find(delim, start);
    }

    std::cout << s.substr(start, end);
*/

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

string sub_line(string line ,int length){
	
	cout <<line.substr(0,length)<<endl;
	
	line = line.substr(length , line.capacity());
	return line;	
}
	
	
	
string split(string &line ,int length){
	
	string token = line.substr(0,length);
	line = line.substr(length , line.capacity());
	cout <<line.substr(0,length)<<endl;
	
	return token;	
}
