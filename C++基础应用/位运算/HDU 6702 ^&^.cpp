// HDU 6702
// ��λ����ԭ��
// ����A��B��Ҫ��һ����С��C��ʹ�� (A^C) & (B^C) ��С
// 
// A �� B �Ķ�Ӧλ�ܹ����������
// 1��ȫΪ1��       C�Ķ�Ӧλ�ṩ1��1��
// 2������һ��0��   C�Ķ�Ӧλ�ṩ0��


#include <iostream>

using namespace std;

unsigned int A, B;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		scanf("%u %u", &A, &B);
		unsigned int C = (A&B);
		if (C == 0) C = 1;
		printf("%u\n", C);
	}
	return 0;
}