
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
	Statement(){};
	 
 int check_indexed();
 int check_statement();	 
 int check_comment();
 int check_format4_lab();
 int check_format4_unlab();	 
 int check_format3_lab();
 int check_format3_unlab();	 
 int check_format2_lab();
 int check_format2_unlab();
 int check_dir_lab();
 int check_dir_unlab();
 
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
	check_statement();
	get_partitioned();
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
	if(check_comment()) return 1;
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
	 string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
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
	 string reg = "\\s*((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
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
		
	 
int Statement::check_dir_lab(){
	 string input;
	 string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s+((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(equ)\\s+\\b([a-z]){1}\\w{1,7}(\\+\\d{1,4})?))\\s*(;.*)?";
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
	 string reg = "\\s*((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(end)(\\s+\\b(){1}\\w{1,7})?)|(\\b(org)(\\s+\\b(){1}\\w{1,7}))|(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*)))\\s*(;.*)?";
	 
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
	 
	 //
	 void Statement::divide_operands(){
		 
		 string matched;
		operand2 = extract(this->operand,"^,\\w");
		 
		 
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
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //operation
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
		
//void trim_(string &s , string delim="");

/**
int main(){
	Statement st;
	//st.check_statement("start    1000   ;commenty");
	st.line = "		+j	* + 5;fff";
	//st.trim(st.line);
	st.check_statement();
	st.get_partitioned();
	
	cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
			cout<<"<"<<st.label<<">"<<endl;
			cout<<"<"<<st.operation<<">"<<endl;
			cout<<"<"<<st.operand<<">"<<endl;
			cout<<"<"<<st.operand2<<">"<<endl;
			cout<<"<"<<st.comment<<">"<<endl;
			cout<<"<"<<st.line<<">"<<endl;
	cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
	
	//string ss("Hello my beauty ");
	//trim_(ss);
	//cout<<ss;
	cout<<sizeof(st);
	return 0;
	
	}

**/
