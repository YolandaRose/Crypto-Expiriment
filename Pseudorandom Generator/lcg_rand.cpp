#include<stdio.h>
#include<time.h>
#include<math.h>

//Ĭ������Ϊ1
unsigned int s = 1;

void lcg_srand(unsigned int seed) {
	//��������ͬ������
	s= seed;
}

unsigned int lcg_rand() {
	//����ͬ��α�����������
	int a = 1103515245, c = 12345, m = pow(2, 31);
	s= ((a * s) + c) % m;
	return s;
}

int main() {
	//ϵͳʱ����Ϊ����
	lcg_srand(time(NULL));

	for (int i = 0; i < 10; i++) {
		printf("%u\n", lcg_rand());
	}
	return 0;
}