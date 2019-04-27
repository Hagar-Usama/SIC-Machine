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


int main(){
	//read_file("src.txt");
	//cout<<lines.size();
	//lines.push_back("ddd");
	//cout<<lines.size()<<" "<<lines[0];
	//try_write("ss.txt" , "\nhi");
	
	//write_dic("ss.txt","hello from dic");
	//write_dic("ss.txt" , "Hello again");
	
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
