#include <iostream>
#include <typeinfo>
#include <string>
#include <cmath>

using namespace std;

signed int BinStr2Int(string bin) {
	signed int ret = -1; int sign = 1;
	for(int i = 0; i < bin.length(); i++) {
		if(i == 0)
			sign = -1;
		if(bin[i] == '0') {
			;
		} else {
			break;
		}
	}
	return sign*ret;
}

string TwosAdd(int w, signed int bin1, signed int bin2) {
	return "+";
}

string TwosSub(int w, signed int bin1, signed int bin2) {
	return "-";
}

string TwosMult(int w, signed int bin1, signed int bin2) {
	return "*";
}

string TwosDiv(int w, signed int bin1, signed int bin2) {
	return "/";
}

string TwosCalc(int w, int op, string num1, string num2) {
	string ret = "a";
	signed int bin1 = BinStr2Int(num1);
	signed int bin2 = BinStr2Int(num2);
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
	const int w = 3; int op;
	const char arith = '+';
	if (arith == '+') {
		op = 0;
	} else if(arith == '-') {
		op = 1;
	} else if(arith == '*') {
		op = 2;
	} else {
		op = 3;
	}
	string in1 = "101";
	string in2 = "010";
	cout << TwosCalc(w, op, in1, in2) << endl;;
}