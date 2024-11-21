#include "head.h"
#include<stdlib.h>
#include<time.h>

// ����ģָ������ĺ���
long long mod_exp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;  // ������ȡģ

    while (exponent > 0) {
        // ��� exponent ������������ǰ����������
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        // exponent ���� 2������ƽ����ȡģ
        exponent = exponent >> 1;  // ��ͬ�� exponent / 2
        base = (base * base) % modulus;
    }

    return result;
}

int miller_rabin_prime_test(unsigned int n, unsigned int a) {
    if (n < 2 || a >= n)return 0;//n<2�����������յ�������������n
    int k = 0;
    unsigned int q = n - 1;

    //Ѱ��k��q
    while (q % 2 == 0) {
        //qΪż��һֱ����2
        q /= 2;
        k++;
    }

    //����a^q mod n = 1
    unsigned int x = mod_exp(a, q, n);
    if (x == 1 || x == n - 1)return 1;//��ȷ��

    //����a^(2^(j-1) * q) mod n = n-1
    //���д���һ��Ϊn-1,ʹ֮���������Ϊ1
    for (int i = 0; i < k - 1; i++) {
        x = mod_exp(x, 2, n);//��һ����ǰһ��2��
        if (x == n - 1)return 1;//��ȷ��
    }

    return 0;//����
}

char miller_rabin_multiple_test(unsigned int n, unsigned int repeat_times) {
    if (n < 2) return 0;//n<2��������
    if (n != 2 && n % 2 == 0)return 0;//����

    srand(time(NULL));//�Ե�ǰ�¼�Ϊ���������������

    for (unsigned int i = 0; i < repeat_times; i++) {
        unsigned int a = 2 + rand() % (n - 3);//����[2,n-2]�������
        if (!miller_rabin_prime_test(n, a)) {
            return 0;//ֻҪ��һ�ֲ�ͨ�����Ǻ���
        }
    }

    return 1;//��ͨ����Ȼ��ȷ��
}

