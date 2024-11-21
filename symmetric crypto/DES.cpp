#include<stdio.h>
#include<openssl/des.h>
#include <string>
using namespace std;

// 该函数实现DES加密算法功能
// 参数：plain - 输入的明文字符串；secret_key - 密钥
// 返回值：string类型, 返回加密的结果
string des_encrypt(string plain, string secret_key) {
	if (plain.empty() || secret_key.empty()) {
		return "";//输入检查
	}
	//密钥转换
	DES_cblock key;
	DES_string_to_key(secret_key.c_str(), &key);
	DES_key_schedule keys;
	DES_set_key_checked(&key, &keys);
	// 明文填充到8字节的倍数
	string pad_plain = plain;
	while (pad_plain.size() % 8 != 0) {
		pad_plain.push_back('\0');//用 '\0' 填充
	}
	//分配空间保存密文
	string ciphertext(pad_plain.size(), '\0');
	//加密
	for (size_t i = 0; i < pad_plain.size(); i++) {
		DES_cblock block_in, block_out;
		memcpy(block_in, pad_plain.c_str() + i, 8);
		DES_ecb_encrypt(&block_in, &block_out, &keys, DES_ENCRYPT);
		memcpy(&ciphertext[i], block_out, 8);// 将每个块的加密结果存储到密文中
	}
	return ciphertext;
}
// 该函数实现DES解密算法功能
// 参数：cipher - 输入的密文字符串；secret_key - 密钥
// 返回值：string类型, 返回解密的结果
string des_decrypt(string cipher, string secret_key) {
	if (cipher.empty() || secret_key.empty()) {
		return "";//输入检查
	}
	//密钥转换
	DES_cblock key;
	DES_string_to_key(secret_key.c_str(), &key);
	DES_key_schedule keys;
	DES_set_key_checked(&key, &keys);
	//分配空间保存解密后的文本
	string decrypted_text(cipher.size(), '\0');
	//解密
	for (size_t i = 0; i < cipher.size(); i++) {
		DES_cblock block_in, block_out;
		memcpy(block_in, cipher.c_str() + i, 8);
		DES_ecb_encrypt(&block_in, &block_out, &keys, DES_DECRYPT);
	}

	//移除填充
	decrypted_text.erase(decrypted_text.find_last_not_of('\0') + 1);
	return decrypted_text;
}
