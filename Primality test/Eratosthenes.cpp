#include "head.h"
bool EratosPrimeTest(unsigned int a) {
	// a: �������������
	// ����: true���aΪ������false���a��Ϊ����
	if (a <= 1)return false;//1�͸�������

	static int set[MAX + 1];//ɸѡ���ϣ�0��ʾ��������1��ʾ����
	static bool initialized = false;

	//��ʼ��
	if (!initialized) {
		for (int i = 0; i <= MAX; i++) {
			set[i] = 1;//Ĭ�ϼٶ�Ϊ����
		}
		set[0] = set[1] = 0;//���ų�1��0
		for (int i = 2; i <= sqrt(MAX); i++) {//��2��ʼ
			if (set[i]) {//���i������
				for (int j = i * i; j <= MAX; j += i) {
					set[j] = 0;//���i�ı���Ϊ������
				}
			}
		}
		initialized = true;
	}

	return set[a];//����a���жϽ��
}
