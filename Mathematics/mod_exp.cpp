#include "BandC.h"
#include <iostream>
#include <cstdio>


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

int main() {
    long long base, exponent, modulus;

    printf("请输入基数、指数和模数：\n");
    scanf_s("%lld %lld %lld", &base, &exponent, &modulus);

    long long result = mod_exp(base, exponent, modulus);
    printf("%lld^%lld mod %lld = %lld\n", base, exponent, modulus, result);

    //进制转换测试
    int decimal = 7;
    string binary = DecimalToBina(decimal);

    // 使用 C++ 的 cout 打印
    cout << "以下是十进制转二进制：" << endl;
    cout << decimal << " -> " << binary << endl;

    cout << "以下是二进制转十进制：" << endl;
    cout << binary << " -> " << BinaryToDec(binary) << endl;

    return 0;
    return 0;
}
