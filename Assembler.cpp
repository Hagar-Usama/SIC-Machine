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
	int prev_lctr;
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
	int calc_operand(const char op , string label , int address);
	int check_complexity();
	void print_error(int err);
	bool check_error12();	
	//void get_instructions(vector<string> lines);	
	};
	
Assembler::Assembler(){
	line_no = 1;
	this->st.line = lines[0];
	st.check_part();
	}

bool Assembler::check_error12(){
	if(st.operand[0] != 'a' || st.operand[0] != 'b' || st.operand[0] != 'f' || st.operand[0] != 'l'|| st.operand[0] != 's'|| st.operand[0] != 't'|| st.operand[0] != 'x')
	return true;
	if(st.operand.back() != 'a' || st.operand.back() != 'b' || st.operand.back() != 'f' || st.operand.back() != 'l'|| st.operand.back() != 's'|| st.operand.back() != 't'|| st.operand.back() != 'x')
	return true;
	return false;
	}	
void Assembler::print_error(int err){
	write_ifile("\t\t\t ***** Error : ");
	switch (err){
		case 1:
		break;
		
		case 2:
		break;
		
		case 3:
		break;
		
		case 4:
		break;
		
		case 5:
		break;
		
		case 6:
		break;
		
		case 7:
		break;
		
		case 8:
		break;
		
		case 9:
		break;
		
		case 10:
		break;
		
		case 11:
		break;
		
		case 12:
		write_ifile(" illegal address for a resiger\n");
		break;
		
		case 13:
		write_ifile(" missing end statement\n");
		break;
		
		default:
		return;
		
		
		}
	
	}
int Assembler::calc_operand(const char op, string label , int address){
	
	int found = find_key(SYMTAB , label);
	if(found !=-1){
		switch(op){
			case '+':
			return address + found; 
			case '-':
			return address - found; 
			case '*':
			return address * found; 
			case '/':
			return address / found; 
			}
		
		
		}return -1;
	}
	
		
int Assembler::check_complexity(){
	string str = st.operand;
	const char* op;
	char opp;
	
	string re("\\+|-|\\*|/");
	string part;
	//now string has no whitespaces
	trim_(str);
	part = extract(str,re," "); //operation
	if(part.size()){

		//trim_(part);
		
		op = part.c_str(); //get operation // now op points to part (what we need)
		opp = *op;
		
		re = "^.*\\s";
		part = extract(str,re); //get label/variable
		
	    int address = calc_operand(opp , part ,stoi(str, 0, 10));
		if(address !=-1) return address;
		return -1;
		
	}else{
		
		trim_(str);
		//str is hex address
		//converting this address to decimal
		return stoi(str, 0, 16);
		
		
		}
	
	//return -1 for error
	return -1;
	}

void Assembler::pass1_1(){
	
	if( st.operation.compare("start") == 0){
		start_address = stoi(st.operand, 0, 16);
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
		write_ifile(stoi(st.operand, 0, 16));
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
	unsigned int count=1;
	
	while((st.operation.compare("end") != 0)){
		
		//if instruction
		if(st.formattype > 1 && st.formattype < 5){
			if(st.labeled){
				//mp.insert({ 2, 30 });
				SYMTAB.insert({st.label , LOCCTR});
				}
				
			if(st.formattype == 2) {
				
				if(check_error12()) st.error = 12;
				print_error(12);
				;
				}
					
			print_statement_part();
			prev_lctr = LOCCTR;
			
			if(st.error == 0){
				L = get_length();
				//prev_lctr = LOCCTR;
				LOCCTR += L;
				//if there is a literal in operand field then insert into LITTAB
				//write_line();
				
				}
			write_line();	
		}
		
		
		else{
			if(st.operation.compare("org") == 0){
				prev_lctr = LOCCTR;
				LOCCTR = stoi(st.operand);
			}else if(st.operation.compare("equ") == 0){
				
				V = check_complexity(); // check complexity of operand and returns the address
				if(V !=-1){SYMTAB.insert({st.label , V});}
				else { /*return error 9*/}
					
				
			}else{
				if(st.labeled){SYMTAB.insert({st.label , LOCCTR}); }
				
				if(st.operation.compare("word") == 0){L=3*calc_storage();} 
				else if(st.operation.compare("byte") == 0) L=calc_storage();//length of
				else if(st.operation.compare("resw") == 0) L = 3*stoi(st.operand);
				else if(st.operation.compare("resb") == 0) L = stoi(st.operand);
				
				prev_lctr = LOCCTR;
				LOCCTR += L;

				write_line();
			}
			
			
		} 
		
		count++;
		if(count > lines.size()) break;
		
		read_next();
		}//end of while
	
	if(st.operation.compare("end") == 0){write_line();}
	else{print_error(13);}	
	
	}

void Assembler::write_line(){
	
		write_ifile(line_no);
		write_ifile("\t\t");
		write_ifile(prev_lctr);
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
	
	
	int len;
	if(st.operand[0] == 'x'){
		len = (st.operand.size() - 3)/2;
		return (len > 0) ? len : 1;
	}else if(st.operand[0] == 'c'){
		return st.operand.size()-3;
	}else{
		
		return std::count(st.operand.begin(), st.operand.end(), ',')+1;
		
		}
	
	return -1;
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
