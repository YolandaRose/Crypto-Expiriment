#include "head.h"
#include<stdlib.h>
#include<time.h>

// 计算模指数运算的函数
long long mod_exp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;  // 将基数取模

    while (exponent > 0) {
        // 如果 exponent 是奇数，将当前基数乘入结果
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        // exponent 除以 2，基数平方并取模
        exponent = exponent >> 1;  // 等同于 exponent / 2
        base = (base * base) % modulus;
    }

    return result;
}

int miller_rabin_prime_test(unsigned int n, unsigned int a) {
    if (n < 2 || a >= n)return 0;//n<2不是素数，收到不符合条件的n
    int k = 0;
    unsigned int q = n - 1;

    //寻找k，q
    while (q % 2 == 0) {
        //q为偶数一直除以2
        q /= 2;
        k++;
    }

    //计算a^q mod n = 1
    unsigned int x = mod_exp(a, q, n);
    if (x == 1 || x == n - 1)return 1;//不确定

    //计算a^(2^(j-1) * q) mod n = n-1
    //序列存在一项为n-1,使之后所有项均为1
    for (int i = 0; i < k - 1; i++) {
        x = mod_exp(x, 2, n);//后一项是前一项2倍
        if (x == n - 1)return 1;//不确定
    }

    return 0;//合数
}

char miller_rabin_multiple_test(unsigned int n, unsigned int repeat_times) {
    if (n < 2) return 0;//n<2不是素数
    if (n != 2 && n % 2 == 0)return 0;//合数

    srand(time(NULL));//以当前事件为参数，随机数播种

    for (unsigned int i = 0; i < repeat_times; i++) {
        unsigned int a = 2 + rand() % (n - 3);//生成[2,n-2]的随机数
        if (!miller_rabin_prime_test(n, a)) {
            return 0;//只要有一轮不通过就是合数
        }
    }

    return 1;//均通过依然不确定
}

