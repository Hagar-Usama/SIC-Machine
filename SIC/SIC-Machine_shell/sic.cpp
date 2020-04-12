#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <regex>
#include <string>

/***********************************************************************
 * To Do :
 * 	1) print all object codes (done)
 * 	2) read object codes into vector obcd (done)
 *  3) print_record (done)
 * 	4) simple addressing --> make it for format3 and format4
 * 
 * 
 ***********************************************************************/

using namespace std;

string split(string &line ,int length);
void get_ob(string filename);
void write_a(string filename , string str);
void write_b(string filename , int hex , int mode=10);
void write_dic(string filename , string str);
void lower_it(string &str);
void read_file(string filename);
void write_file(string filename , string str);
//void write_file(string filename , int num);
void try_write(string filename , string str);
void print_interface();
int find_key(map<string,int> mp , string label);

#include "Statement.cpp"
#include "Assembler.cpp"




void print_interface(){	
	cout<<" *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*" <<endl;
	cout<<" Select mode : 1 for fixed mode , 2 for free format "<<endl;
	cout<<" *.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*.*" <<endl;
	}
	
	
int find_key(map<string,int> mp , string label){
	map<string, int>::iterator it ;
	it = mp.find(label); 
    if(it == mp.end())
		return -1;          
	return it->second; 
      
	}
	
	
	void lower_it(string &str){
		string temp;
		
		//saving case of strings
		temp = extract(str,"[C|c]'.+'" ,"%");
		if(temp.size() >0) temp[0] = tolower(temp[0]);
		
		
		for(unsigned int i=0; i< str.size() ; i++){
			
						str[i] = tolower(str[i]);
			
		}
		extract(str,"%" ,temp);
		
		}
		
void read_file(string filename){
	
	ifstream file(filename);
	if (file.is_open()) {
    string line;
    while (getline(file, line)) {
        /**
         * before pushing call a function that convert statement to
         * lowercase and
         * check if contains the regex [c|C]\\s*'\.+'
         * and extract what's inside the quotation and store it in temp string
         * convert to lower
         * then extract regex \\s*'\.+' and replace with temp
         * lower_it(&line)
         * **/
        lower_it(line);
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


void write_a(string filename , string str){

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


void write_b(string filename , int num , int mode){

	  FILE *fp;
	
		fp = fopen(filename.c_str(),"a");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}
		else{
			
			switch(mode){
				case 2:
				fprintf (fp, "%.2x", num );
				break;
				
				case 6:
				fprintf (fp, "%.6x", num );
				break;
				
				case 8:
				fprintf (fp, "%.8x", num );
				break;
				
				default:
				fprintf (fp, "%x", num );
				break;
				}
				
			}
		
  fclose(fp);

	}
void get_ob(string filename){
	
	ifstream file(filename);
	if (file.is_open()) {
    string line;
    while (getline(file, line)) {
           obcd.push_back(line);
    }
    
    file.close();
	}
	

}
