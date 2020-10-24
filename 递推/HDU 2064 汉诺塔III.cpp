// HDU 2064
// �򵥶�̬�滮����ѧ����
// f(n) ����n�����Ӵ�������ƶ������ұߵĴ���
// ��ô�Ȱ� f(n-1) �ƶ���ȥ��Ȼ������ƶ����м�+1���ٰ�f(n-1)�ƶ��������ٰѴ����ƶ������ұߣ��ٰ�f(n-1)�ƶ���ȥ����ɣ�
// ���ԣ�f(n) = 3*f(n-1) + 2�� ���� f(0) = 0;

#include <iostream>
#include <cstring>
using namespace std;

#define LL __int64
#define MAXN 40

LL f[100];

int main() {
	int i;
	int n;
	f[0] = 0;
	for (i = 1; i < MAXN; ++i) f[i] = f[i - 1] * 3 + 2;
	while (scanf("%d", &n) != EOF) {
		printf("%I64d\n", f[n]);
	}

}