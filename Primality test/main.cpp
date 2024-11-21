#include "head.h"
#include<stdio.h>

//���Ը�����Ч��
int main() {
    unsigned int num;
    printf("Enter a number to test for primality: ");
    scanf_s("%u", &num);
    //Eratosthenes
    printf("\nEratosthenes Prime Test\n ");
    if (EratosPrimeTest(num)) {
        printf("%u is a prime number.\n", num);
    }
    else {
        printf("%u is not a prime number.\n", num);
    }

    //Miller-Rabin
    printf("\nMiller-Rabin Prime Test\n ");
    int repeat_times = 0;
    printf("Please input n repeat_times:");
    scanf_s("%d", &repeat_times);
    if (miller_rabin_multiple_test(num, repeat_times)) {
        printf("\n%d ����������\n", num);
    }
    else  printf("\n%d ��������\n", num);
    return 0;
}