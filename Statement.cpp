

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Statement{
	
	public :
	 string line;
	 string label;
	 string operation;
	 string operand;
	 string operand1;
	 string operand2;
	 int indexed;
	 string comment;
	 int storage;
	 int store_op;
	 bool right;
	 int formattype;
	
	Statement(){};
	 
 int check_indexed();
 //line
 int check_statment();	 
 //line
 int check_comment();
 //line
 int check_format4_lab();
 //line
 int check_format4_unlab();	 
 //line
 int check_format3_lab();
 //line
 int check_format3_unlab();	 
 //line
 int check_format2_lab();
 //line
 int check_format2_unlab();
 //line
 int check_dir_lab();
 //line
 int check_dir_unlab();
 
 void divide_operands();
 //line
 void partition_dir(bool label);
 //line
 //void parition_all(bool label , string exp );
 //line
 void get_partitioned();
 //line
 void partition_format4(bool label);
 
 
 int get_matched(string s , regex reg , string &mat);
 void trim(string &str);
 string extract(string &exp , string re);
 void ltrim(string &exp);
 void rtrim(string &exp);
	};




int Statement:: check_indexed(){
		string reg = "((\\w+)|\\d|\\*)\\s*((\\+|-)\\s*\\d)?\\s*(,\\s*x)";
		regex re(reg);
 		if(regex_match(this->operand,re)){
			//cout<<"indexed"<<endl;
			this->indexed = true;
			return 1;
		}	
			this->indexed = false;
 			return 0;
		 
		 }
		 
		 
int Statement::check_statment(){
		 /**
	 * return -1 if error
	 * return  0 if comment
	 * return 10 if dir 	 unlabeled
	 * return 11 if dir 	 labeled
	 * return 20 if format 2 unlabeled
	 * return 21 if format 2 labeled
	 * return 30 if format 3 unlabeled
	 * return 31 if format 3 labeled
	 * return 40 if format 4 unlabeled
	 * return 41 if format 4 labeled
	 * 
	 * */
	if(check_comment()) return 0;
	if(check_dir_unlab())return 10;
	if(check_dir_lab())return 11;
	if(check_format2_unlab())return 20;
	if(check_format2_lab())return 21;
	if(check_format3_unlab())return 30;
	if(check_format3_lab())return 31;
	if(check_format4_unlab())return 40;
	if(check_format4_lab())return 41;
	return -1;	 
		 }
		 	 
	 
int Statement::check_comment(){
		 string reg = "\\s*\\..*"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			return 1;		
			}
 	
		return 0;
 		 
		 }
	
int Statement::check_format4_lab(){
		 string input;
		string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)\\+\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
		regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid format 4"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
		 
		 };
	
int Statement::check_format4_unlab(){
		 string input;
	 string reg = "\\s*\\+\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid format 4"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
		 
		 
		 }	 
	

		
		int Statement::check_format3_lab(){
	 string input;
	 string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid format 3"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}

		
		
		}

int Statement::check_format3_unlab(){
		string input;
	 string reg = "\\s*\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid format 3"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
		
		
		}
		
			 
int Statement::check_format2_lab(){
		 
		 string input;
	 string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid format 2"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}

		 
		 }
	 
	 
int Statement::check_format2_unlab(){
		
	 string input;
	 string reg = "\\s*((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid format 2"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
		
		
		}
		
	 
int Statement::check_dir_lab(){
		string input;
	 string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s+((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(equ)\\s+\\b([a-z]){1}\\w{1,7}(\\+\\d{1,4})?))\\s*(;.*)?";
	 regex re(reg);
 		if(regex_match(this->line,re)){
			//cout<<"Valid"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}

		
		}

int Statement::check_dir_unlab(){
	string input;
	 string reg = "\\s*((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(end)(\\s+\\b(){1}\\w{1,7})?)|(\\b(org)(\\s+\\b(){1}\\w{1,7}))|(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*)))\\s*(;.*)?";
	 
	 regex re(reg);
		
 		if(regex_match(this->line,re)){
			//cout<<"Valid"<<endl;
			return 1;		
			}
 		else
 		{
 			//cout<<"Invalid input"<<endl;
 			return 0;
 		} 
		 
		 
		}
	 
	 //
	 void Statement::divide_operands(){
		 
		 
		 
		 
		 }
	 
	 
	 //void partition_dir(bool label , string exp , statement &st );
	 void Statement::partition_dir(bool label){
		 string matched;
	regex reg("^\\s*[\\w]+\\s*");
	
	//I think this makes them point to the same value we need clone
	string exp = this->line;
	
	//extracting comment
	matched = extract(exp,";.*");
	this->comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
	//extract(exp,"^\\s*");
	//matched.erase();
	
	if(label){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			rtrim(matched);
			this->label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //operation
		    rtrim(matched);
		    this->operation = matched;
		    
		    matched.erase(); 
		    rtrim(exp);
		    ltrim(exp);
		    this->operand = exp;
		 
		 }
	 
	 
	 
	 
	 void Statement::get_partitioned(){
		 bool label = true;
		
		string exp = this->line;
		
		int format = check_statment();
		if(format%2 == 0) label = false;
		this->formattype = format;
		switch(format){
			
			case 0:
			this->comment = exp;
			break;
			case 10:
			case 11:
			case 20:
			case 21:
			case 30:
			case 31:
			
			partition_dir(label);
			
			break;
			case 40:
			case 41:
			partition_format4(label);
			break;
			
			default:
			
			break;
			
			}
		
		
		 
		 
		 }
	 
	 //void partition_format4(bool label , string exp , statement &st);
	 void Statement::partition_format4(bool label){
		 string matched;
		 string exp = this->line;
	//extracting comment
	matched = extract(exp,";.*");
	this->comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
		
	if(label){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			rtrim(matched);
			this->label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*\\+\\w+\\s*"); //operation
		    rtrim(matched);
		    
		    this->operation = matched;
		    
		    matched.erase(); 
		    rtrim(exp);
		    ltrim(exp);
		    this->operand = exp;
			this->formattype = 4;
		 
		 }
	 
	 int Statement::get_matched(string s , regex reg , string &mat){
		 smatch match;
	if(regex_search(s,match,reg) == true){
		mat = match.str(0);
		return 1;
		}
	return 0;
	
		 }
		 
		 
	 void Statement::trim(string &str){
		 
		 if(str.size()){
			regex ret(".[^\\s]+");
		get_matched(str,ret,str);
			}

		 
		 }
	
	 string Statement::extract(string &exp , string re){
		 
		 regex reg(re);
		string matched;
		get_matched(exp, reg , matched);
		//trim(matched);
		exp = regex_replace(exp,reg, "");
		//cout<<"<"<<exp<<"<"<<endl;
		return matched;
		 }
	
	 void Statement::ltrim(string &exp){
		 regex reg("^\\s*");
		string mat;
		get_matched(exp , reg,mat);
		exp = exp = regex_replace(exp,reg,"");
	 }
	 
	 
	 void Statement::rtrim(string &exp){
		 regex reg("(\\s*)$");
	string mat;
	get_matched(exp , reg,mat);
	exp = exp = regex_replace(exp,reg,"");
		 
		 }




int main(){
	Statement st;
	//st.check_statment("start    1000   ;commenty");
	st.line = "start	1000	;ddd";
	st.get_partitioned();
	
	cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
			cout<<"<"<<st.label<<">"<<endl;
			cout<<"<"<<st.operation<<">"<<endl;
			cout<<"<"<<st.operand<<">"<<endl;
			cout<<"<"<<st.comment<<">"<<endl;
	cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
	
	
	return 0;
	
	}

