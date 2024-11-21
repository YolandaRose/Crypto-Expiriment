#include"bignum.h"
int main() {
	BIGNUM* bn;
	bn = BN_new();//��ʼ��

	BN_zero(bn);//��ֵ0
	BN_print_fp(stdout, bn);//�������16���ƣ�
	printf("\n");

	BN_one(bn);//��ֵ1
	BN_print_fp(stdout, bn);//�������16���ƣ�
	printf("\n");

	BN_set_word(bn, 1024);//��ֵ1024
	BN_print_fp(stdout, bn);//�������16���ƣ�
	printf("\n");

	BN_free(bn);//����

	string a = "7", m = "96", e = "32";
	cout<<mod_exp(a, e, m)<<endl;
	cout<<mod_inverse(a, m)<<endl;
	return 0;
}