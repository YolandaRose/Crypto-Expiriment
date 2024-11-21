#include<stdio.h>

//�ж��Ƿ������Ԫ
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

//��չŷ�����
int euclid_mod_reverse(int a, int m) {
    // a - ��Ҫ����Ԫ����
    // m - ģ
    // ����ֵ��std::int
    // ����ֵ˵��������a����m�˷���Ԫ�������ڷ���-1
    int x, y;
    int gcd = ex_gcd(a, m, x, y);
    if (gcd != 1) {//���a��m������
        return -1;//��Ԫ������
    }
    //ȷ��xΪ�Ǹ�
    return (x % m + m) % m;//���� x ��ģ m �µ�ֵ
}

int main() {
	int a = 0;
	int m = 0;
	printf("������a��ģm\n");
	scanf_s("%d %d", &a, &m);

	if (euclid_mod_reverse(a,m)) {
		printf("\n%d ���� mod%d �˷���ԪΪ %d ",a,m, euclid_mod_reverse(a, m));
	}else printf("\n%d ���� mod%d ��������Ԫ",a,m);
	
	return 0;
}