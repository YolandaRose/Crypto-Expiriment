#include<stdio.h>
#include<openssl/rc4.h>
#include <string>
using namespace std;

// �ú���ʵ��RC4�����㷨����
// ������data - ����������ַ�����secret_key - ��Կ
// ����ֵ��string����, ���ؼ��ܽ����������������쳣���򷵻ؿ��ַ������˳�
string rc4_encrypt(string data, string secret_key) {
	if (data.empty() || secret_key.empty()) {
		return "";//������
	}
	
	//״̬�����û�
	RC4_KEY key;
	RC4_set_key(&key, secret_key.length(), (const unsigned char*)secret_key.c_str());
	//����
	string outdata(data.size(), '\0');//// �����������ͬ��С�����������
	RC4(&key, data.length(), (const unsigned char*)data.c_str(), (unsigned char*)&outdata[0]);
	
	return outdata;
}
// �ú���ʵ��RC4�����㷨����
// ������data - ����������ַ�����secret_key - ��Կ
// ����ֵ��string����, ���ؽ��ܵĽ����������������쳣���򷵻ؿ��ַ������˳�
string rc4_decrypt(string data, string secret_key) {
	return rc4_encrypt(data,secret_key);//���ü��ܺ���
}
