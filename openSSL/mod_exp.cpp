#include"bignum.h"
//����ģָ������
string mod_exp(string a, string e, string m) {
	// ������string���ͣ����a^e mod m����ʾΪ10�������ַ���
	// ����ֵ��string���ͣ����ؼ���Ľ������ʾΪ10�������ַ���
	//BN_CTX �ṩ����ʱ�洢������Ƶ��������ͷ��ڴ棬������ܡ�

	BIGNUM* bn_a = BN_new();// ��ʼ������a, e, m, r��ͬ��
	BIGNUM* bn_e = BN_new();
	BIGNUM* bn_m = BN_new();
	BIGNUM* r = BN_new();//���������

	BN_dec2bn(&bn_a, a.c_str());// ��������ַ���ת��Ϊ����
	BN_dec2bn(&bn_e, e.c_str());
	BN_dec2bn(&bn_m, m.c_str());

	BN_CTX* ctx = BN_CTX_new();//��ʼ����������ctx
	BN_mod_exp(r, bn_a, bn_e, bn_m, ctx);//// ����ģָ������, rΪ������

	char* number_str = BN_bn2dec(r);//������������rת��Ϊʮ�����ַ���

	BN_free(bn_a); BN_free(bn_e); BN_free(bn_m); BN_free(r);
	BN_CTX_free(ctx);
	return number_str;
}