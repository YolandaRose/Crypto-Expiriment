# 乘法逆元

## 欧几里得辗转相除法

1.判断是否存在：a存在关于模m的乘法逆元的充要条件是，a和m的最大公约数为1（或a和m互素），记为gcd(a, m) = 1
2.欧几里得算法：
设a, b, m互质，则有gcd(a, m) = 1
a = q1 *m + r1, r1 >= 0且r1 < m
如果r1 = 0, gcd(a, m) = m；否则, gcd(a, m) = gcd(m, r1)
m = q2*r~1~ + r~2~, r~2· >= 0且r~2~ < r~1~，意味着gcd(m, r1) = gcd(r1, r2)
……辗转相除
r~n-1~ = q~n+1~*r~n~+ 0, 那么gcd(a, m) = gcd(m, r1) = gcd(r1, r2) =…= r~n~

```c
//判断是否存在逆元
int euclid_mod_reverse(int a, int m) {
    // 判断 a, m 是否互素
    int a_ = a, m_ = m;
    while (m_ != 0) { // 当 m 为 0 时，a 就是最大公约数
        int tmp = m_;
        m_ = a_ % m_; // 更新 m 为 a 除以 m 的余数
        a_ = tmp;   // 更新 a 为原来的 m
    }
    if (a_ != 1) return 0; // 不互素无逆元

    //求逆元
    int m0 = m;  // 保存原始模数
    int x0 = 0, x1 = 1;  // x0 和 x1 初始化为 0 和 1
    int tmp;

    // 扩展欧几里得算法
    while (a > 1) {
        // q 是商
        int q = a / m;
        tmp = m;

        // 更新 m 和 a
        m = a % m;
        a = tmp;

        // 更新 x0 和 x1
        tmp = x0;
        x0 = x1 - q * x0;
        x1 = tmp;
    }

    // 确保逆元为正数
    if (x1 < 0) x1 += m0;

    return x1;  // 返回逆元
}
```
# 计算模指数

```c
#include<stdio.h>
#include<math.h>

int main() {
 double a= pow(2, 90);
 double b = 13, c = 0;
 c = (int)a % 13;
 printf("%lf", c);
}
```

pow(2, 90)会溢出，应采用分治法求模。
计算 pow(2,40) 和 pow(2,50)的模，再相乘就是 pow(2,90)的模,可以用以下代码：

eg. pow(5,117) mod 19
117=1+4+16+32+64

pow(5,1) mod 19 = 5;
pow(5,2) mod 19 = [pow(5,1) mod 19] *[pow(5,1) mod 19] =6;
pow(5,4) mod 19 = 17;
pow(5,16) mod 19 = 16;
pow(5,32) mod 19 = 9;
pow(5,64) mod 19 = 5;
