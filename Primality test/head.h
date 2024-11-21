#ifndef HEAD_H
#define MAX 1000000 // 设置最大筛选范围
#include<math.h>
#include<stdbool.h>
bool EratosPrimeTest(unsigned int a);
long long mod_exp(long long base, long long exponent, long long modulus);
int miller_rabin_prime_test(unsigned int n, unsigned int a);
char miller_rabin_multiple_test(unsigned int n, unsigned int repeat_times);
#endif // !HEAD_H
#pragma once