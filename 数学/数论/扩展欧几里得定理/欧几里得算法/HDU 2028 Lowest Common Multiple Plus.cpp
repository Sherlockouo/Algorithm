// HDU 2028
// ���ۣ����Լ���ļ�Ӧ��
// a,b ��С������ = a*b / a,b ���Լ��
#include <iostream>
using namespace std;

#define LL __int64

LL gcd(LL a, LL b) {
	return b == 0 ? a : gcd(b, a%b);
}

LL lcm(LL a, LL b) {
	return a / gcd(a, b) * b;
}

int main() {
	int n;
	int i;
	while (scanf("%d", &n) != EOF) {
		LL ans = 0;
		for (i = 0; i < n; ++i) {
			LL v;
			scanf("%I64d", &v);
			if (i == 0) {
				ans = v;
			}
			else {
				ans = lcm(ans, v);
			}
		}
		printf("%I64d\n", ans);
	}
	return 0;
}