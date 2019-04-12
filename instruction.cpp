#include <iostream>
using namespace std;


	
string split(string &line ,int length){
	
	string token = line.substr(0,length);
	line = line.substr(length , line.capacity());
	cout <<line.substr(0,length)<<endl;
	
	return token;	
}


class instruction{
	public:
		string label;
		string mnemonic;
		string operand;
		string comment;
		instruction();
	    void set_label(string l);
	    void set_mnemonic(string m);
	    void set_operand(string o);
	    void set_comment(string c);
	};


instruction::instruction(){}
void instruction::set_label(string l){
	label = l;
	}

int main(){
instruction obj;
string rr("ddd");
obj.set_label(rr);

string line("prog     start   0100");
string token = split(line , 9);
obj.label = token;
token = split(line , 8);
obj.mnemonic = token;
//token = split(line , 8);
obj.mnemonic = line;

cout<<"****"<<endl;
cout<<obj.label<<endl;
cout<<obj.mnemonic<<endl;
//cout<<obj.operand<<endl;
//cout<<obj.comment<<endl;
cout<<"****"<<endl;

return 0;
}
