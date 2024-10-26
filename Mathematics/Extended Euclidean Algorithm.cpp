#include<stdio.h>

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

int main() {
	int a = 0;
	int m = 0;
	printf("请输入a和模m\n");
	scanf_s("%d %d", &a, &m);

	if (euclid_mod_reverse(a,m)) {
		printf("\n%d 关于 mod%d 乘法逆元为 %d ",a,m, euclid_mod_reverse(a, m));
	}else printf("\n%d 关于 mod%d 不存在逆元",a,m);
	
	return 0;
}