#include <iostream>
using namespace std;


	
string split(string &line ,int length){
	
	string token = line.substr(0,length);
	line = line.substr(length , line.capacity());
	//cout <<line.substr(0,length)<<endl;
	
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

string line("BGN     START    1000              .fcmnt");
//123456789012345678901234567890123456789

cout<<"<<<<<"<<endl;
string label = split(line , 8);
cout<<label<<endl;

string mnemonic = split(line , 9);
cout<<mnemonic<<endl;

string operand = split(line , 18);
cout<<operand<<endl;
cout<<line<<endl;


return 0;
}
