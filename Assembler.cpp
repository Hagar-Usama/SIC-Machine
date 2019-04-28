//#include "Instruction.cpp"
vector<string> lines;


/*******
 * 
 * Replace STOI whith another function that handle any format
 * 
 * 
 * 
 **/
class Assembler {
	public:
	int LOCCTR;
	int line_no;
	int start_address;
	
	//vector<Instruction> inst;
	Statement st;
	map<string,int> SYMTAB;
	
	Assembler();
	void object_file();
	
	void pass1_1();
	void pass1_2();

	void print_statement_part();
	void write_ifile(string str);
	void write_ifile(int num , int mode=1);
	void write_line();
	int calc_storage();
	void read_next();
	int get_length();
	int check_complexity();	
	//void get_instructions(vector<string> lines);	
	};
	
Assembler::Assembler(){
	line_no = 1;
	this->st.line = lines[0];
	st.check_part();
	}
	
int check_complexity(){
	
	
	return 1;
	}	
void Assembler::pass1_1(){
	
	if( st.operation.compare("start") == 0){
		start_address = stoi(st.operand);
		LOCCTR = start_address;
		write_ifile(line_no);
		write_ifile("\t\t");
		write_ifile(LOCCTR);
		write_ifile("\t\t");
		write_ifile(st.label);
		write_ifile("\t\t");
		//assuming operand in start is converted to decimal
		write_ifile(st.operation);
		write_ifile("\t\t");
		write_ifile(stoi(st.operand));
		write_ifile("\t\t");
		write_ifile(st.comment);
		write_ifile("\n");
		
		}else{
			if(st.formattype == 0){
				write_ifile(line_no);
				write_ifile("\t\t");
				write_ifile(st.comment);
				write_ifile("\n");
				}
			read_next();
			pass1_1();
			
			}
	}
	
void Assembler::pass1_2(){
	read_next();
	int L , V;
	while(st.operation.compare("end") != 0){
		//if instruction
		if(st.formattype > 1 && st.formattype < 5){
			if(st.labeled){
				//mp.insert({ 2, 30 });
				SYMTAB.insert({st.label , LOCCTR});
								
				}
			L = get_length();
			LOCCTR += L;
			//if there is a literal in operand field then insert into LITTAB
				
		}
		
		
		else{
			if(st.operation.compare("org") == 0){
				LOCCTR = stoi(st.operand);
			}else if(st.operation.compare("equ") == 0){
				
				V = stoi(st.operand);
				SYMTAB.insert({st.label , V});
			}else{
				if(st.labeled){SYMTAB.insert({st.label , LOCCTR}); }
				if(st.operation.compare("word") == 0) L=3;
				if(st.operation.compare("byte") == 0) L=calc_storage();
				if(st.operation.compare("resw") == 0) L = 3*calc_storage();
				if(st.operation.compare("resb") == 0) L = calc_storage();
				
				LOCCTR += L;
					
			}
			
			
		} 
		
		write_line();
			read_next();
		}//end of while
	
	
	
	}

void Assembler::write_line(){
	
		write_ifile(line_no);
		write_ifile("\t\t");
		write_ifile(LOCCTR);
		write_ifile("\t\t");
		write_ifile(st.label);
		write_ifile("\t\t");
		//assuming operand in start is converted to decimal
		write_ifile(st.operation);
		write_ifile("\t\t");
		write_ifile(st.operand);
		write_ifile("\t\t");
		write_ifile(st.comment);
		write_ifile("\n");
	
	
	}
int Assembler::calc_storage(){
	//returns the length of storage in bytes
	//needs work
	return 1;
	}
int Assembler::get_length(){
	switch(st.formattype){
		case 2:
		return 2;
		case 3:
		return 3;
		case 4:
		return 4;
		case 5:
		//return function to calc
		break;
		default:
		return 0;
		
		}
	return 0;
	}
void Assembler::read_next(){
	st.clear_statement();
	this->st.line = lines[line_no];
	line_no++;
	st.check_part();
	
	}
void Assembler::print_statement_part(){
	
	cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
			cout<<"<"<<st.label<<">"<<endl;
			cout<<"<"<<st.operation<<">"<<endl;
			cout<<"<"<<st.operand<<">"<<endl;
			cout<<"<"<<st.operand2<<">"<<endl;
			cout<<"<"<<st.comment<<">"<<endl;
			cout<<"<"<<st.line<<">"<<endl;
	cout<<"*.*.*.*.*.*.*.*.***...**...**..**"<<endl;
	}
	
void Assembler::write_ifile(string str){
	
  FILE *fp;
	
		//fp = fopen(filename.c_str(),"a");
		fp = fopen("listfile.txt","a");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}
		else{
			
				fprintf (fp, "%s", str.c_str() );
			}
		
		


  fclose(fp);

	
	}

void Assembler::write_ifile(int num , int mode){
	
	FILE *fp;
	
		//fp = fopen(filename.c_str(),"a");
		fp = fopen("listfile.txt","a");
		if(fp == NULL) {
		perror("Error");
		exit(1);
		}
		else{
			
				fprintf (fp, "%x", num );
			}
		
		


  fclose(fp);

	
	
	//
	}

/*
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
*/
