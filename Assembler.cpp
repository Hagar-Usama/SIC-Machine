//#include "Instruction.cpp"
vector<string> lines;


/*******
 * 
 * Replace STOI whith another function that handle any format //done
 * Mind ORG 
 * check error if label is a register 
 * directives not implemented should be ignored with a warning //done
 * 
 **/
 

class Assembler {
	public:
	int LOCCTR;
	int prev_lctr;
	unsigned int line_no;
	bool mode;
	int start_address;
	Statement st;
	map<string,int> SYMTAB;
	unsigned int errors;
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
	bool check_error15();
	bool check_error16();
	bool check_error11();
	bool check_error9();
	bool check_error10();
	bool check_error5();
	bool check_error7();
	bool check_error4();
	bool check_error8();
	bool check_warning();
	bool have_error();	
	bool check_fixed();
	void print_map();
	int check_symbol();
	void sub_pass1();
	};
	
Assembler::Assembler(){
	line_no = 1;
	this->st.line = lines[0];
	st.check_part();
	mode = true; //fixed , free
	}

bool Assembler::check_fixed(){
	/**
	 * how it works :
	 * 1) we search for tabs >> 'tabs not allowed' error 14
	 * 2) we split into 4 sections (label - operation - operand - comment)
	 * 3) if label.size() != 0 & label[0] == ' ' >>  'misplaced label' error 1
	 * 4) if operation[0] == ' ' >> 'missing or missplaced operation nmemonic' error 2
	 * 5) if operand.size()!=0 && operand[0] == ' ' >> missing or misplaced operand field error 3
	 * 
	 * hadles comment 
	 * 
	 * returns true is error exists
	 * **/
	
	
	string temp = st.line;
	string token;
	unsigned int tab =0;
	unsigned int count;
	extract(temp , "\\t","%");
	
	//cout<<"temp replace tabs by %**"<<temp<<endl;
	
	// we can count tabs '\t' directly
	tab = std::count(temp.begin(), temp.end(), '%');
	//1)
	if(tab){ print_error(14); return true;}
		
		//make sure length is 35 to split without throwing error
		while(temp.size() < 35){
			temp.push_back(' ');
			}
		
		//cout<<"**"<<"temp"<<temp<<"**"<<endl;
		//cout<<"**"<<temp.size()<<"**"<<endl;
		
		//label
		token = split(temp,8,0);
		count = std::count(token.begin(), token.end(), ' ');
		
		//cout<<"# of spaces "<<count<<endl;
		if(count > 8){
		 if (token[0] == ' '){ print_error(1); return true;}	
		}
		
		token = split(temp,7,8);
		if(token[0] != ' '){print_error(7); return true;}
		if(token[1] == ' '){print_error(2); return true;}
		
		token = split(temp,20,15);
		if(token[2] == ' '){print_error(3); return true;}
		
/*	
	
	// 1:8 >> 0:7 length 8 and start = 0;
cout<<"*"<<split(str,8,0)<<"*"<<endl;
//cout<<"*"<<str<<"*"<<endl;

// 9:15 >> 8:14 length 7 and start = 8
cout<<"*"<<split(str,7,8)<<"*"<<endl;

// 16:35 >> 15:34 length 20 and start = 15
cout<<"*"<<split(str,20,15)<<"*"<<endl;

	//label
	token = split(st.line ,8,0); 
	//operation
	token = split(st.line ,7,8); 
	//operand
	token = split(st.line ,20,15); 
*/
	
	return false;
	
	}
	
void Assembler::print_map(){
	write_ifile("\n\n\t\t\t*.*.*.*.*SYMBOL TABLE*.*.*.*.*\n");
	write_ifile("\t\t\tSYMBOL\t\t\tADDRESS\n");
	for(map<string, int >::const_iterator it = SYMTAB.begin();
    it != SYMTAB.end(); ++it)
{
    //std::cout << it->first << " " << it->second<< "\n";
    write_ifile("\t\t\t");
    write_ifile(it->first);
    write_ifile("\t\t\t");
    write_ifile(it->second);
    write_ifile("\n");
}
	
write_ifile("\t\t\t*.*.*.*.*.*.*.*.*.*.*.*.*.*.*\n");
	
}
int Assembler::check_symbol(){
	string oper , temp;
	oper = st.operand;
	extract(oper , ",x");
	extract(oper,"\\+");
	extract(oper,"#");
	extract(oper,"@");
	//extract(oper,"\\*");
	if(oper[0] == '*') return 1;
	
	//cout<<"oper after trimming ,x ,+,# "<<oper<<endl;
	temp = extract(oper,"^((0[0-9a-f]+)|(\\d+))");
	
	//cout<<"line_no"<< line_no<<"temp in check symbol :"<<temp<<endl;
	//cout<<"temp is "<<temp<<endl;
	//cout<<"size is "<<temp.size()<<endl;
	
	if(temp.size() > 0) return stoi(temp, 0, 16); 
	
	if(oper.size() >0){
		return find_key(SYMTAB , oper);
		}
		return -1;
	
	}	
bool Assembler::have_error(){
	
	//if fixed mode check tabs and displacement
	if(!mode){if(check_fixed())return true;}
	
	//if found unimplemented instruction display warning
	if(st.error == 0) {return check_warning();}
	
	//if statement unrecognized 
	if(st.check_statement() == -1) return check_error8();
	
	// if statement is labled
	if(st.labeled){
		//if label is register name or j
		if(check_error15()) return true;
		//if label is already defined
		if(check_error4())	return true;
		} else{
			if(st.operation.compare("equ") == 0 ){
				if(check_error16()) return true;}		
			}
	
	//if the hex string in byte isn't hex
	if(st.operation.compare("byte") == 0)
	{	
		if(check_error10())	return true ;
	}
	
	//if statement can't have a label
	if(st.operation.compare("org") == 0 || st.operation.compare("base") == 0 || st.operation.compare("end") == 0){
		if(check_error5()) return true;
		
	}
	
	
	//if undefined label
	if(st.operation.compare("org") == 0 || st.operation.compare("equ") == 0 ){
		if(check_error9()) return true;
		
	}
	
	
	if(st.formattype == 2){
	// if can't be format 4
	if(check_error11()) return true;
	//if illegal address for a register
	if(check_error12()) return true;
	
	} 
	
	if(st.formattype == 3 || st.formattype == 4){
	  //if symbol undefined
	  if(check_error9()) return true;
	}
	
	return false;
	}

bool Assembler::check_warning(){
	print_error(0);
	st.operation = st.line;
	return true;
	}
bool Assembler::check_error16(){
	print_error(16);
	errors++;
	return true;
	
	}
bool Assembler::check_error15(){
		if(st.label.size() == 1){
			char lab = st.label[0];
			
			switch (lab){
				
				case 'a':
				case 'b':
				case 'f':
				case 'l':
				case 's':
				case 't':
				case 'x':
				case 'j':
				print_error(15);
				errors++;
				return true;
						
				}
			
			
			}
		
		return false;
	}

bool Assembler::check_error8(){
		print_error(8);
		errors++;
		st.operation = st.line;
		return true;
	}
bool Assembler::check_error9(){
		//cout<<"enter check error9 \n";
		int k = check_symbol();
	//if key is found >> defined
	if(k !=-1)	
		return false;
	
	print_error(9);
	errors++; 
	return true;	
	
	
	}
		
bool Assembler::check_error4(){
	int k = find_key(SYMTAB , st.label);
	if(k !=-1){
		print_error(4);
		errors++;
		return true;
		} 
	return false;	
	}
	
bool Assembler::check_error7(){
	if(st.operation[0] == '+'){
		st.error = 7;
		print_error(7);
		errors++;
		return true;
		}
	return false;
	}

bool Assembler::check_error11(){
	if(st.operation[0] == '+'){
		st.error = 11;
		print_error(11);
		errors++;
		return true;
		}
	return false;
	}

	
bool Assembler::check_error5(){
	if(st.labeled){
		
		print_error(5);
		errors++;
		return true;
		} 
	
	if(st.error == 5){
		print_error(5);
		errors++;
		return true;
	}
	
	return false;
	}	


bool Assembler::check_error10(){
	string mat;
	regex reg("(c'.{1,14}')|(x'[a-f0-9]{1,15}')");
	if(get_matched(st.operand , reg , mat)){
		
		return false;
		}
	 
		st.error = 10;
		//cout<<"entered error 10"<<endl;
		print_error(10);
		errors++;
	return true;
	
	}
bool Assembler::check_error12(){
	char top = st.operand[0];
	char back = st.operand.back();
	
	switch (top){
		case 'a':
		case 'b':
		case 'f':
		case 'l':
		case 's':
		case 't':
		case 'x':
		break;
		default:
		print_error(12);
		errors++;
		return true;
		}
		
	switch (back){
		case 'a':
		case 'b':
		case 'f':
		case 'l':
		case 's':
		case 't':
		case 'x':
		break;
		default:
		print_error(12);
		errors++;
		return true;
		}
		
		return false;
	
	}	


void Assembler::print_error(int err){
	
	switch (err){
		case 0:
		write_ifile("\t\t\t ***** Warning : Not implemented (ignored)\n");
		break;
		case 1:
		write_ifile("\t\t\t ***** Error :  misplaced label\n");
		break;
		
		case 2:
		write_ifile("\t\t\t ***** Error :  missing or misplaced operation mnemonic\n");
		break;
		
		case 3:
		write_ifile("\t\t\t ***** Error :  missing or misplace operand file\n");
		break;
		
		case 4:
		write_ifile("\t\t\t ***** Error :  duplicate label defition\n");
		break;
		
		case 5:
		write_ifile("\t\t\t ***** Error :  this statement can't have a label\n");
		break;
		
		case 6:
		write_ifile("\t\t\t ***** Error :  this statement can't have an operand\n");
		break;
		
		case 7:
		write_ifile("\t\t\t ***** Error :  wrong operation prefix\n");
		break;
		
		case 8:
		write_ifile("\t\t\t ***** Error :  unrecognized operation code or invalid statement\n");
		break;
		
		case 9:
		write_ifile("\t\t\t ***** Error :  undefined symbol in operand\n");
		break;
		
		case 10:
		write_ifile("\t\t\t ***** Error :  not a hexadecimal string\n");
		break;
		
		case 11:
		write_ifile("\t\t\t ***** Error :  can't be format 4 instruction\n");
		break;
		
		case 12:
		write_ifile("\t\t\t ***** Error :  illegal address for a register\n");
		break;
		
		case 13:
		write_ifile("\t\t\t ***** Error :  missing end statement\n");
		break;
		
		case 14:
		write_ifile("\t\t\t ***** Error :  tabs not allowed\n");
		break;
		
		case 15:
		write_ifile("\t\t\t ***** Error :  invalid name for a label\n");
		break;
		
		case 16:
		write_ifile("\t\t\t ***** Error :  this statement requires a label\n");
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
void Assembler::sub_pass1(){
			
		start_address = stoi(st.operand, 0, 16);
		LOCCTR = start_address;
		if(st.labeled) SYMTAB.insert({st.label , LOCCTR});
		
		write_ifile(line_no , 2);
		write_ifile("\t\t");
		write_ifile(LOCCTR);
		write_ifile("\t\t");
		write_ifile(st.label);
		write_ifile("\t\t");
		write_ifile(st.operation);
		write_ifile("\t\t");
		write_ifile(stoi(st.operand, 0, 16));
		write_ifile("\t\t");
		write_ifile(st.comment);
		write_ifile("\n");
			
			}
		
void Assembler::pass1_1(){
	
	if( st.operation.compare("start") == 0){
			
		if(!have_error()){
			sub_pass1();
			
		}else{
			write_ifile(line_no);
			write_ifile("\t\t\t\t");
			write_ifile(st.line);
			write_ifile("\n");
			LOCCTR = 0;
			
			}
			
			pass1_2();
			// else not start :
	}else{
			if(st.formattype == 0){
				write_ifile(line_no,2);
				write_ifile("\t\t");
				write_ifile(st.comment);
				write_ifile("\n");
			}else{
				write_ifile("\t\t\t ***** Error :  program must start with 'start' mnemonic\n");
				write_ifile(line_no);
				write_ifile("\t\t");
				write_ifile(st.line);
				write_ifile("\n");
				
				}
			read_next();
			pass1_1();
			
	}
}


	
void Assembler::pass1_2(){
	read_next();
	int L , V;
	
	
	while((st.operation.compare("end") != 0) ){
	
			if(line_no >= lines.size() + 1) break;
			
	if(!have_error()){
			
			//if instruction
		if(st.formattype > 1 && st.formattype < 5){
			if(st.labeled){
				
				SYMTAB.insert({st.label , LOCCTR});
				}
				
					
			
			prev_lctr = LOCCTR;
			
			
			L = get_length();
			LOCCTR += L;
				
			//if there is a literal in operand field then insert into LITTAB
				
			
				
				
				
		}
		
		// if directive
		else{
			
			if(st.operation.compare("org") == 0){
				prev_lctr = LOCCTR;
				
				//LOCCTR = stoi(st.operand);
				LOCCTR = check_symbol();
				
			}else if(st.operation.compare("equ") == 0){
				
				V = check_complexity(); // check complexity of operand and returns the address
				if(V !=-1){SYMTAB.insert({st.label , V});}
				else { /*return error 9*/}
					
				
			}else{
				if(st.labeled){SYMTAB.insert({st.label , LOCCTR}); }
				
				if(st.operation.compare("word") == 0){L=3*calc_storage();} 
				else if(st.operation.compare("byte") == 0){
					if(!check_error10()) L=calc_storage();
				} 
				else if(st.operation.compare("resw") == 0) L = 3*stoi(st.operand);
				else if(st.operation.compare("resb") == 0) L = stoi(st.operand);
				
				prev_lctr = LOCCTR;
				LOCCTR += L;

				
			}
			
			
		} 
		
		
		
			
			
	}else{
			 prev_lctr = LOCCTR;
		}
		
		write_line();
		read_next();
		}//end of while
	prev_lctr = LOCCTR;
	if(st.operation.compare("end") == 0){
		
		write_line();}
	else{print_error(13);errors++; write_line();}	
	
	print_map();
	
	if(errors){ 
		write_ifile("\n errors :");
		write_ifile(errors , 2);
		write_ifile("\n *** INCOMPLETE ASSEMBLING ***\n");
		}else{
			
			write_ifile("\n *** SUCCESSFUL ASSEMBLING ***\n");
			
			}
	
		
	
	}

void Assembler::write_line(){
	
		write_ifile(line_no ,2);
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
			if(mode == 1){fprintf (fp, "%5x", num );}
			else {fprintf (fp, "%d", num );}	
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
