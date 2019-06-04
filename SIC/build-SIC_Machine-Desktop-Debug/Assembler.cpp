//#include "Instruction.cpp"
vector<string> lines;
vector<string> obcd;
vector<int> stad;


/*******
 * 
 * Replace STOI whith another function that handle any format //done
 * Mind ORG  //done
 * check error if label is a register //done 
 * directives not implemented should be ignored with a warning //done
 * 
 * 
 * check spaces in list file
 * org and equ check // done
 * 
 * 
 * reconsider general expression evaluation
 **/
 
 void split_obcd();

class Assembler {
	public:
	int LOCCTR;
	int prev_lctr;
	int prog_len;
	int obcode; //object code per line
	unsigned int line_no;
	bool mode;
	int start_address;
	Statement st;
	map<string,int> SYMTAB;
	map<string,int> OPTAB;
	map<string,int> REGTAB;
	short int st_indx;
	unsigned int errors;
	Assembler();
	void object_file();
	
	void pass1_1();
	void pass1_2();
	void pass2();
	void run();
	void init_optab();
	void init_regtab();
	void print_statement_part();
	void write_ifile(string str);
	void write_ifile(int num , int mode=1);
	void write_line();
	void print_header();
	void print_record();
	void print_end();
	int calc_storage();
	void read_next();
	int get_length();
	int get_equ_org_add();
	int check_operand_format3();
	int calc_operand(const char op , string label , int address);
	int check_complexity();
	int extract_label(string &exp);
	int eval_exp(string exp);
	bool check_indirect();
	bool check_immediate();
	bool check_indexed();
	void objectize();
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
	errors = 0;
	init_optab();
	init_regtab();
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
	if(tab){ errors++; print_error(14); return true;}
		
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
		 if (token[0] == ' '){ errors++; print_error(1); return true;}	
		}
		
		token = split(temp,7,8);
		if(token[0] != ' '){errors++; print_error(7); return true;}
		if(token[1] == ' '){errors++; print_error(2); return true;}
		
		token = split(temp,20,15);
		if(token[2] == ' '){errors++; print_error(3); return true;}
		
	
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
	
	if(temp.size() > 0) return stoi(temp, 0, 16); 
	
	if(oper.size() >0){
		return find_key(SYMTAB , oper);
		}
		return -1;
	
	}
	
		
bool Assembler::have_error(){
	
	if(st.check_comment()){cout<<"check_comment in have error >>"<<st.line<<endl; return false;}
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
	
	
	//if undefined label << symbol
	
	
	if(st.operation.compare("org") == 0 || st.operation.compare("equ") == 0 ){
		int type = check_exp_type(st.operand);
		string exp = st.operand;
		int found;
		if(type ==2){
			//label only
			trim_(exp);
			found = find_key(SYMTAB , exp);
		}else if(type == 3){
			//address
			found = 1;
		}else{
			//label + op + address
			string label_com = extract(exp , "^\\b([a-z]\\w([a-z0-9]){0,3})");
				
				//cout<<"\b";
				//cout<<"label_com in check error "<<label_com<<endl;
			
			found = find_key(SYMTAB , label_com);
		}
		
		if( found == -1){
			print_error(9);
			errors++;
			return true;
			}				
		
				
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
		st_indx = line_no-1;
		
		if(st.labeled) SYMTAB.insert({st.label , LOCCTR});
		
		write_ifile(line_no , 10);
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
			write_ifile(line_no , 10);
			write_ifile("\t\t\t\t");
			write_ifile(st.line);
			write_ifile("\n");
			LOCCTR = 0;
			
			}
			
			pass1_2();
			// else not start :
	}else{
			if(st.formattype == 0){
			
				write_ifile(line_no,10);
				write_ifile("\t\t");
				write_ifile(st.comment);
				write_ifile("\n");
			}else{
				errors++;
				write_ifile("\t\t\t ***** Error :  program must start with 'start' mnemonic\n");
				write_ifile(line_no,10);
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
	string exp = st.operand;
	
	while((st.operation.compare("end") != 0) ){
	
			if(line_no >= lines.size() + 1) break;
			if(st.check_comment()){ st.comment = st.line;
			}else {
		
	prev_lctr = LOCCTR;
	if(!have_error()){
		
			
			//if instruction
		if(st.formattype > 1 && st.formattype < 5){
			
			if(st.labeled){
				
				SYMTAB.insert({st.label , LOCCTR});
				}
				
					
			L = get_length();
			LOCCTR += L;
			
			//get object code if instruction
				
			
			/**if there is a literal in operand field then insert into LITTAB**/
						
		}
		// if directive
		else{
			
			if(st.operation.compare("org") == 0){
			
				
				LOCCTR = get_equ_org_add();
				
				
			}else if(st.operation.compare("equ") == 0){
				
					V= get_equ_org_add();
					SYMTAB.insert({st.label , V});
						
			//end of equ if	
			}else{
				// if directive
				if(st.labeled){SYMTAB.insert({st.label , LOCCTR}); }
				
				if(st.operation.compare("word") == 0){L=3*calc_storage();} 
				else if(st.operation.compare("byte") == 0){
					if(!check_error10()) L=calc_storage();
				} 
				else if(st.operation.compare("resw") == 0) L = 3*stoi(st.operand);
				else if(st.operation.compare("resb") == 0) L = stoi(st.operand);
				
				
				LOCCTR += L;

				
			} 
			
	
			
			
		} //else <directive>
		
		
		write_line();
		objectize();
		read_next();	
			
			
	}else{
		write_line();
		read_next();	
			 
		}//end of else have_error
			
		
	}		
		//write_line();
		//read_next();		
		
		}//end of while
		
	prog_len = prev_lctr - start_address;	
		
	prev_lctr = LOCCTR;
	if(st.operation.compare("end") == 0){
		if(st.labeled) {print_error(5); errors++;	 }
		
		write_line();
		
	}else{print_error(13);errors++; /*write_line();*/}	
	
	print_map();
	
	if(errors){ 
		write_ifile("\n errors :");
		write_ifile(errors , 10);
		write_ifile("\n *** INCOMPLETE ASSEMBLING ***\n");
		write_a("state.txt" , "INCOMPLETE ASSEMBLING");
		}else{
			
			write_ifile("\n *** SUCCESSFUL ASSEMBLING ***\n");
			write_a("state.txt" , "SUCCESSFUL ASSEMBLING");
			
			
		}
	
		
	
	}

void Assembler::write_line(){
	
		write_ifile(line_no ,10);
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
		//write_ifile("\n");
	
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
			 // adding random spaces
				fprintf (fp, "%s", str.c_str() );
				//fprintf (fp, "      ");
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
			switch(mode){
				case 1:
				fprintf (fp, "%x", num );
				break;
				case 2:
				fprintf (fp, "%.2x", num );
				break;
				case 4:
				fprintf (fp, "%.4x", num );
				break;
				case 6:
				fprintf (fp, "%.6x", num );
				break;
				case 10:
				fprintf (fp, "%d", num );
				break;
				
				default:
				fprintf (fp, "%d", num );
				break;
				
				
				}
			}
		
		


  fclose(fp);

	
	
	}


int Assembler::extract_label(string &exp){
	
	
	string label= "";
	 
		//we can replace this by : trim_ then extract ^\\+ , ^- ....
		//extract(exp , ",x");
		//extract(exp,"\\+");
		//extract(exp,"#");
		//extract(exp,"@");
		
		label = extract(exp,"^\\s*(\\b([a-z]){1}\\w([a-z0-9]){0,7})");
		if(label.size() == 0){
			//if label is empty, then try with operator
			label = extract(exp,"^\\s*(\\b([a-z]){1}\\w([a-z0-9]){0,7})\\s*\\+");
			
			}
		
		trim_(label);
		
		exp = label;
		
		//cout<<"****label in extract_label >>" <<label<<"*****"<<endl;
		
		if(label.size() >0){
			return find_key(SYMTAB,label);
			}
		return -1;
		
	
	}
	
int Assembler::get_equ_org_add(){
	
	int typ = check_exp_type(st.operand);
	string exp;
	int V = 0;			
				if(typ ==2){
					exp = st.operand;
					
						
						V= extract_label(exp);
						
						
				}else if(typ ==3){
						if(st.operation.compare("org") == 0){
							V = stoi(st.operand,0,10);
							}else{ V = stoi(st.operand,0,16);}
						
							
				}else{
								
							//then it must be type 1:
							//label + op + address
							
							exp = st.operand;
							string label_com = extract(exp , "^\\b([a-z]\\w([a-z0-9]){0,3})");
							string op = extract(exp,"(\\+|-|\\*|/)");
							
							trim_(exp);

							//check if label is found 
							int label_add = find_key(SYMTAB , label_com);
							if(label_add == -1){
								//then operand isn't defined
								print_error(9);
								errors++;
								
							}else{
								//else calc the operand	
								//eval
								
								switch(op[0]){
								case '+':
								V= label_add + stoi(exp ,0,16);
								break;
								
								case '-':
								V= label_add - stoi(exp ,0,16);
								break;
								
								case '*':
								V= label_add * stoi(exp ,0,16);
								break;
								
								case '/':
								V= label_add / stoi(exp ,0,16);
								break;
								
								default:
								V=0;
								}
									
							}
							
						}
					
	
	
	//end of function
	return V;
	}
bool Assembler::check_indirect(){

	if(st.operand[0] == '@')
		return true;
	return false;
}
bool Assembler::check_immediate(){
	if(st.operand[0] == '#')
		return true;
	return false;
}

bool Assembler::check_indexed(){
	int fnd = st.operand.find(",x");
	
	if( fnd!=-1) return true;
	return false;
	//return st.operand.find(",x") >= 0 ?  true : false;
}

int Assembler::check_operand_format3(){
	/**
	 * if #label return 1
	 * if @label return 2
	 * if label  return 3
	 * if #10    return 4
	 * if @10    return 5
	 * if *		 return 7
	 * else      return -1
	 * 
	 **/
	
	if(st.operand[0] == '#' && !isdigit(st.operand[1])) return 1;
	if(st.operand[0] == '@' && !isdigit(st.operand[1])) return 2;
	if(isalpha(st.operand[0])) return 3;
	if(st.operand[0] == '#' && isdigit(st.operand[1])) return 4;
	if(st.operand[0] == '@' && isdigit(st.operand[1])) return 5;
	if(isdigit(st.operand[0])) return 6;
	if(st.operand.compare("*")==0) return 7;
	 
	return -1;	
	}
	
void Assembler::objectize(){
	
	string exp = st.operand;
	string abs_label;
	
	
	int address = 0;
	
	int opcode;
	
	bool n,i,x,b,p,e;
	
	if( st.formattype == 2){
		//each of r1 and r2 has a certain number
		
		/**
		 * this one is super simple
		 * all we have to calc is : operation and registers values
		 * **/
		// string operand1 = st.operand.substr(0,1);
		 int op1 , op2;
		 //address = 
		 op2 = find_key(REGTAB , st.operand.substr(2,1));
		address += op2;
		
		 op1 = find_key(REGTAB , st.operand.substr(0,1));		 
		 address += (op1<<4);
		 
		 address += (find_key(OPTAB , st.operation)<<8);
		 //printf("address_part3: %x \n",address);
		
		
		 write_ifile(address,4);
		 write_b("ob.txt" , address);
		 //write_a("ob.txt" , "\n");
		 
	}else if(st.formattype == 3){
		x= check_indexed();
		//if(x) cout<<"indexed"<<endl;
		b=0;
		p=1;
		e=0;
		
		// dis = TA - PC
		// address of Label - current LOCCTR (if label)
		//dis = the immediate (if immediate)
		//we need a function that differeniate
		int ll_type = check_operand_format3();
		/**
		 * a function is needed to replace this big
		 * switch this function needs no parameters
		 * 
		 * int get_type(){
		 * return the type
		 * 
		 * 
		 * }
		 * 
		 * 
		 * **/
		
		switch(ll_type){
			case 1 : //#label
			n=0;
			i=1;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);

			address = find_key(SYMTAB,abs_label)- LOCCTR -4294963200; /** fffff000 **/;
			break;
			
			case 2: //@label
			n=1;
			i=0;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);
			
			address = find_key(SYMTAB,abs_label)- LOCCTR -4294963200; /** fffff000 **/
			break;
			
			case 3: //label
			n=1;
			i=1;
			
			address = find_key(SYMTAB,exp)- LOCCTR -4294963200; /** fffff000 **/
			break;
			
			case 4: //#10
			n=0;
			i=1;
			p=0;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);
			
			address = stoi(abs_label , 0, 10);
			break;
			
			case 5: //@10
			n=1;
			i=1;
			p=0;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);
			
			address = stoi(abs_label , 0, 10);
			break;
			
			case 7:
			n=1;
			i=1;
			p=1;
			e=0;
			address = prev_lctr -LOCCTR - 4294963200; /** fffff000 **/
			
			default:
			break;
			}

		//printf("line_no :%d\n",line_no);
		//cout<<st.operation<<endl;
		
		
		//printf("address_part1: %x ",address);

		
		address += (e<<12);
		address += (p<<13);
		address += (b<<14);
		address += (x<<15);
		address += (i<<16);
		address += (n<<17);
		
		//cout<<"\nn\ti\tx\tb\tp\te\n"<<endl;
		//cout<<n<<"\t"<<i<<"\t"<<x<<"\t"<<b<<"\t"<<p<<"\t"<<e<<endl;
		
		opcode = find_key(OPTAB , st.operation);
		opcode = opcode>>2;
		
		address += opcode<<18;
		
		//printf("\taddress is **%x**\n",address);
		
		

		write_ifile(address,6);
		write_b("ob.txt" , address,6);
		//write_a("ob.txt" , "\n");
		 
	}else if(st.formattype == 4){
		//relative addressing no allowed
		
		p=0;
		b=0;
		x= check_indexed();
		e=1;
		string operat;
		
		switch(check_operand_format3()){
		case 1 : //#label
			n=0;
			i=1;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);

			address = find_key(SYMTAB,abs_label);
			break;
			
			case 2: //@label
			n=1;
			i=0;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);
			
			address = find_key(SYMTAB,abs_label);
			break;
			
			case 3: //label
			n=1;
			i=1;
			
			address = find_key(SYMTAB,exp);
			break;
			
			case 4: //#10
			n=0;
			i=1;
			p=0;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);
			
			address = stoi(abs_label , 0, 10);
			break;
			
			case 5: //@10
			n=1;
			i=1;
			p=0;
			
			abs_label = exp;
			abs_label[0] = ' ';
			trim_(abs_label);
			
			address = stoi(abs_label , 0, 10);
			break;
			
			default:
			break;
			}

		//now label is got
		//printf("line_no :%d\n",line_no);
		//cout<<st.operation<<endl;
		
		
		//printf("address_part1: %x ",address);

		
		address += (e<<20);
		address += (p<<21);
		address += (b<<22);
		address += (x<<23);
		address += (i<<24);
		address += (n<<25);
		
		//cout<<"\nn\ti\tx\tb\tp\te\n"<<endl;
		//cout<<n<<"\t"<<i<<"\t"<<x<<"\t"<<b<<"\t"<<p<<"\t"<<e<<endl;
		
		operat = st.operation;
		operat[0] = ' ';
		trim_(operat);
		
		opcode = find_key(OPTAB , operat);
		opcode = opcode>>2;
		
		address += opcode<<26;
		
		//printf("\taddress is **%x**\n",address);
		
		write_ifile(address , 8);
		
		write_b("ob.txt" , address,8);
		//write_a("ob.txt" , "\n");
		
	}else if(st.formattype == 1){
		//directive >> (Word and Resb)
		// check how to implement if word 1,2,3
		
		if(!(st.operation.compare("org"))||!(st.operation.compare("resw"))||!(st.operation.compare("resb"))){
			int lctr;
				write_a("ob.txt" , " ");
				if(!(st.operation.compare("org"))){
						lctr = get_equ_org_add();
					}else{ lctr = LOCCTR; }
				
				stad.push_back(lctr);
			
			}
			
		if(st.operation.compare("byte") == 0){
			
			vector<int> bcode;
			
			if(st.operand[0] == 'c'){
				
				for(unsigned int i=2; i<st.operand.size()-1 ;i++){
					
					//printf("char in ascii : %x\n",st.operand[i]);
					bcode.push_back(st.operand[i]);
					
					//printf("address : %x\n",address);
					
					//should = length*2 -- never mind here
					//write_ifile(address,1);
					
					}
				
				//cout<<"object code of string"<<endl;
								
				for(unsigned int j=0; j<bcode.size() ; j++){
					
					//printf("%x",bcode[j]);
					
					//of length 2
					
					write_ifile(bcode[j] , 1);
					write_b("ob.txt" , bcode[j]);
		 
					}
				
				//write_a("ob.txt" , "\n");
				cout<<endl;
				
				
			}
			
			
			}if(st.operand[0] == 'x'){
				string xb = st.operand;
				xb[0] = ' ';
				xb[1] = ' ';
				xb[xb.size()-1] = ' ';
				trim_(xb);
				
				//cout<<"byte x is : "<<xb<<endl;
				
				//length should be even -- it's ok 
				write_ifile(xb);
				write_a("ob.txt" , xb);
				//write_a("ob.txt" , "\n");
				}
		
		}if(st.operation.compare("word") == 0){
			
			int l = calc_storage();
			//cout<<"storage is : "<<l<<endl;
			int numw;
			if(l == 1){
				numw = stoi(st.operand,0,10);
				if(numw < 0){ numw -= 4278190080; /*ff000000*/}
				//printf("%.6x\n",numw);
				
				write_b("ob.txt" , numw,6);
				//write_a("ob.txt" , "\n");
				write_ifile(numw , 6);
			}else{
				
				
				std::string delimiter = ",";
				string s = st.operand;
				size_t pos = 0;
				std::string token;
				bool first =true;
				while ((pos = s.find(delimiter)) != std::string::npos) {
					token = s.substr(0, pos);
					numw = stoi(token,0,10);
					
					if(numw < 0){ numw -= 4278190080; /*ff000000*/}
					//printf("%.6x\n",numw);
					
					if(!first){write_ifile("\t\t\t\t\t\t\t\t\t\t"); }
					write_ifile(numw , 6);
					write_b("ob.txt" , numw,6);
					//write_a("ob.txt" , "\n");
					
					first = false;
					write_ifile("\n");
					
						s.erase(0, pos + delimiter.length());
				}
					numw = stoi(s,0,10);
					if(numw < 0){ numw -= 4278190080; /*ff000000*/}
					//printf("%.6x\n",numw);
					
					write_b("ob.txt" , numw,6);
					//write_a("ob.txt" , "\n");
					write_ifile("\t\t\t\t\t\t\t\t\t\t");
					write_ifile(numw , 6);
					write_ifile("\n");
				
				}
			
			
		}
	
	write_ifile("\n");
			
		obcode = address;
	//print object code in listfile
	
	}


void Assembler:: init_regtab(){
	
	REGTAB.insert({"a" , 0});
	REGTAB.insert({"x" , 1});
	REGTAB.insert({"l" , 2});
	REGTAB.insert({"b" , 3});
	REGTAB.insert({"s" , 4});
	REGTAB.insert({"t" , 5});
	REGTAB.insert({"f" , 6});
	
}

void Assembler:: init_optab(){
	
	//cout<<"optab initialized"<<endl;
	//initializing optab
	
	OPTAB.insert({"add" , stoi("18",0,16)});
	OPTAB.insert({"addr" , stoi("90",0,16)});
	OPTAB.insert({"comp" , stoi("28",0,16)});
	OPTAB.insert({"compr" , stoi("a0",0,16)});
	OPTAB.insert({"j" , stoi("3c",0,16)});
	OPTAB.insert({"jeq" , stoi("30",0,16)});
	OPTAB.insert({"jgt" , stoi("34",0,16)});
	OPTAB.insert({"jlt" , stoi("38",0,16)});
	OPTAB.insert({"lda" , stoi("00",0,16)});
	OPTAB.insert({"ldb" , stoi("68",0,16)});
	OPTAB.insert({"ldch" , stoi("50",0,16)});
	OPTAB.insert({"ldl" , stoi("08",0,16)});
	OPTAB.insert({"lds" , stoi("6c",0,16)});
	OPTAB.insert({"ldt" , stoi("74",0,16)});
	OPTAB.insert({"ldx" , stoi("04",0,16)});
	OPTAB.insert({"rmo" , stoi("ac",0,16)});
	OPTAB.insert({"sta" , stoi("0c",0,16)});
	OPTAB.insert({"stb" , stoi("78",0,16)});
	OPTAB.insert({"stch" , stoi("54",0,16)});
	OPTAB.insert({"stl" , stoi("14",0,16)});
	OPTAB.insert({"sts" , stoi("7c",0,16)});
	OPTAB.insert({"stt" , stoi("84",0,16)});
	OPTAB.insert({"stx" , stoi("10",0,16)});
	OPTAB.insert({"sub" , stoi("1c",0,16)});
	OPTAB.insert({"subr" , stoi("94",0,16)});
	OPTAB.insert({"tix" , stoi("2c",0,16)});
	OPTAB.insert({"tixr" , stoi("b8",0,16)});
	
	
	}
void Assembler::print_header(){
	int temp = line_no;
	line_no = st_indx;
	read_next();
	//print H
	write_a("objectfile.txt" , "H");
	string prg_name = st.label;
	while(prg_name.size() <6){prg_name.push_back(' ');}
	//print program name
	write_a("objectfile.txt" , prg_name);
	//print starting address
	write_b("objectfile.txt" , stoi(st.operand,0,16),6);
	//print object code length which is zero
	write_b("objectfile.txt" , 0,6);
	write_a("objectfile.txt" , "\n");
	
	line_no = temp;
	}
	
void Assembler::print_end(){
	int temp = line_no;
	line_no = st_indx;
	read_next();
	//print E
	write_a("objectfile.txt" , "E");
	string prg_name = st.label;
	write_b("objectfile.txt" , start_address , 6);
	
	line_no = temp;
	}

void Assembler::print_record(){
	
	for(unsigned int i=0; i<obcd.size(); i++){
		write_a("objectfile.txt" , "T");
		write_b("objectfile.txt" , stad[i],6);
		write_b("objectfile.txt" , obcd[i].size()/2,2);
		write_a("objectfile.txt" , obcd[i]);
		write_a("objectfile.txt" , "\n");
		
		}
	
	}
void Assembler::pass2(){
	print_header();
	split_obcd();
	print_record();
	print_end();
	
	}


void Assembler::run(){
	
	pass1_1();
	pass2();
	}

void split_obcd(){
	get_ob("ob.txt");	
	ltrim(obcd[0]);
	
	string s = obcd[0];
	//cout<<"s = "<<s<<endl;
	std::string delimiter = " ";

	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		obcd.push_back(token);
		s.erase(0, pos + delimiter.length());
	}
	obcd.push_back(s);
	obcd.erase(obcd.begin());
	}
