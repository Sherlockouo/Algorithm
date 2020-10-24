// HDU 2065


// ������ֿ�����
// ���ƹ�ʽ���񼶼��٣�ת���ɾ�������⣻
// ������˵����ڲ�ѭ���Ӻ���������������Ų�ȡģ��
// Author: WhereIsHeroFrom
// Update Time: 2018-3-22
// Algorithm Complexity: O(m^3log(n))


#include <iostream>

using namespace std;

#define MAXN 6
#define MOD 100
#define LL int


class Matrix {
public:
	int n, m;
	LL d[MAXN][MAXN];
	Matrix() {
		n = m = 0;
		int i, j;
		for (i = 0; i < MAXN; i++) {
			for (j = 0; j < MAXN; j++) {
				d[i][j] = 0;
			}
		}
	}
	Matrix operator *(const Matrix& other) {
		Matrix ret;
		ret.n = n;
		ret.m = other.m;
		int i, j, k;
		for (j = 0; j < ret.m; j++) {
			for (i = 0; i < ret.n; i++) {
				ret.d[i][j] = 0;
				for (k = 0; k < m; k++) {
					ret.d[i][j] += d[i][k] * other.d[k][j];
					if (ret.d[i][j] >= MOD)
						ret.d[i][j] %= MOD;
				}
			}
		}
		return ret;
	}

	Matrix Identity(int _n) {
		Matrix I;
		I.n = I.m = _n;
		int i, j;
		for (i = 0; i < _n; i++) {
			for (j = 0; j < _n; j++) {
				I.d[i][j] = (i == j) ? 1 : 0;
			}
		}
		return I;
	}

	Matrix getPow(unsigned __int64 e) {
		Matrix tmp = *this;
		Matrix ret = Identity(n);
		while (e) {
			if (e & 1) {
				ret = ret * tmp;
			}
			e >>= 1;
			tmp = tmp * tmp;
		}
		return ret;
	}

	// | A  A |
	// | O  I |
	// ��չ����������A + A^2 + A^3 + ... + A^n
	Matrix getExtendMatrix() {
		Matrix ret;
		ret.n = ret.m = n * 2;
		ret.copyMatrix(*this, 0, 0);
		ret.copyMatrix(*this, 0, n);
		ret.copyMatrix(Identity(n), n, n);
		return ret;
	}

	// ������A���������ھ����(r, c)λ��
	void copyMatrix(Matrix A, int r, int c) {
		for (int i = r; i < r + A.n; i++) {
			for (int j = c; j < c + A.n; j++) {
				d[i][j] = A.d[i - r][j - c];
			}
		}
	}

	void Print() {
		int i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%d ", d[i][j]);
			}
			puts("");
		}
	}
};

int main() {
	Matrix A, B;
	int i, j;
	int t;
	A.n = A.m = 4;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j) {
			if (i == j) {
				A.d[i][j] = 2;
			}
			else if (i + j == 3) {
				A.d[i][j] = 0;
			}
			else {
				A.d[i][j] = 1;
			}
		}
	}
	B.n = 4;
	B.m = 1;
	B.d[0][0] = 1;
	B.d[1][0] = 0;
	B.d[2][0] = 0;
	B.d[3][0] = 0;

	while (scanf("%d", &t) != EOF && t) {
		int v = t;
		while (t--) {
			unsigned __int64 N;
			scanf("%I64d", &N);
			Matrix ans = A.getPow(N) * B;
			printf("Case %d: %d\n", v - t, ans.d[0][0]);
		}
		puts("");
	}

	return 0;
}