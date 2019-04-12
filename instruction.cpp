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
	    int classify(int len);
	    void display_parts();
	};


instruction::instruction(){}
void instruction::set_label(string l){
	label = l;

	}

void instruction::display_parts(){
	cout<<"<<Label>>\n";
	cout<<label<<endl;
	
	cout<<"<<Mnemonic>>\n";
	cout<<mnemonic<<endl;
	
	cout<<"<<Operand>>\n";
	cout<<operand<<endl;
	
	cout<<"<<Comment>>\n";
	cout<<comment<<endl;
	
	}
int instruction::classify(int len){
	if(len >10 && len <18) // 11:17  xxx  RSUB
		{  
			return 1;
		}else if (len > 19 && len <36) // 18:35  xxx ADD   5
		{
			return 2;

		}else if (len > 35 && len <67) //36 :66	 xxx  ADD  2    .comment	
		{
			return 3;			
		}else return 0;
	
	}
	
void instruction::check_comment(){
	if(line[0] == '.')
		commented = true;
		
	}

void instruction::check_error(){
	
	
	}


void instruction::partition(){
	check_error();
	check_comment();
	if (!commented){	
		string token = line;
		int len = token.capacity();
		operand.clear();
		comment.clear();
		switch(classify(len)){
			case 1:
		    label = split(token , 8);
			mnemonic = token;
			break;
			case 2:
			label = split(token , 8);
			mnemonic = split(token , 9);
			operand = token;
			break;
			case 3:
			label = split(token , 8);
			mnemonic = split(token , 9);
			operand = split(token , 18);
			comment = token;
            break;
            
            default:
            cout<<"invalid type"<<endl;
			}
			
	}
	

}
int main(){
instruction obj;
//           123456789012345678901234567890123456789
string line("BGN     START    1000              .FFF");
obj.line = line;

obj.partition();

cout<<"*******"<<endl;
obj.display_parts();
cout<<"*******"<<endl;

line = "BGN     START    1000";
obj.line = line;
obj.partition();
obj.display_parts();


line = "BGN     START";
obj.line = line;
obj.partition();
obj.display_parts();

cout<<obj.mnemonic.capacity()<<endl;
cout<<obj.mnemonic<<"ddd";
return 0;
}
