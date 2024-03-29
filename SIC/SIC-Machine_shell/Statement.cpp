
/**
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
**/



 void trim(string &str);
 string extract(string &exp , string re , string delim="");
 void ltrim(string &exp);
 void rtrim(string &exp);
 void trim_(string &s , string delim="");
 string split(string line ,int length,int start=0);
 int eval_exp(string exp);
 bool check_case_1(string exp);
 bool check_case_2(string exp);
 bool check_case_3(string exp);
 int check_exp_type(string exp); 
class Statement{
	
	public :
	 string line;
	 string label;
	 string operation;
	 string operand;
	 //string operand1;
	 string operand2;
	 int indexed;
	 string comment;
	 int storage;
	 int store_op;
	 bool labeled;
	 int formattype;
	 int error;
	Statement(){ error = -1;};
	 
 int check_indexed();
 int check_statement();	 
 int check_not_implemented();
 int check_comment();

 int check_format4_lab();
 int check_format4_unlab();	 
 int check_format3_lab();
 int check_format3_unlab();	 
 int check_format2_lab();
 int check_format2_unlab();
 int check_dir_lab();
 int check_dir_unlab();
 int check_dir_not(); 
 void divide_operands();
 void clear_statement();

 void partition_dir();

 void get_partitioned();

 void partition_format4();
 
 
 int get_matched(string s , regex reg , string &mat);
 
 void check_part();
/**
 void trim(string &str);
 string extract(string &exp , string re);
 void ltrim(string &exp);
 void rtrim(string &exp);
 void trim_(string &s , string delim="");
 **/
	};


void Statement::clear_statement(){
	line.erase();
	label.erase();
	operation.erase();
	operand.erase();
	//operand1.erase();
	operand2.erase();
	
	 indexed=-1;
	 comment.erase();
	 storage=-1;
	 store_op=-1;
	 labeled=false;
	 formattype=-1;
	 error=-1;
	
	
	}
void Statement::check_part(){
	
	if(check_statement() == 1){
		//if(!check_comment())
			get_partitioned();
		}
	
	}
	
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
		 
		 
int Statement::check_statement(){
		 /**
		  * modified : now label and format included in each check
	  
	 * */
	if(check_not_implemented()) return -1;
	if(check_comment()) return 1;
	
	if(check_dir_not()) return 1;
	if(check_dir_unlab())return 1;
	if(check_dir_lab())return 1;
	if(check_format2_unlab())return 1;
	if(check_format2_lab())return 1;
	if(check_format3_unlab())return 1;
	if(check_format3_lab())return 1;
	if(check_format4_unlab())return 1;
	if(check_format4_lab())return 1;
	
	return -1;	 
		 }
		 	 
int Statement::check_not_implemented(){
	
	//LTORG to be remove if to be used later
	string reg ="\\s*(.+\\s+)?\\b(jsub|nobase|extdef|extref|use|csect|ltorg|td|rsub)\\s*(\\s+.+)?";
	regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = false;
			this->formattype = -2;
			this->error = 0;
			//cout<<"this is not implemented"<<endl;
			
			return 1;		
			
			}
 	
		return 0;
 		 
	}
int Statement::check_comment(){
	string reg = "\\s*\\..*"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = false;
			this->formattype = 0;
			return 1;		
			}
 	
		return 0;
 		 
		 }
	
int Statement::check_format4_lab(){
		 string input;
		string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)\\+\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
		regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = true;
			this->formattype = 4;
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
			this->labeled = false;
			this->formattype = 4;
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
			this->labeled = true;
			this->formattype = 3;
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
			this->labeled = false;
			this->formattype = 3;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
		
		
		}
		
			 
int Statement::check_format2_lab(){
		 
		 string input;
		 //format 2 doesn't have prefix + but this just for check error 7
	 string reg = "\\s*\\+?((\\b([a-z]){1}\\w{0,7})\\s+)((\\b(rmo|addr|subr|compr)\\s+[a-z]\\s*,\\s*)|(\\b(tixr)\\s+))[a-z]\\s*(;.*)?"; 
	 //string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = true;
			this->formattype = 2;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}

		 
		 }
	 
	 
int Statement::check_format2_unlab(){
		
	 string input;
	 string reg = "\\s*\\+?((\\b(rmo|addr|subr|compr)\\s+[a-z]\\s*,\\s*)|(\\b(tixr)\\s+))[a-z]\\s*(;.*)?"; 
	 //string reg = "\\s*((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = false;
			this->formattype = 2;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
		
		
		}
		
int Statement::check_dir_not(){
		
	string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s+((\\b(end)(\\s+\\b(){1}\\w{1,7})?)|(\\b(org)(\\s+\\b(){1}\\w{1,7}))|(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*)))\\s*(;.*)?";
	 regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = true;
			this->formattype = 1; 
			return 1;		
			}
 		
	return 0;
 		
	}	 
int Statement::check_dir_lab(){
	 string input;
	 //"(\\b(equ)\\s+(\\b([a-z]){1}\\w{0,7}\\s*(\\+\\s*\\d{1,4})?)|\\d{1,4})"
	 string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s+((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-z0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(equ)\\s+((\\b([a-z]){1}\\w{0,7}\\s*((\\+|-|\\*|/)\\s*\\d{1,4})?)|\\d{1,4})))\\s*(;.*)?";
	 regex re(reg);
 		if(regex_match(this->line,re)){
			this->labeled = true;
			this->formattype = 1; 
			return 1;		
			}
 		else
 		{
 			return 0;
 		}

		
		}


int Statement::check_dir_unlab(){
	string input;
	
	 string reg = "\\s*((\\b(equ)\\s+((\\b([a-z]){1}\\w{0,7}\\s*((\\+|-|\\*|/)\\s*\\d{1,4})?)|\\d{1,4}))|(\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-z0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(end)(\\s+\\b(){1}\\w{1,7})?)|(\\b(org)(\\s+\\b(){1}\\w{1,7}))|(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*)))\\s*(;.*)?";
	 
	 regex re(reg);
		
 		if(regex_match(this->line,re)){
			this->labeled = false;
			this->formattype = 1;
			return 1;		
			}
 		else
 		{
 		
 			return 0;
 		} 
		 
		 
		}
	 
	 //
	 void Statement::divide_operands(){
		 
		 string matched;
		 this->operand2 = extract(this->operand,"^,\\w");
		 
		 
		 }
	 
	 
	 void Statement::partition_dir(){
		 string matched;
		 regex reg("^\\s*[\\w]+\\s*");
	
		string exp = this->line;
	
	//extracting comment
	matched = extract(exp,";.*");
	this->comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
	
	if(this->labeled){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			trim_(matched);
			
			//rtrim(matched);
			this->label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*\\+?[\\w]+\\s*"); //operation
		    //rtrim(matched);
		    trim_(matched);
		    this->operation = matched;
		    
		    matched.erase(); 
		    rtrim(exp);
		    ltrim(exp);
		    trim_(exp);
		    this->operand = exp;
		 
		 }
	 
	 
	 
	 
	 void Statement::get_partitioned(){
		 		
		string exp = this->line;
		
		switch(this->formattype){
			
			case 0:
			this->comment = exp;
			break;
			
			case 1:
			case 2:
			case 3:			
			partition_dir();
			break;
			
			case 4:
			partition_format4();
			break;
			
			default:
			
			break;
			
			}
		
		
		 
		 
		 }
	 
	 //void partition_format4(bool label , string exp , statement &st);
	 void Statement::partition_format4(){
		 string matched;
		 string exp = this->line;
		 
	//extracting comment
	matched = extract(exp,";.*");
	this->comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
		
	if(this->labeled){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			//rtrim(matched);
			trim_(matched);
			this->label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*\\+\\w+\\s*"); //operation
		    //rtrim(matched);
		    trim_(matched);
		    
		    this->operation = matched;
		    
		    matched.erase(); 
		    //rtrim(exp);
		    //ltrim(exp);
		    trim_(exp);
		    this->operand = exp;
			this->formattype = 4;
		 
		 }
	 
	int get_matched(string s , regex reg , string &mat){
	smatch match;
	if(regex_search(s,match,reg) == true){
		mat = match.str(0);
		return 1;
		}
	return 0;
	
		 }
		 
		  
	  void trim(string &str){
		 
		 if(str.size()){
			regex ret(".[^\\s]+");
		get_matched(str,ret,str);
			}

		 
		 }

	
	 string extract(string &exp , string re , string delim){
		 
		regex reg(re);
		string matched;
		get_matched(exp, reg , matched);
		trim(matched);
		exp = regex_replace(exp,reg, delim);
		//cout<<"<"<<exp<<"<"<<endl;
		return matched;
		 }
	
	 void ltrim(string &exp){
		 regex reg("^\\s*");
		string mat;
		get_matched(exp , reg,mat);
		exp = regex_replace(exp,reg,"");
	 }
	 
	 
	 void rtrim(string &exp){
	regex reg("(\\s*)$");
	string mat;
	get_matched(exp ,reg,mat);
	exp = regex_replace(exp,reg,"");
		 
		 }

	void trim_(string &exp , string delim){
	regex reg("\\s+");
	exp = regex_replace(exp,reg,delim);
	}
		
	
		
	string split(string line ,int length,int start){
	string token = line.substr(start,length);
	//line = line.substr(length , line.capacity());
	//cout <<line.substr(0,length)<<endl;
	return token;	
}

//void trim_(string &s , string delim="");

bool check_case_1(string exp){
	
	/**
	 * check if operand : label + op + address
	 * */
	 
	//cout<<"check case_1"<<endl;
	
	//exp has no white spaces
	trim_(exp);
	
	//cout<<"Exp in check_case_1 :  "<<"*"<<exp<<"*"<<endl;
	
	string reg = ".+(\\+|-|\\*|/)\\w([0-9a-f]){1,4}"; 
	regex re(reg);
 		if(regex_match(exp , re)){
			//cout<<"yes , case_1"<<endl;	
			return true;		
			}
 return false;		 
}

bool check_case_11(string exp){
	
	/**
	 * check if operand : label only
	 * */
	 
	string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s*"; 
	regex re(reg);
 		if(regex_match(exp , re)){
			
			return true;		
			}
 return false;		 
}

bool check_case_2(string exp){
	
	/**
	 * check if operand : label only
	 * */
	 
	string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s*"; 
	regex re(reg);
 		if(regex_match(exp , re)){
			
			return true;		
			}
 return false;		 
}

bool check_case_3(string exp){
	
	/**
	 * check if operand : address only
	 * */
	 
	string reg = "\\s*\\b([0-9])\\w([0-9a-f]){1,3}\\s*"; 
	regex re(reg);
 		if(regex_match(exp , re)){
			
			return true;		
			}
 return false;		 
}

int check_exp_type(string exp){
	
	int type;
	//label + op + address
	if(check_case_1(exp)) type = 1;
	//label only
	else if(check_case_2(exp)) type = 2;
	//address only
	else if(check_case_3(exp)) type = 3;
	else type = -1;
	return type;
}


