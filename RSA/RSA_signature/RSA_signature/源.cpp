#include<stdio.h>
#include<openssl/rsa.h>

string RSA_signature_signing(string input) {
	load_RSA_keys();
	// 参数: input 代表要签名的明文字符串
	// 返回值: string类型, 返回签名的结果
}
bool RSA_signature_verify(string message, string
	signature) {
	load_RSA_keys();
	// 参数: message 代表输入的签名结果；signature 代表签名的结果
	// 返回值: bool类型, 成功返回true, 失败返回false
}
