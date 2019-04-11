#include <iostream>
#include <queue>
#include <map>
//#include <bits/stsc++.h>
using namespace std;

//std::vector<T>
//std::queue<T>
//std::dequeue<T>
//std::set<T>
//std::map<T>
//std::multiset<T>
//std::multimap<T>

int main(){

map<string , float> s;

string x = "djjg";

cout<<x<<endl;

s["a"] = 2000;
s["dd"] = 3000;
s["ed"] = 4000;

cout<<s["a"]<<endl;

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
