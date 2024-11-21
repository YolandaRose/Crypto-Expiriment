#include<stdio.h>
#include<openssl/sha.h>
#include <string>
using namespace std;

// �ú���ʵ��SHA1 hash�㷨����
// ������msg - ������ַ���
// ����ֵ��string���ͣ�����sha1��ϢժҪ���
string sha1_digest(string msg) {
	if (msg.empty())return "";//������
	//��ʼ��sha������
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	//���¹�ϣ����
	//�����ݷֿ���µ��������С�������Զ�ε��� SHA1_Update ������ͬ�ķֿ顣
	SHA1_Update(&ctx, (const unsigned char*)msg.c_str(), msg.length());
	//��ȡ���չ�ϣֵ
	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1_Final(hash, &ctx);

	string hash_string;
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
		char buf[3];
		snprintf(buf, sizeof(buf), " %02x", hash[i]);
		hash_string += buf;
	}
	return hash_string;
}
