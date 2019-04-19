//https://www.tutorialspoint.com/cpp_standard_library/cpp_regex_search.htm
//https://stackoverflow.com/questions/11508798/conditionally-replace-regex-matches-in-string
//https://solarianprogrammer.com/2011/10/12/cpp-11-regex-tutorial/
#include <iostream>
#include <regex>
#include <string>
 
 using namespace std;
 
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
 	
 	string s ("		labhhel  start we1 ARE11 searching1 for4 a sub subroutine submarine anything :) ");
   smatch m;
   //a boundry word 'sub' followed by anything1 except* for whitespaces (0 or more times)
   regex e ("^[ |\t]*\\b(sub)([^ ]*)");
   // label :   ^([ |\t]*([a-zA-Z]{1}\\w{1,7})[ |\t]?)?
   //directive: [ |\t]*(\\b(start)|\\b(end))[ |\t]
   regex g ("^([ |\t]*([a-zA-Z]{1}\\w{1,7})[ |\t]?)?[ |\t]*(\\b(start)|\\b(end))[ |\t]");
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
    
    cout<<"***"<<endl; 	
 	string input;
 	//"((\\+|-)?([[:digit:]]){4})(\\.(([[:digit:]]+)?))?"
 	regex integer("[^\\w]+");

 	//As long as the input is correct ask for another number
 	while(true)
 	{
 		cout<<"Enter an expression!"<<endl;
 		cin>>input;
 		if(!cin) break;
 		//Exit when the user inputs q
 		if(input=="q")
 			break;
 			//regex_match(line,myExp)
 		if(regex_match(input,integer))
 			cout<<"Valid"<<endl;
 		else
 		{
 			cout<<"Invalid input"<<endl;
 		} 	}
 }
