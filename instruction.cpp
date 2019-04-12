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
		string line;
		string label;
		string mnemonic;
		string operand;
		string comment;
		bool commented;
		instruction();
	    void set_label(string l);
	    void set_mnemonic(string m);
	    void set_operand(string o);
	    void set_comment(string c);
	    void partition();
	    void check_error();
	    void check_comment();
	};


instruction::instruction(){}
void instruction::set_label(string l){
	label = l;

	}

void instruction::check_comment(){
	if(line[0] == '.'){
		commented = true;
		}
		
	}

void instruction::check_error(){
	
	
	}


void instruction::partition(){
	check_error();
	check_comment();
	if (!commented){
		
		string token = line;
		int len = token.length();
		
		if(len >10 && len <18) // 11:17
		{  
		}else if (len > 19 && len <36) // 18:35
		{
				
				
		
		}else if (len > 35 && len <67) //36 :66		
		{
			
			label = split(token , 8);
			//label = "fff";
			//cout<<label<<endl;
			mnemonic = split(token , 9);
			//cout<<mnemonic<<endl;

			operand = split(token , 18);
			//cout<<operand<<endl;
			//cout<<line<<endl;
			
			comment = token;
            cout<<"bye"<<endl;
			}
	}
	
	cout<<"Hi";
}
int main(){
instruction obj;
//           123456789012345678901234567890123456789
string line("BGN     START    1000              .FFF");
obj.line = line;

obj.partition();

cout<<"*******"<<endl;
cout<<obj.line<<endl;
cout<<obj.label<<endl;
cout<<obj.mnemonic<<endl;
cout<<obj.operand<<endl;
cout<<obj.comment<<endl;
cout<<"*******"<<endl;
return 0;
}
