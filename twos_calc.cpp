/* 
Author: David J. Morfe
Application Name: Twos Calculator
Functionality Purpose: Apply arithmetic operations to Two's Complement numbers of varying bit sizes
Version: 1.0.1
*/
// 8/17/20

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
	int all_one = 0, idx = bin.length()-w-1;
	if(BinStr2Int(bin) == 0) // Return 0 binary with respect to 'w'
		return bin.substr(bin.length()-w);
	for(int i = 0; i < bits; i++) {
		if(bin[i] == '1') {
			all_one += 1;
		} else {
			all_one = 0;
			ret = bin.substr(bin.length()-(w+1));
			break;
		}
	}
	if(ret.length() > w+1)
		ret = ret.substr(1);
	if(all_one == bits) // Return -1 binary equivalent with respect to 'w'
		return bin.substr(bin.length()-w);
	return ret;
}

string SlimBin2(string bin, int w) {
	int bits = bin.length(); string ret = "-1";
	int all_one = 0;
	if(BinStr2Int(bin) == 0) // Return 0 binary with respect to 'w'
		return bin.substr(bin.length()-2*w);
	if(ret.length() > w+1)
		ret = ret.substr(1);
	else
		ret = bin;
	if(all_one == bits) // Return -1 binary equivalent with respect to 'w'
		return bin.substr(bin.length()-2*w);
	return ret;
}

string TwosAdd(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 + bin2; string ret = "";
	string binary_str = (string)bitset<32>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w);
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(BinStr2Int(trunc_bin)); // Truncated Decimal
	string bin_rep = SlimBin(binary_str, w); // Binary Rep
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + dec_trunc;
	return ret;
}

string TwosSub(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 - bin2; string ret = "";
	string binary_str = (string)bitset<32>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w);
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(BinStr2Int(trunc_bin)); // Truncated Decimal
	string bin_rep = SlimBin(binary_str, w); // Binary Rep
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + dec_trunc;
	return ret;
}

string TwosMult(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 * bin2; string ret = ""; string sign = "";
	string binary_str = (string)bitset<32>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w);
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(res % (signed int)pow(2, w)); // Truncated Decimal
	string bin_rep = SlimBin2(binary_str.substr(binary_str.length()-(2*w)), w); // Binary Rep
	if(trunc_bin[0] == '1' && dec_trunc[0] != '-')
		sign = "-";
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + sign + dec_trunc;
	return ret;
}

string TwosDiv(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 / bin2; string ret = ""; string sign = "";
	string binary_str = (string)bitset<32>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w);
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(res % (signed int)pow(2, w)); // Truncated Decimal
	string bin_rep = SlimBin2(binary_str.substr(binary_str.length()-(2*w)), w); // Binary Rep
	if(trunc_bin[0] == '1' && dec_trunc[0] != '-')
		sign = "-";
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + sign + dec_trunc;
	return ret;
}

string TwosCalc(int w, int op, string num1, string num2) {
	string ret;
	signed int bin1 = BinStr2Int(num1);
	signed int bin2 = BinStr2Int(num2);
	//cout << "bin1 = " << bin1 << endl;
	//cout << "bin2 = " << bin2 << endl;
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
			cout << "Error: Invalid Operation!" << endl;
	}
	return ret;
}

/*
Argument 1: w -> Number of Bits
Argument 2: arith -> Arithmetic Operator
Argument 3: in1 -> Left Operand Binary Number
Argument 4: in2 -> Right Operand Binary Number
*/
int main(int argc, char *argv[]) {
	int op = 4; int w; char arith;
	string in1, in2;
	if(argc == 5) {
		w = stoi(argv[1]);
		arith = (char)*argv[2];
		in1 = argv[3];
		in2 = argv[4];
	}
	if (arith == '+') {
		op = 0;
	} else if(arith == '-') {
		op = 1;
	} else if(arith == 'x') {
		op = 2;
	} else { // / Division
		op = 3;
	}
	cout << TwosCalc(w, op, in1, in2) << endl;
}