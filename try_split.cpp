#include <iostream>
using namespace std;



	
string split(string &line ,int length,int start=0){
	string token = line.substr(start,length);
	line = line.substr(length , line.capacity());
	//cout <<line.substr(0,length)<<endl;
	return token;	
}


int main(){

string str = "bgn      start   1000   ";
// 1:8 >> 0:7 length 8 and start = 0;
cout<<"*"<<split(str,8,0)<<"*"<<endl;
//cout<<"*"<<str<<"*"<<endl;

// 9:15 >> 8:14 length 7 and start = 8
cout<<"*"<<split(str,7,0)<<"*"<<endl;

// 16:35 >> 15:34 length 20 and start = 15
cout<<"*"<<split(str,20,0)<<"*"<<endl;

return 0;

}
