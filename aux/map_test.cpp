#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int find_key(map<string, int> mp, string label)
{
	map<string, int>::iterator it;
	it = mp.find(label);
	if (it == mp.end())
		return -1;
	return it->second;
}

int check_string(string str)
{

	int len;
	if (str[0] == 'x')
	{
		len = (str.size() - 3) / 2;
		return (len > 0) ? len : 1;
	}
	else if (str[0] == 'c')
	{
		return str.size() - 3;
	}
	else
	{

		return std::count(str.begin(), str.end(), ',') + 1;
	}

	return -1;
}

int main()
{

	cout << check_string("x'adbfdd'") << endl;
	cout << check_string("c'adefes'") << endl;
	cout << check_string("-1,5,2,14,19") << endl;

	// declaring map
	// of char and int
	map<string, int> mp;

	// inserting values
	mp["start"] = 5;
	mp["end"] = 10;
	mp["base"] = 15;
	mp["equ"] = 20;
	mp["org"] = 30;

	// using find() to search for 'b'
	// key found
	// "it" has address of key value pair.
	cout << find_key(mp, "start") << endl;
	cout << find_key(mp, "stars");

	return 0;
}
