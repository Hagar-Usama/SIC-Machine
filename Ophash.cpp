#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Ophash{
	string operation;
	int op_num;
	int format;
	Ophash();
	};


Ophash::Ophash(){}

int main(){
vector< pair <int,int> > operation;
vector<string> statement;
operation.push_back(make_pair(2,2)); //RMO 
operation.push_back(make_pair(1,7)); //LDR
operation.push_back(make_pair(1,7)); //STR
operation.push_back(make_pair(1,7)); //LDCH
operation.push_back(make_pair(1,7)); //STCH
operation.push_back(make_pair(1,7)); //ADD
operation.push_back(make_pair(1,7)); //SUB
operation.push_back(make_pair(2,7)); //ADDR
operation.push_back(make_pair(2,2)); //SUBR
operation.push_back(make_pair(2,7)); //COMP
operation.push_back(make_pair(2,2)); //COMPR
operation.push_back(make_pair(1,7)); //J
operation.push_back(make_pair(1,7)); //JEQ
operation.push_back(make_pair(1,7)); //JLT
operation.push_back(make_pair(1,7)); //JGT
operation.push_back(make_pair(1,7)); //TIX
operation.push_back(make_pair(1,2)); //TIXR



operation.push_back(make_pair(0,2)); //start
operation.push_back(make_pair(0,0)); //end
operation.push_back(make_pair(0,2)); //byte*
operation.push_back(make_pair(0,2)); //word*
operation.push_back(make_pair(0,2)); //resw*
operation.push_back(make_pair(0,2)); //rsub*
operation.push_back(make_pair(0,1)); //equ
operation.push_back(make_pair(0,0)); //org
operation.push_back(make_pair(0,0)); //base

statement.push_back("rmo");
statement.push_back("ldr");
statement.push_back("str");
statement.push_back("ldch");
statement.push_back("stch");
statement.push_back("add");
statement.push_back("sub");
statement.push_back("addr");
statement.push_back("subr");
statement.push_back("comp");
statement.push_back("compr");
statement.push_back("j");
statement.push_back("jeq");
statement.push_back("jlt");
statement.push_back("jgt");
statement.push_back("tix");
statement.push_back("tixr");



statement.push_back("start");
statement.push_back("end");
statement.push_back("byte");
statement.push_back("word");
statement.push_back("resw");
statement.push_back("resb");
statement.push_back("equ");
statement.push_back("org");
statement.push_back("base");

map <string ,pair<int,int>> st_map;
for (int i=0 ; i<26 ; i++){
		st_map[statement[i]] = operation[i];
	}

map<string , pair<int,int>>::iterator p;
string s="star1t";
p = st_map.find(s);
if(p!= st_map.end()){
	cout<<p->second.second<<endl;
	}else{
		cout<<"Not found"<<endl;
		}

	
map<string , float> ss;

ss["a"] = 2000;
ss["dd"] = 3000;
ss["ed"] = 4000;
	
	
return 0;

	}