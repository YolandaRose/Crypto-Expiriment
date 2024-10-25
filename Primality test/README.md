# 素性测试

## 基于Eratosthenes筛选法

- Eratosthenes筛选法

目标：产生最小N个素数（例如N=n1/2）
• 不适用于计算某个范围内全部素数
1.取第一个素数2, 划去{2,…, N}中除2以外所有2的倍数
2.大于2的第一个正整数(即3)被认定为素数, 在余下的整数中划去
除3以外所有3的倍数
3.循环此过程直到找到{2, 3,…, N}中的所有素数

- 判断2543是否为素数
1.求平方根：25431/2 ~= 50，确定待筛选集合{2, 3, 4,…, 50}
2.使用Eratosthenes筛选法在集合{2, 3, 4,…, 50}中筛选出所有素
数: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
3.整除判定：2543除以这15个素数，结果都不是整数，因此2543
一定是素数

## Miller-Rabin

通过测试的**不一定**是素数，无法通过测试的一定不是素数。

- 判断n是否是素数步骤：

1.确定整数k和q：n=2^k*q+1，其中q是奇数，k>0
2.随机选择整数a,满足a>1且a<n-1
3.如果a^q mod n=1，则输出“不确定”，否则继续执行第4步
4.如果存在a^(2^j*q) mod n=n-1，则输出“不确定”，否则继续执行第5步
5.返回“合数”

```c
int miller_rabin_prime_test(unsigned int n, unsigned int a) {
    if (n < 2 || a >= n)return 0;//n<2不是素数，收到不符合条件的n
    int k = 0;
    unsigned int q = n - 1;

    //寻找k，q
    while (q % 2 == 0) {
        //q为偶数一直除以2
        q /= 2;
        k++;
    }

    //计算a^q mod n = 1
    unsigned int x = mod_exp(a, q, n);
    if (x == 1 || x == n - 1)return 1;//不确定

    //计算a^(2^(j-1) * q) mod n = n-1
    //序列存在一项为n-1,使之后所有项均为1
    for (int i = 0; i < k - 1; i++) {
        x = mod_exp(x, 2, n);//后一项是前一项2倍
        if (x == n - 1)return 1;//不确定
    }

    return 0;//合数
```

- 二次探测

1.

```c
char miller_rabin_multiple_test(unsigned int n, unsigned int repeat_times) {
    if (n < 2) return 0;//n<2不是素数
    if (n != 2 && n % 2 == 0)return 0;//合数

    srand(time(NULL));//以当前事件为参数，随机数播种

    for (unsigned int i = 0; i < repeat_times; i++) {
        unsigned int a = 2 + rand() % (n - 3);//生成[2,n-2]的随机数
        if (!miller_rabin_prime_test(n, a)) {
            return 0;//只要有一轮不通过就是合数
        }
    }

    return 1;//均通过依然不确定
}
```