#include<iostream>

using namespace std;

int main(){

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
