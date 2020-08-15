/* 
Author: David J. Morfe
Application Name: Twos Calculator
Functionality Purpose: Apply arithmetic operations to Two's Complement numbers of varying bit sizes
Version: 0.1.0
*/

#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

signed int BinStr2Int(string bin) {
	signed int ret = 0; int bits = bin.length();
	for(int i = 0; i < bits; i++) {
		signed int val = (signed int)pow(2, bits-1-i);
		if(i == 0) {
			if(bin[i] == '1')
				ret += -1*val;
		} else {
			if(bin[i] == '1')
				ret += val;
		}
	}
	return ret;
}

string SlimBin(string bin, int w) {
	int bits = bin.length(); string ret = "-1";
	bool all_one = false;
	for(int i = 0; i < bits; i++) {
		if(bin[i+1] != '1')
			if(bin[i] == '1') {
				ret = bin.substr(i);
				break;
			}
		if(bin[i] == '1') {
			all_one = true;
		} else {
			all_one = false;
			ret = bin.substr(bin.length()-(w+1));
			break;
		}
	}
	if(all_one)
		return bin.substr(bin.length()-w);
	return ret;
}

string TwosAdd(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 + bin2; string ret = "";
	string binary_str = (string)bitset<32>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w);
	ret += SlimBin(binary_str, w); // Binary Rep
	ret += "," + to_string(res); // Decimal Rep
	ret += "," + trunc_bin; // Truncated Binary
	ret += "," + to_string(BinStr2Int(trunc_bin)); // Truncated Decimal
	return ret;
}

string TwosSub(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 - bin2; string ret = "";
	string binary_str = (string)bitset<32>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w);
	ret += SlimBin(binary_str, w); // Binary Rep
	ret += "," + to_string(res); // Decimal Rep
	ret += "," + trunc_bin; // Truncated Binary
	ret += "," + to_string(BinStr2Int(trunc_bin)); // Truncated Decimal
	return ret;
}

string TwosMult(int w, signed int bin1, signed int bin2) {
	return "*";
}

string TwosDiv(int w, signed int bin1, signed int bin2) {
	return "/";
}

string TwosCalc(int w, int op, string num1, string num2) {
	string ret;
	signed int bin1 = BinStr2Int(num1);
	signed int bin2 = BinStr2Int(num2);
	cout << "bin1 = " << bin1 << endl;
	cout << "bin2 = " << bin2 << endl;
	switch(op) {
		case 0:
			ret = TwosAdd(w, bin1, bin2);
			break;
		case 1:
			ret = TwosSub(w, bin1, bin2);
			break;
		case 2:
			ret = TwosMult(w, bin1, bin2);
			break;
		case 3:
			ret = TwosDiv(w, bin1, bin2);
			break;
		default:
			cout << "Error: Invalid Operator!" << endl;
	}
	return ret;
}

int main() {
	const int w = 4; int op;
	const char arith = '-';
	string in1 = "1000";
	string in2 = "0111";
	if (arith == '+') {
		op = 0;
	} else if(arith == '-') {
		op = 1;
	} else if(arith == '*') {
		op = 2;
	} else { // / Division
		op = 3;
	}
	cout << TwosCalc(w, op, in1, in2) << endl;
}