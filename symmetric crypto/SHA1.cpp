#include<stdio.h>
#include<openssl/sha.h>
#include <string>
using namespace std;

// 该函数实现SHA1 hash算法功能
// 参数：msg - 输入的字符串
// 返回值：string类型，返回sha1消息摘要结果
string sha1_digest(string msg) {
	if (msg.empty())return "";//输入检查
	//初始化sha上下文
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	//更新哈希计算
	//将数据分块更新到上下文中。这里可以多次调用 SHA1_Update 来处理不同的分块。
	SHA1_Update(&ctx, (const unsigned char*)msg.c_str(), msg.length());
	//获取最终哈希值
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
