// HDU 2039
// ��ѧ
// ����������֮�ʹ��ڵ�����
// STL sort ����Ӧ��
// ע�⸡�����������⣬�� <= ���� > �ж�

#include <iostream>
#include <algorithm>
using namespace std;

double a[3];

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%lf %lf %lf", &a[0], &a[1], &a[2]);
		sort(a, a + 3);
		printf("%s\n", a[0] + a[1] <= a[2] ? "NO" : "YES");
	}
	return 0;
}