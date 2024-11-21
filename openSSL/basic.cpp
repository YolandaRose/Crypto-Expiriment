#include"bignum.h"
int main() {
	BIGNUM* bn;
	bn = BN_new();//初始化

	BN_zero(bn);//赋值0
	BN_print_fp(stdout, bn);//输出（按16进制）
	printf("\n");

	BN_one(bn);//赋值1
	BN_print_fp(stdout, bn);//输出（按16进制）
	printf("\n");

	BN_set_word(bn, 1024);//赋值1024
	BN_print_fp(stdout, bn);//输出（按16进制）
	printf("\n");

	BN_free(bn);//回收

	string a = "7", m = "96", e = "32";
	cout<<mod_exp(a, e, m)<<endl;
	cout<<mod_inverse(a, m)<<endl;
	return 0;
}