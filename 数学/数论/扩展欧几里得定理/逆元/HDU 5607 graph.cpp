#include <iostream>
#include <string>
#include <cmath>
using namespace std;


/*
������ֿ�����
���ƹ�ʽ���񼶼��٣�ת���ɾ�������⣻
������˵����ڲ�ѭ���Ӻ���������������Ų�ȡģ��
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 60
#define LL __int64
int MOD = 1000000007;

class Matrix {
private:
	int n, m;
	LL** pkData;

	static Matrix s_kMatrix[64], s_kMultiplyTemp;

	void _Alloc() {
		// ֮���԰ѿռ���ڶ��ϣ�����Ϊ��MAXN�ܴ�ʱ��ջ�Ϸ��䲻����ô��ռ�
		pkData = new LL *[MAXN];
		for (int i = 0; i < MAXN; ++i) {
			pkData[i] = new LL[MAXN];
		}
	}

	void _Dealloc() {
		if (pkData) {
			// ���ͷŵ�ά�ռ䣬���ͷŸ�ά��
			for (int i = 0; i < MAXN; ++i) {
				delete[] pkData[i];
			}
			delete[] pkData;
			pkData = NULL;
		}
	}
public:
	Matrix() : n(0), m(0), pkData(NULL) {
		_Alloc();
	}
	virtual ~Matrix() {
		_Dealloc();
	}

	LL get(int i, int j) const {
		return pkData[i][j];
	}

	int getN() const {
		return n;
	}

	static void Identity(int _n, Matrix& ret) {
		ret.n = ret.m = _n;
		int i, j;
		for (i = 0; i < _n; i++) {
			for (j = 0; j < _n; j++) {
				ret.pkData[i][j] = (i == j) ? 1 : 0;
			}
		}
	}

	static void GetPow(Matrix& raw, unsigned __int64 e, Matrix& ret) {
		int index = 1;
		Matrix::Identity(raw.getN(), ret);       // 0����
		Matrix::s_kMatrix[1].Copy(raw);          // 1����
		while (e) {
			if (e & 1) {
				Matrix::Multiply(ret, Matrix::s_kMatrix[index], Matrix::s_kMultiplyTemp);
				ret.Copy(Matrix::s_kMultiplyTemp);
			}
			e >>= 1;
			Matrix::Multiply(Matrix::s_kMatrix[index], Matrix::s_kMatrix[index], Matrix::s_kMatrix[index + 1]);
			++index;
		}
	}

	static void Multiply(const Matrix &me, const Matrix& other, Matrix& ret) {
		// assert(m == other.n);
		ret.Reset(me.n, other.m);
		int i, j, k;
		for (i = 0; i < me.n; i++) {
			for (k = 0; k < me.m; k++) {
				LL v = me.pkData[i][k];
				for (j = 0; j < other.m; j++) {
					ret.pkData[i][j] += v * other.pkData[k][j];
					if (ret.pkData[i][j] >= MOD) {
						ret.pkData[i][j] %= MOD;
					}
				}
			}
		}
	}

	static void Add(const Matrix &me, const Matrix& other, Matrix& ret) {
		ret.Reset(me.n, other.m);
		int i, j;
		for (i = 0; i < me.n; i++) {
			for (j = 0; j < me.m; j++) {
				ret.pkData[i][j] = (me.pkData[i][j] + other.pkData[i][j]) % MOD;
			}
		}
	}

	void Reset(int nn, int mm, LL data[][MAXN]) {
		n = nn;
		m = mm;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				pkData[i][j] = data[i][j];
			}
		}
	}

	void Reset(int nn, int mm) {
		n = nn;
		m = mm;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				pkData[i][j] = 0;
			}
		}
	}

	void Copy(const Matrix& other) {
		n = other.n;
		m = other.m;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				pkData[i][j] = other.pkData[i][j];
			}
		}
	}



	// | A  A |
	// | O  I |
	// I ��Ҫ�ֶ����� Identity(n);
	// ��չ����������A + A^2 + A^3 + ... + A^n
	void getExtendMatrix(Matrix& ret, Matrix& I) {
		ret.n = ret.m = n * 2;
		ret.Reset(n * 2, n * 2);
		ret.copyMatrix(*this, 0, 0);
		ret.copyMatrix(*this, 0, n);
		ret.copyMatrix(I, n, n);
	}

	// ��ȡ this ����� (r,c) - (n,m) ���Ӿ���浽 ret
	void getSubMatrix(Matrix& ret, int r, int c, int n, int m) {
		ret.n = n;
		ret.m = m;
		for (int i = r; i < r + n; i++) {
			for (int j = c; j < c + m; j++) {
				ret.pkData[i - r][j - c] = pkData[i][j];
			}
		}
	}

	// ������A���������ھ����(r, c)λ��
	void copyMatrix(Matrix& A, int r, int c) {
		for (int i = r; i < r + A.n; i++) {
			for (int j = c; j < c + A.m; j++) {
				pkData[i][j] = A.pkData[i - r][j - c];
			}
		}
	}

	void Print() {
		int i, j;
		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				printf("%I64d ", pkData[i][j]);
			}
			puts("");
		}
	}
};

Matrix Matrix::s_kMatrix[64];
Matrix Matrix::s_kMultiplyTemp;

LL AArray[MAXN][MAXN] = {
};
LL BArray[MAXN][MAXN] = {
};

LL Exp(LL a, LL b, LL c) {
	if (b == 0) {
		return 1 % c;
	}
	LL tmp = Exp(a*a % c, (b >> 1), c);
	if (b & 1) {
		tmp = tmp * a % c;
	}
	return tmp;
}


// 1. ����ϵ������
// 2. ����������
// 3. �����ݾ��� * ������

Matrix A, B, ret1, ret2;


/*
����ͬ��
���ͬ�෽�̵�һ����ת����һ��ʽ��ax + by = c��������̵���ⲽ�����£�
i) �������a��b�����Լ��d = gcd(a, b)����ôԭ���̿���ת����d(ax/d + by/d) = c������֪��(ax/d + by/d)Ϊ����������d��������b�����̱�Ȼ�޽⣬�㷨�������������ii)��
ii) ��i)���Ե�֪�������н���һ�����Ա�ʾ�� ax + by = c = gcd(a, b)*c'����ô����������������d = gcd(a, b) = ax + by������ŷ����¶����У�
d = gcd(a, b) = gcd(b, a%b) = bx' + (a%b)y' = bx' + [a-b*(a/b)]y' = ay' + b[x' - (a/b)y'], ������x = y',  y = x' - (a/b)y'��
����gcd(a, b)��һ���ݹ�ļ��㣬���������(x, y)ʱ��(x', y')��ʵ�Ѿ����õݹ��������ˣ��ݹ����Ϊb == 0��ʱ�򣨶Ա�շת�����Ҳ��b == 0��ʱ��ݹ����������ô��ʱ���̵Ľ�x0 = 1, y0 = 0��
Author: WhereIsHeroFrom
Update Time: 2018-3-23
Algorithm Complexity: O(log(n))
*/

LL GCD(LL a, LL b) {
	return b ? GCD(b, a%b) : a;
}

// ��չŷ�����
// aX + bY = 1 
LL ExpGcd(LL a, LL b, LL &X, LL &Y) {
	LL q, temp;
	if (!b) {
		q = a; X = 1; Y = 0;
		return q;
	}
	else {
		q = ExpGcd(b, a % b, X, Y);
		temp = X;
		X = Y;
		Y = temp - (a / b) * Y;
		return q;
	}
}

int Map[MAXN][MAXN];

int main() {
	int N, M, Q, u, K;
	int i, j;
	while (scanf("%d %d", &N, &M) != EOF) {
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				Map[i][j] = 0;
			}
		}
		while (M--) {
			int from, to;
			scanf("%d %d", &from, &to);
			--from;
			--to;
			Map[from][to] ++;
		}

		for (i = 0; i < N; ++i) {
			int c = 0;
			for (j = 0; j < N; ++j) {
				c += Map[i][j];
			}
			LL X, Y;
			if (c) {
				ExpGcd(c, MOD, X, Y);
				X = (X % MOD + MOD) % MOD;
			}
			else {
				X = 0;
			}

			for (j = 0; j < N; ++j) {
				AArray[j][i] = Map[i][j] ? X : 0;
			}
		}

		A.Reset(N, N, AArray);

		scanf("%d", &Q);

		while (Q--) {
			scanf("%d %d", &u, &K);
			--u;
			for (i = 0; i < N; ++i) {
				BArray[i][0] = (i == u) ? 1 : 0;
			}
			B.Reset(N, 1, BArray);
			Matrix::GetPow(A, K, ret1);
			Matrix::Multiply(ret1, B, ret2);

			for (i = 0; i < N; ++i) {
				printf("%d ", (int)ret2.get(i, 0));
			}
			puts("");
		}
	}
	return 0;
}

/*
3 6
1 2
1 3
2 1
2 2
2 3
3 2

10
1 0
2 0
3 0
1 1
2 1
3 1
1 2
2 2
3 2
*/