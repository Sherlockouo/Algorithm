// HDU 2037
// ̰��
// STL sort С�ں������ص�Ӧ��
// 1. ���ս�βʱ�����������βʱ����ͬ����ʼʱ�������ǰ�棨��ʱ�̣���
// 2. ̰��ö�٣����ص���ȡ�������ұ�ǽ���ʱ�䣻

#include <iostream>
#include <algorithm>
using namespace std;

struct Intval {
	int l, r;
	void Scanf() {
		scanf("%d %d", &l, &r);
	}

	bool operator < (const Intval& other) const {
		if (r == other.r) {
			return l < other.l;
		}
		return r < other.r;
	}
}I[1000];

int main() {
	int n, i;
	while (scanf("%d", &n) != EOF && n) {
		for (i = 0; i < n; ++i) {
			I[i].Scanf();
		}
		sort(I, I + n);
		int end = -1, c = 0;
		for (i = 0; i < n; ++i) {
			if (I[i].l >= end) {
				++c;
				end = I[i].r;
			}
		}
		printf("%d\n", c);
	}
	return 0;
}