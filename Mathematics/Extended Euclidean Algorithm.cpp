#include<stdio.h>

//�ж��Ƿ������Ԫ
int euclid_mod_reverse(int a, int m) {
    // �ж� a, m �Ƿ���
    int a_ = a, m_ = m;
    while (m_ != 0) { // �� m Ϊ 0 ʱ��a �������Լ��
        int tmp = m_;
        m_ = a_ % m_; // ���� m Ϊ a ���� m ������
        a_ = tmp;   // ���� a Ϊԭ���� m
    }
    if (a_ != 1) return 0; // ����������Ԫ

    //����Ԫ
    int m0 = m;  // ����ԭʼģ��
    int x0 = 0, x1 = 1;  // x0 �� x1 ��ʼ��Ϊ 0 �� 1
    int tmp;

    // ��չŷ������㷨
    while (a > 1) {
        // q ����
        int q = a / m;
        tmp = m;

        // ���� m �� a
        m = a % m;
        a = tmp;

        // ���� x0 �� x1
        tmp = x0;
        x0 = x1 - q * x0;
        x1 = tmp;
    }

    // ȷ����ԪΪ����
    if (x1 < 0) x1 += m0;

    return x1;  // ������Ԫ
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