#include <iostream>
#include <iostream>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <ctype.h>


using namespace std;

int main(){

string s = "rmo stem ,x";
int pos = s.find(",x");
cout<<pos<<endl;
 
//int count = std::count(token.begin(), token.end(), ' ');

bool g = 1;
int i = g<<3;
//00001 , 01000
printf("%x\n",i);

int address = 22408;
int x = 1;
int opcode = 4;
int obcode;

printf("%x\n",address);

x = x<<15;
printf("%x\n",x);

opcode = opcode <<16;
printf("%x\n",opcode);

obcode = opcode + x + address;
printf("%x\n",obcode);


return 0;
}
