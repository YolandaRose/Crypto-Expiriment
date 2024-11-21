    # 对称密码

- 加密解密使用相同密钥
- 优点：加解密速度快，密钥管理简单，适合一对一通信
- 缺点：密钥分发困难，不适合一对多加密传输

## 流密码：RC4

- 使用伪随机数生成器替代一次一密随机密钥
- 处理单位：比特 → 低错误传播
- 思路：先产生状态数组的置换，再进行加密/解密

```c++
RC4_KEY key;
// 异常处理：如果密钥为空，则返回空
int data_length = data.length();
auto buf = new unsigned char[data_length]{};
// 产生K置换状态数组
RC4_set_key(&key,secret_key.length(),secret_key.c_str());
RC4(&key, data_length, data.c_str(), buf); // 加密或解密
// 返回为需加密或解密数据长度的string结果
string result((char *) (buf), data_length);
return result;
```

## 分组密码：DES

- 处理单位：分组 → 扩散
- 基于Feistel网络 → 加解密具有相似性
- 分组密码应用模式：ECB、CBC、CTR → 处理多个分组长度数据

```c++
DES-ECB
DES_cblock key;
DES_string_to_key(secret_key.c_str(), &key); // 将string类型密钥转换为DES内部key
DES_key_schedule ks;
DES_set_key_checked(&key, &ks); // 产生子密钥
const DES_cblock plain_data;
convert_string_to_des_block(plain, plain_data); // 将string明文转换为DES_cblock类型
DES_cblock cipher;
DES_ecb_encrypt(&plain_data, &cipher, &ks, DES_ENCRYPT); // 加密，结果返回至cipher
string result((char *)cipher, sizeof(cipher)); // 返回为加密数据长度的string结果
return result;
```

    
