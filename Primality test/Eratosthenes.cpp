#include "head.h"
bool EratosPrimeTest(unsigned int a) {
	// a: 输入测试正整数
	// 返回: true如果a为素数；false如果a不为素数
	if (a <= 1)return false;//1和负数不是

	static int set[MAX + 1];//筛选集合，0表示非素数，1表示素数
	static bool initialized = false;

	//初始化
	if (!initialized) {
		for (int i = 0; i <= MAX; i++) {
			set[i] = 1;//默认假定为素数
		}
		set[0] = set[1] = 0;//先排除1和0
		for (int i = 2; i <= sqrt(MAX); i++) {//从2开始
			if (set[i]) {//如果i是素数
				for (int j = i * i; j <= MAX; j += i) {
					set[j] = 0;//标记i的倍数为非素数
				}
			}
		}
		initialized = true;
	}

	return set[a];//返回a的判断结果
}
