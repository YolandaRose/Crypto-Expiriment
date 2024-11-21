#include<stdio.h>

//判断是否存在逆元
int ex_gcd(int a, int m, int& x, int& y) {
    if (m == 0) {
        x = 1; y = 0;
        return a;
    }
    int r = ex_gcd(m, a % m, x, y);
    int t = x;
    x = y;
    y = t - a / m * y;
    return r;
}

//扩展欧几里得
int euclid_mod_reverse(int a, int m) {
    // a - 需要求逆元的数
    // m - 模
    // 返回值：std::int
    // 返回值说明：返回a关于m乘法逆元；不存在返回-1
    int x, y;
    int gcd = ex_gcd(a, m, x, y);
    if (gcd != 1) {//如果a和m不互质
        return -1;//逆元不存在
    }
    //确保x为非负
    return (x % m + m) % m;//返回 x 在模 m 下的值
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