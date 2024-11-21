#include "bbs.h"
#include<stdio.h>
#include <ctime>
#include<math.h>
#define R 5

//Ĭ������Ϊ1
unsigned int s = 1;

void lcg_srand(unsigned int seed) {
	//��������ͬ������
	s = seed;
}

unsigned int lcg_rand() {
	//����ͬ��α�����������
	int a = 1103515245, c = 12345, m = pow(2, 31);
	s = ((a * s) + c) % m;
	printf("%u\n", s);
	return s;
}

//BBS�㷨
unsigned int BBS_Rand(int flag) {
	int p = 11, q = 19, s = 3;//���ù̶�����
	int N = p * q;
	//����R�ֵ���
	unsigned int seed[R+1] = { 0 }; int i = 1;
	seed[0] = s % N;
	while (i <=R) {
		seed[i] = (seed[i - 1] * seed[i - 1]) % N;
		i++;
	}
	
	//תΪ�����Ʋ���������
	char res[R+1] = { 0 };
	switch (flag) {
	case 0:
		//��ͱ���λ
		printf("flag 0 - ��ͱ���λ\n");
		for (i = 1; i <= R; i++) {
			int n = seed[i];
			res[i] = n % 2;	
		}
		break;
	case 1:
		//��У��λ
		printf("flag 1 - ��У��λ\n");
		for (i = 1; i <= R; i++) {
			int k = 0, n = seed[i];
			int count = 0;//1����ͳ��
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
		//żУ��λ
		printf("flag 2 - żУ��λ\n");
		for (i = 1; i <= R; i++) {
			int k = 0, n = seed[i];
			int count = 0;//1����ͳ��
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
	
	//תΪʮ���ƽ��
	int result = 0,base=1;
	for (int j = R; j >0; j--) {
		result+= res[j] * base;
		base *= 2;
	}
	printf("%d\n", result);
	return result;
}

//ʱ��Ƚ�
void rand_time() {
	time_t start, end;
	double time_lcg, time_bbs;

	//��������ͬ���㷨
	start = clock();
	for (int i = 0; i < 10; i++) {
		lcg_rand();
	}
	end = clock();
	time_lcg = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

	//����BBS�㷨
	start = clock();
	for (int i = 0; i < 10; i++) {
		bbs_rand(0);
	}
	end = clock();
	time_bbs = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

	// ��������㷨������ʱ��
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