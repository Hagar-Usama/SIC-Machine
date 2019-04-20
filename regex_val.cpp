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
// >>trim>> http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
#include <iostream>
#include <regex>
#include <string>

 using namespace std;
 struct statement{
	 string label;
	 string operation;
	 string operand;
	 string commnet;
	 int formattype;	 
	 };
 
 int check_dir_lab( string exp);
 int check_dir_unlab( string exp);
 void partition_dir(bool label , string exp);
 int get_matched(string s , regex reg , string &mat);
 void trim(string &str);
/* 
 std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

*/
int main(){
	bool labeled;
	
	string input;
 	while(true)
 	{
 		cout<<"labeled mode\n";
 		getline (cin, input);
 		if(check_dir_lab( input)){
			labeled = true;
			//string reg = "^(\\s*(\\b(){1}\\w{1,7})\\s+)";
			
			string reg("^(\\w)+");
			regex re (reg);
			string pmatch;
			//get_matched(input, re , pmatch);
			//pmatch = trim(pmatch);
			//cout<<endl<<"**"<<pmatch<<"**\n";
			partition_dir(labeled , input);
			
		}else if(check_dir_unlab( input)){
			labeled = false;
			}
			
 		 	}

return 0;

	}



 int check_dir_lab( string exp){
	 
	 string input;
	 string reg = "\\s*(\\b([a-z]){1}\\w{1,7})\\s+((\\b(start)\\s+[a-f0-9]{1,4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,15}')))|(\\b(word)\\s+-?\\d{1,4}(,-?\\d{1,4})*)|(\\b(resw|resb)\\s+\\d{1,4})|(\\b(equ)\\s+\\b([a-z]){1}\\w{1,7}(\\+\\d{1,4})?))\\s*(;.*)?";
	 
	 regex re(reg);
		
 		if(regex_match(exp,re)){
			cout<<"Valid"<<endl;
			return 1;		
			}
 		else
 		{
 			cout<<"Invalid input"<<endl;
 			return 0;
 		}

		
/*
label :
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
			cout<<"Valid"<<endl;
			return 1;		
			}
 		else
 		{
 			cout<<"Invalid input"<<endl;
 			return 0;
 		}
}


int get_matched(string s , regex reg, string &mat){
	
	smatch match;
	if(regex_search(s,match,reg) == true){
		//cout<<"Match Size = "<<match.size()<<endl;
		mat = match.str(0);
		return 1;
		}
	return 0;
	
	}
	
void partition_dir(bool label , string exp){
	
	string matched;
	if(label){
	//target : label - operation - operand - comment
	
	//extract label	    
    regex reg1("^\\s*[\\w]+\\s*");
    get_matched(exp, reg1 , matched);
    
    
    //trimming label using regex:
    trim(matched);
    cout<<"label :"<<"<"<<matched<<">"<<endl;
   
	matched.erase();
    //erasing extracted part
    exp = regex_replace(exp,reg1, "");
    cout <<"after replacing: "<<exp << endl;
    
    //search for another part
    regex reg2("^\\s*[\\w]+\\s*");
    get_matched(exp, reg2 , matched);
    trim(matched);
    cout<<"operation: ""<"<<matched<<">"<<endl;
    matched.erase();
    
    exp = regex_replace(exp,reg2, "");
    cout <<"after replacing: "<<exp << endl;
    
    //search for another part
    get_matched(exp, reg2 , matched);
    trim(matched);
    cout<<"operand: ""<"<<matched<<">"<<endl;
    matched.erase();
    
    exp = regex_replace(exp,reg2, "");
    cout <<"after replacing: "<<exp << endl;
    
    //search for another part
    get_matched(exp, reg2 , matched);
    trim(matched);
    cout<<"comment: ""<"<<matched<<">"<<endl;
    
    exp = regex_replace(exp,reg2, "");
    cout <<"after replacing: "<<exp << endl;
    
		}else{}
	
	
	}

void trim(string &str){
		if(str.size()){
			regex ret("\\w+");
		get_matched(str,ret,str);
			}
		
		}
