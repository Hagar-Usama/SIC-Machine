#include "sic.cpp"

int main()
{

	write_dic("listfile.txt", "");
	write_dic("ob.txt", "");
	write_dic("objectfile.txt", "");
	read_file("src.txt");

	string buffer;
	Assembler assembler;

	print_interface();
	getline(cin, buffer);
	if (buffer.compare("1") == 0)
	{
		assembler.mode = false;
	}
	else if (buffer.compare("2") == 0)
	{
		assembler.mode = true;
	}

	assembler.run();

	return 0;
}
