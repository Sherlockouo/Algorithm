/*
	̰��
	
	��Ϊ 2���� ��������֮ǰ���� ����С���ݵĺͣ����ԴӴ������С���ߣ�ֻҪ�зǵľ�ֱ���˳����н��㼴��
*/

#include <iostream>

using namespace std;

#define MAXN 10010
#define MAXM 32

int mat[MAXN][MAXM];
int dow[MAXN];

int gcd(int a, int b) {
	return !b ? a : gcd(b, a%b);
}

int main() {
	int n, m;
	int i, j;
	while (scanf("%d %d", &n, &m) != EOF && (n || m)) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; ++j) {
				scanf("%d", &mat[i][j]);
			}
		}

		for (i = m - 1; i >= 0; --i) {
			for (j = 0; j < n; ++j) {
				if (mat[j][i]) {
					break;
				}
			}
			if (j < n) {
				break;
			}
		}

		int l = i;
		int sum = 0;
		for (i = 0; i < n; ++i) {
			sum += mat[i][l];
		}

		for (i = 0; i < n; ++i) {
			int g = gcd(mat[i][l], sum);
			mat[i][l] /= g;
			dow[i] = sum / g;
		}

		for (i = 0; i < n; ++i) {
			printf("%d / %d\n", mat[i][l], dow[i]);
		}
	}

	return 0;
}