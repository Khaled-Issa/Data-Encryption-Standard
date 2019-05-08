#include <iostream>
#include <string>
#include <vector>

using namespace std;

//[8][8]
vector <int> InitialPermutation = {
	58, 50, 42, 34, 26, 18, 10, 2 ,
	60, 52, 44, 36, 28, 20, 12, 4 ,
	62, 54, 46, 38, 30, 22, 14, 6 ,
	64, 56, 48, 40, 32, 24, 16, 8 ,
	57, 49, 41, 33, 25, 17, 9, 1 ,
	59, 51, 43, 35, 27, 19, 11, 3 ,
	61, 53, 45, 37, 29, 21, 13, 5 ,
	63, 55, 47, 39, 31, 23, 15, 7
};

//8*7
vector <int> PermutationChoice1 = {
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

vector<int> ExpansionPermutation = {
	32, 1, 2, 3, 4, 5 ,
	4, 5, 6, 7, 8, 9 ,
	8, 9, 10, 11, 12, 13 ,
	12, 13, 14, 15, 16, 17 ,
	16, 17, 18, 19, 20, 21 ,
	20, 21, 22, 23, 24, 25 ,
	24, 25, 26, 27, 28, 29 ,
	28, 29, 30, 31, 32, 1
};

int sbox[8][4][16] = {
	{
		{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
		{ 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
		{ 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
		{ 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }
	},

	{
		{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
		{ 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
		{ 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
		{ 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }
	},

	{
		{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
		{ 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
		{ 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
		{ 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }
	},

	{
		{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
		{ 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
		{ 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
		{ 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }
	},

	{
		{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
		{ 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
		{ 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
		{ 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }
	},

	{
		{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
		{ 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
		{ 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
		{ 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }
	},

	{
		{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
		{ 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
		{ 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
		{ 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }
	},

	{
		{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
		{ 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
		{ 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
		{ 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }
	}
};

//Permutation[4][8]
vector<int> PermutationFunction = {
	16, 7, 20, 21 , 29, 12, 28, 17,
	1, 15, 23, 26 ,5 , 18, 31, 10,
	2, 8, 24, 14 , 32, 27, 3, 9,
	19, 13, 30, 6 ,22, 11, 4, 25
};

//[8][8]
vector <int> InverseInitPermutation = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
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

const int bin_char_to_dec4(string c)
{

	if (!c.compare("0000")) return 0;
	else if (!c.compare("0001")) return 1;
	else if (!c.compare("0010")) return 2;
	else if (!c.compare("0011")) return 3;
	else if (!c.compare("0100")) return 4;
	else if (!c.compare("0101")) return 5;
	else if (!c.compare("0110")) return 6;
	else if (!c.compare("0111")) return 7;
	else if (!c.compare("1000")) return 8;
	else if (!c.compare("1001")) return 9;
	else if (!c.compare("1010")) return 10;
	else if (!c.compare("1011")) return 11;
	else if (!c.compare("1100")) return 12;
	else if (!c.compare("1101")) return 13;
	else if (!c.compare("1110")) return 14;
	else if (!c.compare("1111")) return 15;


}

string bin_str_to_dec_str(const string& bin)
{
	string dec;

	for (int i = 0; i < bin.length(); i = i + 4) {
		dec += bin_char_to_dec4(bin);

	}

	return dec;
}

const int bin_char_to_dec2(string c)
{

	if (!c.compare("00")) return 0;
	else if (!c.compare("01")) return 1;
	else if (!c.compare("10")) return 2;
	else if (!c.compare("11")) return 3;


}

string bin_str_to_dec_str2(const string& bin)
{
	string hex;

	for (int i = 0; i < bin.length(); i = i + 4) {
		hex += bin_char_to_dec2(bin);

	}

	return hex;
}

const char* dec_int_to_bin(int c)
{

	switch (toupper(c))
	{
	case 0: return "0000";
	case 1: return "0001";
	case 2: return "0010";
	case 3: return "0011";
	case 4: return "0100";
	case 5: return "0101";
	case 6: return "0110";
	case 7: return "0111";
	case 8: return "1000";
	case 9: return "1001";
	case 10: return "1010";
	case 11: return "1011";
	case 12: return "1100";
	case 13: return "1101";
	case 14: return "1110";
	case 15: return "1111";
	}
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
	output = output + (input.substr(shift, 28) + input.substr(0, shift));

	return output;
}

string xxor(string in1, string in2) {
	string output;
	for (int i = 0; i < in2.length(); i++) {
		if (in1[i] == in2[i]) {
			output = output + "0";
		}
		else {
			output = output + "1";
		}
	}
	return output;
}

string s_box(string bininput) {
	string osbox[8];
	string row;
	string column;
	string result;


	for (int i = 0; i < 8; i++) {
		osbox[i] = (bininput).substr(i * 6, 6);

		row = osbox[i].substr(0, 1) + osbox[i].substr(5, 1);

		column = osbox[i].substr(1, 4);

		result += (dec_int_to_bin((sbox[i][bin_char_to_dec2(row)][bin_char_to_dec4(column)])));

	}

	return result;
}



void encrypt(string ct, string k, int n) {

	string ip;	                                       string pc1 = permutate(k, PermutationChoice1);
	string L;                                          string C = pc1.substr(0, 28);
	string R;                                          string D = pc1.substr(28, 28);
	string ep;                                         string pc2;
	string F;                                          string keyno[16];
	string S;
	string pf;
	string result;
	string iip;

	if (n == 0) { cout << ct; }

	for (int i = 0; i < 16; i++) {

		C = shiftlift(C, LShiftRound[i]);
		D = shiftlift(D, LShiftRound[i]);
		pc2 = permutate(bin_str_to_hex_str4(C + D), PermutationChoice2);
		keyno[i] = pc2;

	}


	for (int i = 0; i < n; i++) {
		ip = permutate(ct, InitialPermutation);
		L = ip.substr(0, 32);
		R = ip.substr(32, 32);
	

		for (int j = 0; j < 16; j++) {

			ep = permutate(bin_str_to_hex_str4(R), ExpansionPermutation);
	
			F = xxor(ep, keyno[15-j]);
		
			S = s_box(F);
			
			pf = permutate(bin_str_to_hex_str4(S), PermutationFunction);
	

			result = xxor(pf, L);
			

			L = R;	
			R = result;
			

		}

		iip = permutate(bin_str_to_hex_str4(R + L), InverseInitPermutation);
		ct = bin_str_to_hex_str4(iip);
	}

	cout << bin_str_to_hex_str4(iip);
}





int main()
{
	string cipherText;
	string key;
	int nofrounds;

	cin >> key >> cipherText >> nofrounds;


	encrypt(cipherText, key, nofrounds);


	
	return 0;
}