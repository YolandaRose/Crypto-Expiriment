#include<stdio.h>
#include<openssl/rsa.h>

string RSA_signature_signing(string input) {
	load_RSA_keys();
	// ����: input ����Ҫǩ���������ַ���
	// ����ֵ: string����, ����ǩ���Ľ��
}
bool RSA_signature_verify(string message, string
	signature) {
	load_RSA_keys();
	// ����: message ���������ǩ�������signature ����ǩ���Ľ��
	// ����ֵ: bool����, �ɹ�����true, ʧ�ܷ���false
}
