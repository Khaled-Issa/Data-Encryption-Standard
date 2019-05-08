#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


const char* hex_char_to_bin(char c)
{

	switch (toupper(c))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	}
}

string hex_str_to_bin_str(const string& hex)
{
	string bin;
	for (unsigned i = 0; i != hex.length(); ++i)
		bin += hex_char_to_bin(hex[i]);
	return bin;
}


const char* hex_bin_to_char(string c)
{

	if (!c.compare("0000")) return "0";
	else if (!c.compare("0001")) return "1";
	else if (!c.compare("0010")) return "2";
	else if (!c.compare("0011")) return "3";
	else if (!c.compare("0100")) return "4";
	else if (!c.compare("0101")) return "5";
	else if (!c.compare("0110")) return "6";
	else if (!c.compare("0111")) return "7";
	else if (!c.compare("1000")) return "8";
	else if (!c.compare("1001")) return "9";
	else if (!c.compare("1010")) return "A";
	else if (!c.compare("1011")) return "B";
	else if (!c.compare("1100")) return "C";
	else if (!c.compare("1101")) return "D";
	else if (!c.compare("1110")) return "E";
	else if (!c.compare("1111")) return "F";
	else return "";
	
}

string bin_str_to_hex_str(const string& bin)
{
	string hex;

	for (int i = 0; i < bin.length(); i = i + 4) {
		hex += hex_bin_to_char(bin.substr(i, 4));

	}

	return hex;
}


string permutate(string pText, vector <int> pBox,int size) {
	string pTextbin = hex_str_to_bin_str(pText);
	string pTextpermuatetd ;

	
	for (int i = 0; i < size; i++) {
		pTextpermuatetd += (pTextbin[pBox[i]-1]);
		
	}

	
	pTextpermuatetd = bin_str_to_hex_str((pTextpermuatetd));
	return pTextpermuatetd;
}


int main()
{
	int oSize;
	cin >> oSize;


	vector <int> pBox(oSize);
	for (int i = 0; i < oSize; i++) {
		cin >> pBox[i];
	}

	int iSize;
	string itopBox;

	cin >> iSize;
	cin >> itopBox;
	

	string result = permutate(itopBox,pBox,oSize);
	cout<<result;
	
	
	
    return 0;
}