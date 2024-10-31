#include<stdio.h>
#include<openssl/des.h>
#include <string>
using namespace std;

// �ú���ʵ��DES�����㷨����
// ������plain - ����������ַ�����secret_key - ��Կ
// ����ֵ��string����, ���ؼ��ܵĽ��
string des_encrypt(string plain, string secret_key) {
	if (plain.empty() || secret_key.empty()) {
		return "";//������
	}
	//��Կת��
	DES_cblock key;
	DES_string_to_key(secret_key.c_str(), &key);
	DES_key_schedule keys;
	DES_set_key_checked(&key, &keys);
	// ������䵽8�ֽڵı���
	string pad_plain = plain;
	while (pad_plain.size() % 8 != 0) {
		pad_plain.push_back('\0');//�� '\0' ���
	}
	//����ռ䱣������
	string ciphertext(pad_plain.size(), '\0');
	//����
	for (size_t i = 0; i < pad_plain.size(); i++) {
		DES_cblock block_in, block_out;
		memcpy(block_in, pad_plain.c_str() + i, 8);
		DES_ecb_encrypt(&block_in, &block_out, &keys, DES_ENCRYPT);
		memcpy(&ciphertext[i], block_out, 8);// ��ÿ����ļ��ܽ���洢��������
	}
	return ciphertext;
}
// �ú���ʵ��DES�����㷨����
// ������cipher - ����������ַ�����secret_key - ��Կ
// ����ֵ��string����, ���ؽ��ܵĽ��
string des_decrypt(string cipher, string secret_key) {
	if (cipher.empty() || secret_key.empty()) {
		return "";//������
	}
	//��Կת��
	DES_cblock key;
	DES_string_to_key(secret_key.c_str(), &key);
	DES_key_schedule keys;
	DES_set_key_checked(&key, &keys);
	//����ռ䱣����ܺ���ı�
	string decrypted_text(cipher.size(), '\0');
	//����
	for (size_t i = 0; i < cipher.size(); i++) {
		DES_cblock block_in, block_out;
		memcpy(block_in, cipher.c_str() + i, 8);
		DES_ecb_encrypt(&block_in, &block_out, &keys, DES_DECRYPT);
	}

	//�Ƴ����
	decrypted_text.erase(decrypted_text.find_last_not_of('\0') + 1);
	return decrypted_text;
}
