#include"bignum.h"
// 大数求乘法逆元
string mod_inverse(string a, string m) {
	// 参数：string类型，求解a关于m的乘法逆元，表示为10进制数字符串
	// 返回值：string类型，返回计算的结果，表示为10进制数字符串
	BIGNUM* bn_a = BN_new();// 初始化大数a, e, m, r等同理
	BIGNUM* bn_m = BN_new();
	BIGNUM* r = BN_new();//保存计算结果

	BN_dec2bn(&bn_a, a.c_str());// 将输入的字符串转换为大数
	BN_dec2bn(&bn_m, m.c_str());

	BN_CTX* ctx = BN_CTX_new();//初始化辅助变量ctx
	BN_mod_inverse(r, bn_a, bn_m, ctx);// 计算模指数运算, r为计算结果

	char* number_str = BN_bn2dec(r);// 将大数计算结果r转换为十进制字符串

	BN_free(bn_a); BN_free(bn_m); BN_free(r);
	BN_CTX_free(ctx);
	return number_str;
}