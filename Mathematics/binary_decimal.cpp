#include "BandC.h"
using namespace std;

//二进制转十进制
int BinaryToDec(string input) {
	int value = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '1') {
			++value;
		}
		value = value << 1;//左移一位
	}
	value = value >> 1;//去除多余的最后一次左移
	return value;
}

//十进制转二进制
string DecimalToBina(int input) {
	string binary = "";
	while (input > 0) {
		if (input % 2 == 1) {
			binary.insert(0, "1");//在原串下标为0的字符前将1添加到字符数组
		}
		else {
			binary.insert(0, "0");//在原串下标为0的字符前将0添加到字符数组
		}
		input = input >> 1;//右移一位，除以2
	}
	return binary;
}
