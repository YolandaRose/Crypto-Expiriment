#include<stdio.h>
#include<openssl/rc4.h>
#include <string>
using namespace std;

// 该函数实现RC4加密算法功能
// 参数：data - 输入的明文字符串；secret_key - 密钥
// 返回值：string类型, 返回加密结果。如果输入数据异常，则返回空字符串并退出
string rc4_encrypt(string data, string secret_key) {
	if (data.empty() || secret_key.empty()) {
		return "";//输入检查
	}
	
	//状态数组置换
	RC4_KEY key;
	RC4_set_key(&key, secret_key.length(), (const unsigned char*)secret_key.c_str());
	//加密
	string outdata(data.size(), '\0');//// 分配和输入相同大小的输出缓冲区
	RC4(&key, data.length(), (const unsigned char*)data.c_str(), (unsigned char*)&outdata[0]);
	
	return outdata;
}
// 该函数实现RC4解密算法功能
// 参数：data - 输入的密文字符串；secret_key - 密钥
// 返回值：string类型, 返回解密的结果。如果输入数据异常，则返回空字符串并退出
string rc4_decrypt(string data, string secret_key) {
	return rc4_encrypt(data,secret_key);//复用加密函数
}
