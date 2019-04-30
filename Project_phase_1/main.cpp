#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <vector>

#include <regex>
#include <string>
#include <vector>


using namespace std;

string split(string &line ,int length);

void write_dic(string filename , string str);

void read_file(string filename);
void write_file(string filename , string str);
//void write_file(string filename , int num);
void try_write(string filename , string str);

int find_key(map<string,int> mp , string label);
#include "Statement.cpp"
#include "Assembler.cpp"




int main(){
	
	write_dic("listfile.txt" , "");
	read_file("src.txt");
	
	cout<<" *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*" <<endl;
	cout<<" Welcome to my SIC Assembler "<<endl;
	
	string buffer;	
	Assembler assembler;
	
	
		
		cout<<" *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*" <<endl;
		cout<<" Select mode : 1 for fixed mode , 2 for free format "<<endl;
		
		getline(cin , buffer);
		if(buffer.compare("1") == 0){assembler.mode = false;}
		else if(buffer.compare("2") == 0){assembler.mode = true;}
		
		assembler.pass1_1();	
	

return 0;	
}

int find_key(map<string,int> mp , string label){
	map<string, int>::iterator it ;
	it = mp.find(label); 
    if(it == mp.end())
		return -1;          
	return it->second; 
      
	}
	
	
void read_file(string filename){
	
	ifstream file(filename);
	if (file.is_open()) {
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
          
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
	
		fp = fopen(filename.c_str(),"w");
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
