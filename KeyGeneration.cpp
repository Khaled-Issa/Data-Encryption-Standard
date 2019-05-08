#include <iostream>
#include <string>
#include <vector>

using namespace std;

//8*7
vector <int> PermutationChoice1= {
	 57, 49, 41, 33, 25, 17, 9, 
	 1, 58, 50, 42, 34, 26, 18, 
	 10, 2, 59, 51, 43, 35, 27, 
	 19, 11, 3, 60, 52, 44, 36, 
	 63, 55, 47, 39, 31, 23, 15, 
	 7, 62, 54, 46, 38, 30, 22, 
	 14, 6, 61, 53, 45, 37, 29,
	 21, 13, 5, 28, 20, 12, 4 
};

 int LShiftRound[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
 
 //8*6
vector <int> PermutationChoice2 = {
	14, 17, 11, 24, 1, 5,3, 28,
	15, 6, 21, 10, 23, 19, 12, 4, 
	26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40,
	51, 45, 33, 48, 44, 49, 39, 56,
	34, 53, 46, 42, 50, 36, 29, 32 
};



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

const char* bin_char_to_hex4(string c)
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

string bin_str_to_hex_str4(const string& bin)
{
	string hex;

	for (int i = 0; i < bin.length(); i = i + 4) {
		hex += bin_char_to_hex4(bin.substr(i, 4));

	}

	return hex;
}



string permutate(string text, vector <int> box) {

	string textbin = hex_str_to_bin_str(text);
	string textpermuatetd;

	for (int i = 0; i < box.size(); i++) {
		textpermuatetd += (textbin[box[i] - 1]);
	}

	return textpermuatetd;
}

string shiftlift(string input, int shift) {

	string output;
	output =output+ (input.substr(shift, 28) + input.substr(0, shift));
	
	return output;
}

void GenerateKey(string ciphertext) {
//	string ciphertextbin = hex_str_to_bin_str(ciphertext);
	string pc1 = permutate(ciphertext, PermutationChoice1);
	string leftpart = pc1.substr(0, 28);
	string rightpart = pc1.substr(28, 28);
	string pc2;
	//cout << leftpart << "\n" << rightpart;

	for (int i = 0; i < 16; i++) {
		leftpart = shiftlift(leftpart, LShiftRound[i]);
		//cout << leftpart << " ";
		rightpart = shiftlift(rightpart, LShiftRound[i]);
	//	cout << leftpart+rightpart << "\n";
		pc2 = permutate(bin_str_to_hex_str4(leftpart+rightpart), PermutationChoice2);
		 cout<< bin_str_to_hex_str4(pc2)<<"\n";
	}
}




int main()
{

	string key;
	cin >> key;

	GenerateKey(key);
	//cout<<permutate(key, PermutationChoice1);
	//cout << bin_str_to_hex_str4(key);
	//system("pause");
    return 0;
}
