#include "BandC.h"
using namespace std;

//������תʮ����
int BinaryToDec(string input) {
	int value = 0;
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '1') {
			++value;
		}
		value = value << 1;//����һλ
	}
	value = value >> 1;//ȥ����������һ������
	return value;
}

//ʮ����ת������
string DecimalToBina(int input) {
	string binary = "";
	while (input > 0) {
		if (input % 2 == 1) {
			binary.insert(0, "1");//��ԭ���±�Ϊ0���ַ�ǰ��1��ӵ��ַ�����
		}
		else {
			binary.insert(0, "0");//��ԭ���±�Ϊ0���ַ�ǰ��0��ӵ��ַ�����
		}
		input = input >> 1;//����һλ������2
	}
	return binary;
}
