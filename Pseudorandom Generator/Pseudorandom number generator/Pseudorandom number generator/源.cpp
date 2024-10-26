#include<stdio.h>
#include<time.h>
#include<math.h>

//默认种子为1
unsigned int s = 1;

void lcg_srand(unsigned int seed) {
	//设置线性同余种子
	s= seed;
}

unsigned int lcg_rand() {
	//线性同余伪随机数生成器
	int a = 1103515245, c = 12345, m = pow(2, 31);
	s= ((a * s) + c) % m;
	return s;
}

int main() {
	//lcg_srand(123);

	for (int i = 0; i < 10; i++) {
		printf("%u\n", lcg_rand());
	}
	return 0;
}