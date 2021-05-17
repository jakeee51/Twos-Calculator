/* 
Author: David J. Morfe
Application Name: Twos Calculator
Functionality Purpose: Apply arithmetic operations to Two's Complement numbers of varying bit sizes
Version: 1.0.2
*/
// 8/17/20

#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>
#include <bitset>

using namespace std;

// Helper function: converts binary string to int for 
signed int BinaryStr2Int(string bin) {
	signed int ret = 0; int bits = bin.length();
	for(int i = 0; i < bits; i++) {
		signed int val = (signed int)pow(2, bits - 1 - i);
		if(i == 0) {
			if(bin[i] == '1')
				ret += -1 * val;
		} else {
			if(bin[i] == '1')
				ret += val;
		}
	}
	return ret;
}

// Helper function for addition & subtraction: remove the padded 0's added by default by bitset<64>
string unpad_binary(string bin, int w) {
	int bits = bin.length(); string ret = "-1";
	int all_one = 0, idx = bin.length() - w - 1;
	if(BinaryStr2Int(bin) == 0) // Return 0 binary with respect to 'w'
		return bin.substr(bin.length() - w);
	for(int i = 0; i < bits; i++) {
		if(bin[i] == '1') {
			all_one += 1;
		} else {
			all_one = 0;
			ret = bin.substr(bin.length() - (w + 1));
			break;
		}
	}
	if(ret.length() > w + 1 )
		ret = ret.substr(1);
	if(all_one == bits) // Return -1 binary equivalent with respect to 'w'
		return bin.substr(bin.length() - w);
	return ret;
}

// Helper function for multiplication & division: remove the padded 0's added by default by bitset<64>
string unpad_binary2(string bin, int w) {
	int bits = bin.length(); string ret = "-1";
	int all_one = 0;
	if(BinaryStr2Int(bin) == 0) // Return 0 binary with respect to 'w'
		return bin.substr(bin.length() - 2 * w);
	if(ret.length() > w + 1)
		ret = ret.substr(1);
	else
		ret = bin;
	if(all_one == bits) // Return -1 binary equivalent with respect to 'w'
		return bin.substr(bin.length() - 2 * w);
	return ret;
}

// Addition
string twos_add(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 + bin2; string ret = "";
	string binary_str = (string)bitset<64>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w); // Truncated Binary
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(BinaryStr2Int(trunc_bin)); // Truncated Decimal
	string bin_rep = unpad_binary(binary_str, w); // Binary Rep
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + dec_trunc;
	return ret;
}

// Subtraction
string twos_sub(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 - bin2; string ret = "";
	string binary_str = (string)bitset<64>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length()-w); // Truncated Binary
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(BinaryStr2Int(trunc_bin)); // Truncated Decimal
	string bin_rep = unpad_binary(binary_str, w); // Binary Rep
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + dec_trunc;
	return ret;
}

// Multiplication
string twos_mult(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 * bin2; string ret = ""; string sign = "";
	string binary_str = (string)bitset<64>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length() - w); // Truncated Binary
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(res % (signed int)pow(2, w)); // Truncated Decimal
	string bin_rep = unpad_binary2(binary_str.substr(binary_str.length() - (2 * w)), w); // Binary Rep
	if(trunc_bin[0] == '1' && dec_trunc[0] != '-')
		sign = "-";
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + sign + dec_trunc;
	return ret;
}

// Division
string twos_div(int w, signed int bin1, signed int bin2) {
	signed int res = bin1 / bin2; string ret = ""; string sign = "";
	string binary_str = (string)bitset<64>(res).to_string();
	string trunc_bin = binary_str.substr(binary_str.length() - w); // Truncated Binary
	string dec_rep = to_string(res); // Decimal Rep
	string dec_trunc = to_string(res % (signed int)pow(2, w)); // Truncated Decimal
	string bin_rep = unpad_binary2(binary_str.substr(binary_str.length() - ( 2 * w)), w); // Binary Rep
	if(trunc_bin[0] == '1' && dec_trunc[0] != '-')
		sign = "-";
	ret = bin_rep + "," + dec_rep + "," + trunc_bin + "," + sign + dec_trunc;
	return ret;
}

// Two's Compliment Operation Handler
string twos_calc(int w, int op, string num1, string num2) {
	string ret;
	signed int bin1 = BinaryStr2Int(num1);
	signed int bin2 = BinaryStr2Int(num2);

	switch(op) {
		case 0:
			ret = twos_add(w, bin1, bin2);
			break;
		case 1:
			ret = twos_sub(w, bin1, bin2);
			break;
		case 2:
			ret = twos_mult(w, bin1, bin2);
			break;
		case 3:
			ret = twos_div(w, bin1, bin2);
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
	if (arith == '+') { // Addition
		op = 0;
	} else if(arith == '-') { // Subtraction
		op = 1;
	} else if(arith == 'x') { // Multiplication
		op = 2;
	} else { // '/' Division
		op = 3;
	}
	cout << twos_calc(w, op, in1, in2) << endl;
	return 0;
}