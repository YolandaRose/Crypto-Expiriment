#include<iostream>
using namespace std;

int last_bit(unsigned int s) {//最低位
	return s & 0x0001;//与0x0001进行并运算获得最后一位的比特值
}

int parity_even(unsigned int s) {//偶校验位
	int count = 0;
	while (s) {
		if (s & 0x1)count++;//为1就计数
		s >>= 1;//移位进行下一位判断
	}
	return count % 2 == 0 ? 0 : 1;//奇数返回1，偶数返回0
}
int parity_odd(unsigned int s) {//奇校验位
	//与偶校验相反即可
	return 1 - parity_even(s);
}

unsigned int bbs_rand(int flag) {
	int p = 11, q = 19, s = 3;
	int N = p * q;
	unsigned int bbs_seed = s;
	unsigned int bit_stream = 0;//重要比特位
	for (int i = 0; i < 32; i++) {//32轮迭代
		bbs_seed = (bbs_seed * bbs_seed) % N;
		unsigned int important_bit = 0; // 当前重要比特位
		switch (flag) {
			case 0:important_bit = last_bit(bbs_seed); break;
			case 1:important_bit = parity_odd(bbs_seed); break;
			case 2:important_bit = parity_even(bbs_seed); break;
			default: throw invalid_argument("Invalid flag!"); // 错误处理
		}
		bit_stream = (bit_stream << 1) | important_bit;// 拼接比特流
	}
	return bit_stream;
}