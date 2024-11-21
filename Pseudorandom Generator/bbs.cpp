#include<iostream>
using namespace std;

int last_bit(unsigned int s) {//���λ
	return s & 0x0001;//��0x0001���в����������һλ�ı���ֵ
}

int parity_even(unsigned int s) {//żУ��λ
	int count = 0;
	while (s) {
		if (s & 0x1)count++;//Ϊ1�ͼ���
		s >>= 1;//��λ������һλ�ж�
	}
	return count % 2 == 0 ? 0 : 1;//��������1��ż������0
}
int parity_odd(unsigned int s) {//��У��λ
	//��żУ���෴����
	return 1 - parity_even(s);
}

unsigned int bbs_rand(int flag) {
	int p = 11, q = 19, s = 3;
	int N = p * q;
	unsigned int bbs_seed = s;
	unsigned int bit_stream = 0;//��Ҫ����λ
	for (int i = 0; i < 32; i++) {//32�ֵ���
		bbs_seed = (bbs_seed * bbs_seed) % N;
		unsigned int important_bit = 0; // ��ǰ��Ҫ����λ
		switch (flag) {
			case 0:important_bit = last_bit(bbs_seed); break;
			case 1:important_bit = parity_odd(bbs_seed); break;
			case 2:important_bit = parity_even(bbs_seed); break;
			default: throw invalid_argument("Invalid flag!"); // ������
		}
		bit_stream = (bit_stream << 1) | important_bit;// ƴ�ӱ�����
	}
	return bit_stream;
}