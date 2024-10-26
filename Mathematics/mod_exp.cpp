#include <stdio.h>

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

int main() {
    long long base, exponent, modulus;

    printf("�����������ָ����ģ����\n");
    scanf_s("%lld %lld %lld", &base, &exponent, &modulus);

    long long result = mod_exp(base, exponent, modulus);
    printf("%lld^%lld mod %lld = %lld\n", base, exponent, modulus, result);

    return 0;
}
