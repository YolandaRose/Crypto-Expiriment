#include "bbs.h"
#include<stdio.h>
#include <ctime>
#include<math.h>
#define R 5

//默认种子为1
unsigned int s = 1;

void lcg_srand(unsigned int seed) {
	//设置线性同余种子
	s = seed;
}

unsigned int lcg_rand() {
	//线性同余伪随机数生成器
	int a = 1103515245, c = 12345, m = pow(2, 31);
	s = ((a * s) + c) % m;
	printf("%u\n", s);
	return s;
}

//BBS算法
unsigned int BBS_Rand(int flag) {
	int p = 11, q = 19, s = 3;//设置固定参数
	int N = p * q;
	//进行R轮迭代
	unsigned int seed[R+1] = { 0 }; int i = 1;
	seed[0] = s % N;
	while (i <=R) {
		seed[i] = (seed[i - 1] * seed[i - 1]) % N;
		i++;
	}
	
	//转为二进制并输出随机数
	char res[R+1] = { 0 };
	switch (flag) {
	case 0:
		//最低比特位
		printf("flag 0 - 最低比特位\n");
		for (i = 1; i <= R; i++) {
			int n = seed[i];
			res[i] = n % 2;	
		}
		break;
	case 1:
		//奇校验位
		printf("flag 1 - 奇校验位\n");
		for (i = 1; i <= R; i++) {
			int k = 0, n = seed[i];
			int count = 0;//1次数统计
			while (n > 0) {
				k = n % 2;
				n = n / 2;
				if (k==1)count += 1;
			}
			if (count % 2 == 0)res[i] = 1;
			else res[i] = 0;
		}
		break;
	case 2:
		//偶校验位
		printf("flag 2 - 偶校验位\n");
		for (i = 1; i <= R; i++) {
			int k = 0, n = seed[i];
			int count = 0;//1次数统计
			while (n > 0) {
				k = n % 2;
				n = n / 2;
				if (k == 1)count += 1;
			}
			if (count % 2 == 0)res[i] = 0;
			else res[i] = 1;
		}
		break;
	default:
		printf("input wrong");
		break;
	}
	
	//转为十进制结果
	int result = 0,base=1;
	for (int j = R; j >0; j--) {
		result+= res[j] * base;
		base *= 2;
	}
	printf("%d\n", result);
	return result;
}

//时间比较
void rand_time() {
	time_t start, end;
	double time_lcg, time_bbs;

	//测量线性同余算法
	start = clock();
	for (int i = 0; i < 10; i++) {
		lcg_rand();
	}
	end = clock();
	time_lcg = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

	//测量BBS算法
	start = clock();
	for (int i = 0; i < 10; i++) {
		bbs_rand(0);
	}
	end = clock();
	time_bbs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

	// 输出两种算法的运行时间
	printf("LCG Algorithm Time: %.2f microseconds\n", time_lcg);
	printf("BBS Algorithm Time: %.2f microseconds\n", time_bbs);
}
int main() {
	printf("last bit unsigned int %u\n", bbs_rand(0));
	printf("parity odd unsigned int %u\n", bbs_rand(1));
	printf("parity even unsigned int %u\n", bbs_rand(2));
	//rand_time();
	return 0;
}