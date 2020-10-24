// HDU 5908
// ö�ٴ� + ��ϣ
// ö�����п��ܵ� k��Ȼ����������hash��
// ǰk��Ԫ����1����ϣ������n-k��Ԫ���õ�2����ϣ��ÿk��Ԫ���ж�һ�Σ�

#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 100010

int Hash[2][MAXN];
int sta[MAXN];
int n, a[MAXN];

bool check(int per, int tot) {
	// per: ÿ�γ���
	// tot: �ܹ�����
	memset(Hash, 0, sizeof(Hash));
	int i, j;

	// ��һ�η��� Hash[0] ��
	for (i = 1; i <= per; ++i) {
		++Hash[0][a[i]];
	}

	for (i = 2; i <= tot; ++i) {
		// �� i �ηŵ� Hash[1] ��
		for (j = 1; j <= per; ++j) {
			++Hash[1][a[(i - 1)*per + j]];
		}

		for (j = 1; j <= per; ++j) {
			if ((i - 1) * Hash[0][a[j]] != Hash[1][a[j]]) {
				return false;
			}
		}
	}
	return true;
}


int main() {
	int t;
	int i;
	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		for (i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		sta[0] = 0;
		for (i = 1; i <= n; ++i) {
			if (n % i == 0) {
				if (check(i, n / i)) {
					sta[++sta[0]] = i;
				}
			}
		}

		for (i = 1; i <= sta[0]; ++i) {
			if (i > 1) printf(" ");
			printf("%d", sta[i]);
		}
		puts("");
	}
	return 0;
}