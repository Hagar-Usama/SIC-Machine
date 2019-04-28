#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#include <regex>
#include <string>
#include <vector>


#define MAX 100
using namespace std;

string split(string &line ,int length);

void write_dic(string filename , string str);

void read_file(string filename);
void write_file(string filename , string str);
//void write_file(string filename , int num);
void try_write(string filename , string str);


#include "Statement.cpp"
#include "Assembler.cpp"


void check_it(string exp){
	//string str(" label+");
	string str = exp;
	char op;
	//string re("^\\s*\\b([a-z]){1}\\w{0,7}\\s*(\\+|-|\\*)");
	string re("\\+|-|\\*|/");
	string part;
	
	//now string has no whitespaces
	trim_(str);
	part = extract(str,re," "); //operation
	if(part.size()){
		//trim_(part);
		cout<<"mode 1 "<<endl;
		cout<<"operation " << part<<endl;
		re = "^.*\\s";
		part = extract(str,re);
		cout<<part<<endl;
		cout<<str<<endl;
		
	}else{
		/*
		//check for just hex
		re= "^\\s*+[a-f0-9]{1,4}";
		string part = extract(str,re);
		cout<<"mode 2 "<<endl;
		cout<<part<<endl;
		*/
		}
	
	
	}




int main(){
	
	check_it("		label	/	15");
	check_it("1ff5");
	
	
	//cout<<str<<endl;
	
	read_file("src.txt");
	//write_dic("listfile.txt","Line no\t\tAddress\t\tLabel\t\tMnemonic\t\tOperands\t\tComments\n");
	Assembler ass;
	ass.pass1_1();
	ass.pass1_2();
	ass.print_statement_part();
	cout<<ass.LOCCTR<<endl;
	cout<<sizeof(ass)<<endl;
	Statement s;
	s.operand = "a";
	s.check_indexed();
	cout<<s.indexed;
return 0;	
}

void read_file(string filename){
	
	ifstream file(filename);
	int i =0;
	if (file.is_open()) {
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
        cout<<lines[i++]<<endl;    
    }
    
    file.close();
	}
	

}

void try_write(string filename , string str){
	ofstream outfile;
   outfile.open(filename);
   outfile<<str;
   
   outfile.close();
	
	
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
	

void write_dic(string filename , string str){

	  FILE *fp;
	
		fp = fopen(filename.c_str(),"a");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}
		else{
			
				fprintf (fp, "%s", str.c_str() );
			}
		
		


  fclose(fp);

	}


////////////////////////////////////////////////////////////////////////	
/*
string split(string &line ,int length){
	
	string token = line.substr(0,length);
	line = line.substr(length , line.capacity());
	
	
	return token;	
}
*/
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
