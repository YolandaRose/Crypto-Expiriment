# 素性测试

## 基于Eratosthenes筛选法

- Eratosthenes筛选法

目标：产生最小N个素数（例如N=n^1/2^）

- **不适用于计算某个范围内全部素数**

1. 取第一个素数2, 划去{2,…, N}中除2以外所有2的倍数
2. 大于2的第一个正整数(即3)被认定为素数, 在余下的整数中划去
除3以外所有3的倍数
3. 循环此过程直到找到{2, 3,…, N}中的所有素数

- 判断2543是否为素数

1. 求平方根：25431/2 ~= 50，确定待筛选集合{2, 3, 4,…, 50}
2. 使用Eratosthenes筛选法在集合{2, 3, 4,…, 50}中筛选出所有素
数: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
3. 整除判定：2543除以这15个素数，结果都不是整数，因此2543
一定是素数

- 实际算法

1. prime_test 函数：
首先，检查 a 是否小于等于1，返回 false（因为1和负数不是素数）。
通过一个静态数组 set 来存储素数的筛选结果，初始时假定所有数为素数。
只在第一次调用时执行筛选算法（埃拉托色尼筛法），筛选出小于等于 MAX 的所有素数。
如果 a 小于等于 MAX，直接通过 set[a] 来判断该数是否为素数。
2. 筛选算法：
通过数组 `set` 来标记素数。
使用Eratosthenes筛法从2开始，逐个标记倍数为非素数，直到 `sqrt(MAX)` 为止。

```c
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define MAX 1000000 // 设置最大筛选范围

bool prime_test(unsigned int a) {
 // a: 输入测试正整数
 // 返回: true如果a为素数；false如果a不为素数
 if (a <= 1)return false;//1和负数不是

 static int set[MAX + 1];//筛选集合，0表示非素数，1表示素数
 static bool initialized = false;

 //初始化
 if (!initialized) {
  for (int i = 0; i <= MAX; i++) {
   set[i] = 1;//默认假定为素数
  }
  set[0] = set[1] = 0;//先排除1和0
  for (int i = 2; i <= sqrt(MAX); i++) {//从2开始
   if (set[i]) {//如果i是素数
    for (int j = i * i; j <= MAX; j += i) {
     set[j] = 0;//标记i的倍数为非素数
    }
   }
  }
  initialized = true;
 }

 return set[a];//返回a的判断结果
}
```

## Miller-Rabin

通过测试的**不一定**是素数，无法通过测试的一定不是素数。

- **理论基础：费马小定理 `a^(p-1)^ mod p = 1`**
  所以我们会思考，这个定理是否可以反过来使用？
  很遗憾，答案是不行，因为存在一些合数满足这个等式。
  这些合数被称为费马伪素数，例如最小的费马伪素数为341。
  那我们又考虑，如果多随机选取几个a的话能否提高正确率？
  是的，通过多选取几个底数，我们很大程度上降低了错误的概率，比如341就成功被筛去了。
  但仍旧存在极少的一些合数，即便遍历 [2, p-1] 的每一个数字作为底数，也无法筛去。
  这样的合数被称为卡迈克尔数，在一亿内有255个，最小的卡迈克尔数为561。
  若 n 为卡迈克尔数，则 2^n^ - 1 也是卡迈克尔数，故其个数是无穷的。

- 判断n是否是素数步骤：
1.确定整数k和q：n=2^k^*q+1，其中q是奇数，k>0
2.随机选择整数a,满足a>1且a<n-1
3.如果a^q^ mod n=1，则输出“不确定”，否则继续执行第4步

```c
// 判定a^q mod n ?= 1, 即temp ?= 1
for(int i=1;i<q;i++){
    temp = (unsigned long long)(temp *a) % n;
}
if(temp == 1)return 1;//不确定
```

4.如果存在a^(2^^j^^*q)^ mod n=n-1，则输出“不确定”，否则继续执行第5步

```c
// 判定存在a^[(2^j-1)*q] mod n ?= n-1
for(int i=1;i<k && temp != (n-1); i++){//只要有一个满足，后面都是1
    temp = (unsigned long long)(temp * temp) % n;
}
if(temp == n-1)return 1;//不确定
```

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

- **二次探测定理**
1.单单费马小定理行不通，所以我们考虑引入新的定理来提高检测的正确性。
2.二次探测定理：对于质数p, 若x^2^ mod p = 1, 则小于p的解只有两个，x~1~ = 1, X~2~ = P-1
3.定理证明：
   x^2^ - 1 mod p = 0 ------>  (x+1)(x-1) mod p = 0
   故(x+1)(x-1)整除p，又因为p是质数，故要么(x+1)(x-1)=0，要么(x+1)(x-1)是p的倍数，可得唯二解

```c
int miller_rabin_multiple_test(unsigned int n, unsigned int repeat_times) {
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

    
