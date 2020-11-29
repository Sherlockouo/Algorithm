// HDU 2076
// ��ѧ�⣬����ʱ�ӵ� ʱ��ͷ��� �ļн�

#include <iostream>
#include <cmath>
using namespace std;
int h, m, s;

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &h, &m, &s);
		h %= 12;
		double h_acr = h / 12.0 + m / 720.0 + s / 720.0 / 60.0;
		double m_acr = m / 60.0 + s / 3600.0;
		double v = (h_acr - m_acr) * 360;

		if (v < 0) v = -v;
		if (v > 180) v = 360 - v;
		printf("%d\n", int(v));
	}
	return 0;
}