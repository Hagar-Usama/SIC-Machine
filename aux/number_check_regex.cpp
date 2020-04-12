//https://www.tutorialspoint.com/cpp_standard_library/cpp_regex_search.htm
//https://stackoverflow.com/questions/11508798/conditionally-replace-regex-matches-in-string
//https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/
#include <iostream>
#include <regex>
#include <string>

#define SP [ |\t] 
 using namespace std;
 
 int check_dir_lab( string exp);
 int main()
 {
 	
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
 	
 	string s ("		start   1000  ;gggg");
   smatch m;
   //a boundry word 'sub' followed by anything1 except* for whitespaces (0 or more times)
   regex e ("^[ |\t]*\\b(sub)([^ ]*)");
   // label :   ^([ |\t]*([a-zA-Z]{1}\\w{1,7})[ |\t]?)?
   //directive: [ |\t]*(\\b(start)|\\b(end))[ |\t]
   // ^([ |\t]*(\\b(){1}\\w{1,7})[ |\t]?)?[ |\t]*(\\b(start)|\\b(end))[ |\t]
   //final thought : \\s*(\\b(){1}\\w{1,7})\\s+((\\b(start)\\s+\\[a-f0-9]{4})|(\\b(byte)\\s+((c'.{1,14}')|(x'[a-f0-9]{1,4}'))))
   regex g ("\\s*(\\b(){1}\\w{1,7})\\s+(;.*)?");
   cout << "Target sequence: " << s << std::endl;
   cout << "Regular expression: /\\b(sub)([^ ]*)/" << endl;
   cout << "The following matches and submatches were found:" << endl;

 
  while (std::regex_search (s,m,g)) {
      for (auto x:m) cout <<"{"<< x << "}";
      cout << endl;
      s = m.suffix().str();
 	}
 	
 	cout<<"\n*****\n";
 	//*****************************************************************
 	string test = "test replacing \"these characters\"";
    
    regex reg("[^\\w]+");
    test = regex_replace(test, reg, "_");
    cout << test << endl;
    
    cout<<"************************************************"<<endl; 	
	
 	string input;
 	while(true)
 	{
 		cout<<"Enter an expression!"<<endl;
 		getline (cin, input);
 		check_dir_lab( input); 		
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


 */


	 }
