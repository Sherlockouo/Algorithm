// HDU 2060
// ̰�ģ����� ˹ŵ�� ����
// �����ǣ�������˺����ٴ���򣬲����ǿ��Ա��ó���������ģ�

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
	int n, a, b;
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &a, &b);
		int v;
		if (n < 6) {
			v = (15 - n) * n / 2;
		}
		else {
			// ����n-6
			// ����6�������� 2/3/4/5/6/7
			v = 1 * (n - 6) + 7 * (n - 6) + 2 + 3 + 4 + 5 + 6 + 7;
		}
		if (v + a >= b) {
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
	}
	return 0;
}