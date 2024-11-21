# RSA

- RSA三元组：(N, e, d）
- 大素数：p和q
- e和d为正整数，满足e*d mod (p-1)(q-1) = 1

## 接口

### RSA对象创建

`int RSA_generate_key_ex(RSA *rsa, int bits, BIGNUM *e, BN_GENCB *cb);`
功能：创建⼀对rsa的公钥私钥
参数：RSA密钥指针，密钥bit位数，公钥指数的⼤数形式指针，回调函数
**返回：成功返回1，失败返回0**
e主要有两个取值：第二个更常用

```c
  # define RSA_3 0x3L
  # define RSA_F4 0x10001L
```

注意1：旧接口RSA_generate_key已经被废弃
注意2：回调函数可为null，在key的生成过程中会生成素数，cb会在生成素数之后对其进行处理

### 加密解密

- `int RSA_public_encrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);`

功能：公钥加密，将⻓度为flen的from字符串加密，使用to指针返回密文，返回to的⻓度等于RSA_size(rsa)
参数：明⽂⻓度（flen需要满⾜padding的限制规则），明⽂，密⽂，密钥，padding填充模式
padding填充模式有：
    RSA_PKCS1_PADDING: flen <= RSA_size(rsa) - 11
    RSA_PKCS1_OAEP_PADDING: flen < RSA_size(rsa) - 42
    RSA_NO_PADDING: flen == RSA_size(rsa)
    RSA_SSLV23_PADDING
**返回：成功返回密⽂⻓度，失败返回-1**

- `int RSA_private_decrypt(int flen, const unsigned char *from, unsigned char *to, RSA *rsa, int padding);`

功能：私钥解密，将⻓度为flen的from密文解密，使用to指针返回明文
参数：密⽂⻓度，密⽂，明⽂, 密钥，padding填充模式
padding填充模式：
RSA_PKCS1_PADDING、RSA_PKCS1_OAEP_PADDING、RSA_SSLV23_PADDING、RSA_NO_PADDING
**返回：成功返回明⽂⻓度，失败返回-1**

### 签名验证

- `int RSA_sign(int type, const unsigned char *m, unsigned int m_len, unsigned char *sigret, unsigned int *siglen, RSA *rsa);`

功能：RSA签名，输⼊摘要数据，返回签名sigret
参数：type表⽰⽣成m使⽤的摘要算法类型，m表⽰摘要（hash）数据，m_len表示摘要数据⻓度 sigret是返回签名的指针（指向的内存长度需要等于RSA_size(rsa)），siglen是签名⻓度，rsa是签名者的公钥
type类型：NID_md5、NID_sha、NID_sha1、NID_md5_sha1
注意1：摘要m需要和type类型保持一致，接口内部会针对不同的hash长度做padding
注意2：RSA类型本身可同时存储私钥和公钥信息，根据实际接口使用不同的能力
**返回：成功返回1**

- `int RSA_verify(int type, const unsigned char *m, unsigned int m_len, unsigned char *sigret, unsigned int siglen, RSA *rsa);`

功能：RSA验证签名，输⼊摘要m和签名sigret，返回验签是否通过，即m和解密的sigret是否匹配
参数：type表⽰⽣成m使⽤的摘要算法类型，m表⽰摘要数据，m_len为摘要⻓度，sigret签名
siglen为签名长度，rsa是签名者的公钥
type：NID_md5、NID_sha、NID_sha1、NID_md5_sha1
**返回：成功返回1**

### pem文件

- `RSA *PEM_read_RSAPublicKey(FILE *fp, RSA **x, pem_password_cb *cb, void *u);`
- `RSA *PEM_read_RSAPrivateKey(FILE *fp, RSA **x, pem_password_cb *cb, void *u);`

功能：从pem文件中读取公钥私钥
参数：fp为⽂件，x是输出的RSA类型指针，cb⽤于对加密的pem解密，u是cb函数的参数
注意：当x不为null时，读取的密钥将输出到RSA类型密钥x中；当设置x为null，接口将在返回值中return rsa指针
**返回：nullptr 为读取失败**

```c
int PEM_write_RSAPublicKey(FILE *fp, RSA *x);
int PEM_write_RSAPrivateKey(FILE *fp, RSA *x, const EVP_CIPHER *enc, unsigned
char *kstr, int klen, pem_password_cb *cb, void *u);
```

参数：fp输⼊⽂件，x为待写入的密钥，enc为指定要使用的加密算法使得私钥文件不为明文存储，后续参数均可以设置为null
功能：写⼊公钥私钥
**返回：1 success，0 failed**

## 加解密算法
