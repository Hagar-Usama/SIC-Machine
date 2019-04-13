#include "Instruction.cpp"


class Assembler {
	public:
	int LC;
	int pc;
	vector<Instruction> inst(SIZE);
	Assembler();
	void object_file();
	void get_instructions(vector<string> lines);	
	};
	
Assembler::Assembler(){}
void Assembler::get_instructions(vector<string> lines){
	int size = lines.size();
	for( int i=0; i< size ; i++){
		Instruction temp;
		temp.line = lines[i];
		temp.partition();
		inst.push_back(temp);
		
		//lines.push_back(line);
		}
	
	}

