# OpenSSL大数运算库

- 头文件`#include<openssl/bn.h>`

## 基础

- 初始化: BN_new
- 回收 ： BN_free

```c
#include <openssl/bn.h>
    int main () {
    BIGNUM *bn;
    bn = BN_new();
    BN_free(bn);
    return 0;
}
```

## 赋值和输出

- 赋值函数：BN_zero、BN_one、BN_set_word…
- 输出函数：BN_print_fp
- 注：BN_print_fp按16进制输出

```c
#include <openssl/bn.h>
int main () {
    BIGNUM *bn;
    bn = BN_new();
    BN_zero(bn);
    BN_print_fp(stdout, bn);
    BN_one(bn);
    BN_print_fp(stdout, bn);
    BN_set_word(1024, bn);
    BN_print_fp(stdout, bn);
    BN_free(bn);
    return 0;
}
```

## 模指数运算

```c++
string mod_exp(string a, string e, string m) {
 // 参数：string类型，求解a^e mod m，表示为10进制数字符串
 // 返回值：string类型，返回计算的结果，表示为10进制数字符串
 //BN_CTX 提供了临时存储，避免频繁分配和释放内存，提高性能。

    BIGNUM* bn_a = BN_new();// 初始化大数a, e, m, r等同理
    BIGNUM* bn_e = BN_new();
    BIGNUM* bn_m = BN_new();
    BIGNUM* r = BN_new();//保存计算结果

    BN_dec2bn(&bn_a, a.c_str());// 将输入的字符串转换为大数
    BN_dec2bn(&bn_e, e.c_str());
    BN_dec2bn(&bn_m, m.c_str());

    BN_CTX* ctx = BN_CTX_new();//初始化辅助变量ctx
    BN_mod_exp(r, bn_a, bn_e, bn_m, ctx);// 计算模指数运算, r为计算结果

    char* number_str = BN_bn2dec(r);//将大数计算结果r转换为十进制字符串

    BN_free(bn_a); BN_free(bn_e); BN_free(bn_m); BN_free(r);
    BN_CTX_free(ctx);
    return number_str;
}
```

## 乘法逆元

```c++
string mod_inverse(string a, string m) {
 // 参数：string类型，求解a关于m的乘法逆元，表示为10进制数字符串
 // 返回值：string类型，返回计算的结果，表示为10进制数字符串
    BIGNUM* bn_a = BN_new();// 初始化大数a, e, m, r等同理
    BIGNUM* bn_m = BN_new();
    BIGNUM* r = BN_new();//保存计算结果

    BN_dec2bn(&bn_a, a.c_str());// 将输入的字符串转换为大数
    BN_dec2bn(&bn_m, m.c_str());

    BN_CTX* ctx = BN_CTX_new();//初始化辅助变量ctx
    BN_mod_inverse(r, bn_a, bn_m, ctx);// 计算乘法逆元, r为计算结果

    char* number_str = BN_bn2dec(r);// 将大数计算结果r转换为十进制字符串

    BN_free(bn_a); BN_free(bn_m); BN_free(r);
    BN_CTX_free(ctx);
    return number_str;
}
```

    
