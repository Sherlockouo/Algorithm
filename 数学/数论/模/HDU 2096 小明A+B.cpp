// HDU 2096
// ���ۣ� ȡģ�Ļ�������
// ע��һ��Ҫ�ֱ�ȡģ�������ȡģ����ΪA��B�ֱ���int32��Χ����ӾͿ��ܳ�int32��

#include <iostream>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	while (t--) {
		int A, B;
		scanf("%d %d", &A, &B);
		printf("%d\n", (A % 100 + B % 100) % 100);
	}

	return 0;
}
