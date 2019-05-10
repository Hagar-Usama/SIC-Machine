#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>

#include <regex>
#include <string>
#include <vector>

using namespace std;

int eval_exp(string exp){
	/**
	 * exp can be in ... cases :
	 * label + op +  address
	 * label only
	 * address only 
	 * */
	
	}


int main(){



return 0;

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
