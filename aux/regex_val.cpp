/***
 	 * My algorithm for validating SIC instruction using RegEx
 	 * 
 	 * 
 	 * Part II (extracting data form accepted expression)
 	 * 		assume we know : (statement/directive) , (which format/type) , (labeled or not)
 	 * 		we extract part by part, then replace extracted part by a whitespace
 	 * 		then the next part is now the first one, we extract it as if it was the first
 	 * 		regular expression suggested is "^[ |\t]*\\b('exact expression we search for without quotation mark')([^ ]*)"
 	 * */
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

 using namespace std;

vector<string> lines;
 
//statement taken from txt file
 struct statement{
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
	 int formattype; //directive = 0 , format2 = 2 , format3=3 ,format4=4	 
	 };

int read_file(string filename){
	
	ifstream file(filename);
	int i =0;
	if (file.is_open()) {
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
        cout<<lines[i++]<<endl;    
    }
    
    file.close();
	return i;
	}
	
	return -1;
}

void write_file(string filename , string str){
	
  ofstream myfile (filename);
  if (myfile.is_open())
  {
    myfile <<str;
    myfile.close();
  }
  else cout << "Unable to open file";
	
	}
 int check_indexed(statement &st);
 int check_statment(string exp);	 
 int check_comment( string exp);
 int check_format4_lab( string exp);
 int check_format4_unlab( string exp);	 
 int check_format3_lab( string exp);
 int check_format3_unlab( string exp);	 
 int check_format2_lab( string exp);
 int check_format2_unlab( string exp);
 int check_dir_lab( string exp);
 int check_dir_unlab( string exp);
 
 void divide_operands(statement &st);
 void partition_dir(bool label , string exp , statement &st );
 void parition_all(bool label , string exp , statement &st);
 void get_partitioned(string exp , statement &st);
 void partition_format4(bool label , string exp , statement &st);
 
 int get_matched(string s , regex reg , string &mat);
 void trim(string &str);
 string extract(string &exp , string re);
 void ltrim(string &exp);
 void rtrim(string &exp);

int main(){
	//bool labeled;
	statement st;
	string input;
	int flag;
	
	int index = read_file("src.txt");
 	for(int i = 0 ; i<index ; i++){
		cout<<"free format mode\n";
 		//getline (cin, input);
 		
 		
 			flag = check_statment(lines[i]);
 			
 			switch(flag){
				case 0:
				//labeled = false;
				cout<<"comment"<<endl;
				break;
				case 10:
				//labeled = false;
				cout<<"dir unlabled"<<endl;
				break;
				case 11:
				//labeled = true;
				cout<<"dir labled"<<endl;
				break;
				case 20:
				//labeled = false;
				cout<<"format 2 unlabled"<<endl;
				break;
				case 21:
				//labeled = true;
				cout<<"format 2 labled"<<endl;
				break;
				case 30:
				//labeled = false;
				cout<<"format 3 unlabled"<<endl;
				break;
				case 31:
				//labeled = true;
				cout<<"format 3 labled"<<endl;
				break;
				case 40:
				//labeled = false;
				cout<<"format 4 unlabled"<<endl;
				break;
				case 41:
				//labeled = true;
				cout<<"format 4 labled"<<endl;
				break;
				default:
				cout<<"invalid input"<<endl;
				break;
				}
				
				st.label.erase();
				st.operation.erase();
				st.operand.erase();
				st.comment.erase();
				get_partitioned(lines[i] , st);
				
			if(flag>21){check_indexed(st);}		
			cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
			cout<<"<"<<st.label<<">"<<endl;
			cout<<"<"<<st.operation<<">"<<endl;
			cout<<"<"<<st.operand<<">"<<endl;
			cout<<"<"<<st.comment<<">"<<endl;
			cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
		
		
		}
 	
 	/*
 	while(1)
 	{
 		
 		 	}
   */
return 0;

	}

/*

(\\b(resw|resb)\\s+\\d{1,4})
RMO :ADDER ,SUBR,COMPR
	(\\b(rmo|addr|subr|compr)\\s+\\b(a,x,l,b,s,t,f),\\b(a,x,l,b,s,t,f))
TIXR:
	(\\b(tixr)\\s+\\b(a,x,l,b,s,t,f))
*/

/*
	(\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|j|jeq|jlt|jgt|tix)\\s+(@|#)?\\s+(((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s+(,\\s*x))

*/

int check_indexed(statement &st){
	/** we're gonna check operand filed **/
	
	string reg = "((\\w+)|\\d|\\*)\\s*((\\+|-)\\s*\\d)?\\s*(,\\s*x)";
	regex re(reg);
 		if(regex_match(st.operand,re)){
			//cout<<"indexed"<<endl;
			st.indexed = true;
			return 1;
		}	
			st.indexed = false;
 			return 0;
	}
	
int check_statment(string exp){
	
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
	if(check_comment(exp)) return 0;
	if(check_dir_unlab(exp))return 10;
	if(check_dir_lab(exp))return 11;
	if(check_format2_unlab(exp))return 20;
	if(check_format2_lab(exp))return 21;
	if(check_format3_unlab(exp))return 30;
	if(check_format3_lab(exp))return 31;
	if(check_format4_unlab(exp))return 40;
	if(check_format4_lab(exp))return 41;
	return -1;
	
	
	}
int check_comment( string exp){
	 string reg = "\\s*\\..*"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}


int check_format4_lab( string exp){
	 string input;
	 string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)\\+\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid format 4"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}

int check_format4_unlab( string exp){
	 string input;
	 string reg = "\\s*\\+\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid format 4"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}
int check_format3_lab( string exp){
	 string input;
	 string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid format 3"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}

int check_format3_unlab( string exp){
	 string input;
	 string reg = "\\s*\\b(lda|ldb|ldf|ldl|lds|ldt|ldx|sta|stb|stf|stl|sts|stt|stx|ldch|stch|add|sub|comp|j|jeq|jlt|jgt|tix)\\s+((@|#)\\s*)?((\\b([a-z]){1}\\w{0,7})|\\d{1,4}|\\*)\\s*((\\+|-)\\s*\\d{1,4})?\\s*(,\\s*x)?\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid format 3"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}

int check_format2_lab( string exp){
	 string input;
	 string reg = "\\s*((\\b([a-z]){1}\\w{0,7})\\s+)((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid format 2"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}

int check_format2_unlab( string exp){
	 string input;
	 string reg = "\\s*((\\b(rmo|addr|subr|compr)\\s+\\b(a|x|l|b|s|t|f)\\s*,\\s*)|(\\b(tixr)\\s+))\\b(a|x|l|b|s|t|f)\\s*(;.*)?"; 
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid format 2"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}
}

 int check_dir_lab( string exp){
	 string input;
	 string reg = "\\s*(\\b([a-z]){1}\\w{0,7})\\s+((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(equ)\\s+\\b([a-z]){1}\\w{1,7}(\\+\\d{1,4})?))\\s*(;.*)?";
	 regex re(reg);
 		if(regex_match(exp,re)){
			//cout<<"Valid"<<endl;
			return 1;		
			}
 		else
 		{
 			return 0;
 		}

		
/*
label : \\s*(\\b([a-z]){1}\\w{0,7})
		\\s*(\\b(){1}\\w{1,7})\\s+
START :
		(\\b(start)\\s+\\[a-f0-9]{4})
BYTE :
		(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))
WORD :
		(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)

RESEB / RESW
		(\\b(resw|resb)\\s+\\d{1,4})

EQU :
		(\\b(equ)\\s+\\b(){1}\\w{1,7}(+\\d{1,4})?)
comment:
		(;.*)?

END : 	(\\b(end)(\\s+\\b(){1}\\w{1,7})?)

ORG :
		(\\b(org)(\\s+\\b(){1}\\w{1,7}))
BASE:
		(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*))
 */


	 }


int check_dir_unlab( string exp){
	 
	 //(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*))
	 //(\\b(org)(\\s+\\b(){1}\\w{1,7}))
	 string input;
	 string reg = "\\s*((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(end)(\\s+\\b(){1}\\w{1,7})?)|(\\b(org)(\\s+\\b(){1}\\w{1,7}))|(\\b(base)\\s+((\\b(){1}\\w{1,7})|\\*)))\\s*(;.*)?";
	 
	 regex re(reg);
		
 		if(regex_match(exp,re)){
			//cout<<"Valid"<<endl;
			return 1;		
			}
 		else
 		{
 			//cout<<"Invalid input"<<endl;
 			return 0;
 		}
}


int get_matched(string s , regex reg, string &mat){
	
	smatch match;
	if(regex_search(s,match,reg) == true){
		mat = match.str(0);
		return 1;
		}
	return 0;
	
	}

void partition_format2(bool label , string exp , statement *st ){
	
	string matched;
	regex reg("^\\s*[\\w]+\\s*");
	
	//extracting comment
	matched = extract(exp,"(;|\\.).*");
	st->comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
	
	if(label){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			st->label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //operation
		    rtrim(matched);
		    st->operation = matched;
		    
		    matched.erase(); 
		    rtrim(exp);
		    ltrim(exp);
		    st->operand = exp;
			st->formattype = 0;	
	}


void partition_format4(bool label , string exp , statement &st){
	
	string matched;
	//extracting comment
	matched = extract(exp,";.*");
	st.comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
		
	if(label){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			rtrim(matched);
			st.label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*\\+\\w+\\s*"); //operation
		    rtrim(matched);
		    
		    st.operation = matched;
		    
		    matched.erase(); 
		    rtrim(exp);
		    ltrim(exp);
		    st.operand = exp;
			st.formattype = 4;
	}	

void get_partitioned(string exp , statement &st){
		bool label = true;
		
		int format = check_statment(exp);
		if(format%2 == 0) label = false;
		st.formattype = format;
		switch(format){
			
			case 0:
			st.comment = exp;
			break;
			case 10:
			case 11:
			case 20:
			case 21:
			case 30:
			case 31:
			partition_dir(label,exp,st);
			break;
			case 40:
			case 41:
			partition_format4(label , exp ,st);
			break;
			
			default:
			
			break;
			
			}
		
			
	}
void partition_dir(bool label , string exp , statement &st ){
	
	string matched;
	regex reg("^\\s*[\\w]+\\s*");
	
	//extracting comment
	matched = extract(exp,";.*");
	st.comment = matched;
	matched.erase();
			
	//trimming :
	ltrim(exp);
	//extract(exp,"^\\s*");
	//matched.erase();
	
	if(label){
	//target : label - operation - operand - comment
			
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //label
			rtrim(matched);
			st.label = matched;
			matched.erase();
		}	
			ltrim(exp);
			matched = extract(exp,"^\\s*[\\w]+\\s*"); //operation
		    rtrim(matched);
		    st.operation = matched;
		    
		    matched.erase(); 
		    rtrim(exp);
		    ltrim(exp);
		    st.operand = exp;
			//st.formattype = 0;	
	}

void trim(string &str){
		if(str.size()){
			regex ret(".[^\\s]+");
		get_matched(str,ret,str);
			}
		
		}

string extract(string &exp , string re ){
		regex reg(re);
		string matched;
		get_matched(exp, reg , matched);
		//trim(matched);
		exp = regex_replace(exp,reg, "");
		//cout<<"<"<<exp<<"<"<<endl;
		return matched;
		}

void ltrim(string &exp){
	regex reg("^\\s*");
	string mat;
	get_matched(exp , reg,mat);
	exp = exp = regex_replace(exp,reg,"");
	}


void rtrim(string &exp){
	regex reg("(\\s*)$");
	string mat;
	get_matched(exp , reg,mat);
	exp = exp = regex_replace(exp,reg,"");
	}

