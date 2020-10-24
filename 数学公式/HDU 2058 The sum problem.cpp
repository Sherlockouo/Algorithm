// HDU 2058
// ��ѧ : ��Ԫһ�η��̵���������
// x��ʾ��㣬n��ʾ���䳤��, ��ô��   (x + x+y-1)*y/2 = M;
// 1�� (x + x+y-1)*y Ϊż����
// 2��2x+y-1 �� y �ֱ�Ϊ 2M �����ӣ����ҳ˻�Ϊ 2M��ö�� sqrt(2M) �ڵ����ӣ� 
// STL sort ������С�ںŽ�������

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Intval {
	int l, r;
	Intval(int _l, int _r) : l(_l), r(_r) {}
	Intval() {}

	void Print() {
		printf("[%d,%d]\n", l, r);
	}

	bool operator<(const Intval& o) const {
		return l < o.l;
	}

	bool operator!=(const Intval& o) const {
		return l != o.l || r != o.r;
	}
};
vector <Intval> ans;

void cal(int n, int A, int B, vector <Intval>& ans) {
	// (2x+y-1)*y = 2M
	// 2x + y - 1 = A
	// y = B
	int x = A + 1 - B;
	if (x & 1) return;
	x /= 2;
	int l = x, r = x + B - 1;
	if (x >= 1 && x <= n) {
		if (r >= 1 && r <= n) {
			if (A*B % 2 == 0)
				ans.push_back(Intval(l, r));
		}
	}
}

int n, m;

int main() {
	int i;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		m *= 2;
		ans.clear();

		for (i = 1; i <= sqrt(1.0*m) + 1; ++i) {
			if (m % i == 0) {
				cal(n, i, m / i, ans);
				cal(n, m / i, i, ans);
			}
		}
		sort(ans.begin(), ans.end());
		for (i = 0; i < ans.size(); ++i) {
			if (!i || i && ans[i] != ans[i - 1])
				ans[i].Print();
		}
		puts("");
	}
	return 0;
}