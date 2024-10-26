#include<stdio.h>
#include<openssl/bn.h>
#include<openssl/rsa.h>
#include <openssl/pem.h>
#include <string>

using namespace std;

//RSA结构体
RSA* rsa = RSA_new();

//密钥载入
RSA* rsa_private_key = NULL;//私钥
RSA* rsa_public_key = NULL;//公钥
bool load_RSA_keys() {
	//读取私钥
	FILE* private_key;
	fopen_s(&private_key,"E:/expi/private.pem", "r");
	if (private_key == NULL)return false;
	rsa_private_key = PEM_read_RSAPrivateKey(private_key, NULL, NULL, NULL);

	//读取公钥
	FILE* public_key;
	fopen_s(&public_key, "E:/expi/public.pem", "r");
	if (public_key == NULL)return false;
	rsa_public_key = PEM_read_RSA_PUBKEY(public_key, NULL, NULL, NULL);
}

//RSA加密
string RSA_Encryption(string plaintext) {
	if (!load_RSA_keys()) {
		printf("failed to load RSA keys\n");
		return "";
	}

	int rsa_len = RSA_size(rsa_public_key);
	unsigned char* cipher = (unsigned char*)malloc(RSA_size(rsa));
	int result = RSA_public_encrypt(plaintext.length(), (unsigned char*)plaintext.c_str(),cipher, rsa_public_key, RSA_PKCS1_OAEP_PADDING);

	if (result == -1) {
		printf("RSA enctyption failed\n");
		free(cipher);
		return "";
	}

	string encrypted((char*)cipher, rsa_len);
	free(cipher);
	return encrypted;
}

//RSA解密
string RSA_Decryption(string ciphertext){
	if (!load_RSA_keys()) {
		printf("failed to load RSA keys\n");
		return "";
	}
	int rsa_len = RSA_size(rsa_private_key);
	unsigned char* decryptedtext = (unsigned char*)malloc(RSA_size(rsa));
	int result = RSA_private_decrypt(ciphertext.length(), (unsigned char*)ciphertext.c_str(), decryptedtext, rsa_private_key, RSA_PKCS1_OAEP_PADDING);
	if (result == -1) {
		printf("RSA denctyption failed\n");
		free(decryptedtext);
		return "";
	}

	string decrypted((char*)decryptedtext, rsa_len);
	free(decryptedtext);
	return decrypted;
}

//RSA数字签名
string RSA_signature_signing(string input) {
	if (!load_RSA_keys()) {
		printf("failed to load RSA keys\n");
		return "";
	}
	int rsa_len = RSA_size(rsa_private_key);
	unsigned char* signature = new unsigned char[RSA_size(rsa)];
	int result = RSA_sign(NID_sha256, (unsigned char*)input.c_str(),input.length(), signature, (unsigned int*)rsa_len, rsa_private_key);
	if (result == -1) {
		printf("RSA sign failed\n");
		return "";
	}
	
	string signatured((char*)signature, result);
	return signatured;
}
bool RSA_signature_verify(string message, string signature) {
	if (!load_RSA_keys()) {
		printf("failed to load RSA keys\n");
		return "";
	}
	// 参数: message 代表输入的签名结果；signature 代表签名的结果
	// 返回值: bool类型, 成功返回true, 失败返回false
	int rsa_len = RSA_size(rsa_private_key);
	
	int result = RSA_verify(NID_sha256, (unsigned char*)message.c_str(), message.length(), (unsigned char*)signature.c_str(), rsa_len, rsa_public_key);
	if (result == -1)return false;
	return true;
}

int main() {
	FILE* fp = NULL;//初始化文件指针
	fopen_s(&fp, "E:/expi/number.txt", "r");
	if (fp==NULL) {// 判断文件是否能正常打开
		printf("file open failed!\n");
		return 1;
	}
	//放入plaintext
	string plaintext;
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		plaintext += buffer;
	}
	fclose(fp);
	//RSA加密解密
	printf("The plaintext:\n%s\n", plaintext.c_str());
	string ciphertext = RSA_Encryption(plaintext);
	printf("Encrypt the plaintext:\n%s\n", ciphertext.c_str());
	printf("Decrypt the ciphertext:\n%s\n", RSA_Decryption(ciphertext).c_str());
	//RSA数字签名
	string signature = RSA_signature_signing(plaintext);
	bool verify = RSA_signature_verify(plaintext, signature);
	printf("Signature sign:\n%s\n", signature.c_str());
	printf("Verify signature:\n%s\n", verify? "true" : "false");
	return 0;
}
