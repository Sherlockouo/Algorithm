#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;


/*
������ֿ�����
���ƹ�ʽ���񼶼��٣�ת���ɾ�������⣻
������˵����ڲ�ѭ���Ӻ���������������Ų�ȡģ��
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 52
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
				printf("%d ", pkData[i][j]);
			}
			puts("");
		}
	}
};

Matrix Matrix::s_kMatrix[64];
Matrix Matrix::s_kMultiplyTemp;

LL AArray[MAXN][MAXN] = {};
LL BArray[MAXN][MAXN] = {};


// 1. ����ϵ������
// 2. ����������
// 3. �����ݾ��� * ������

Matrix A, B, ret1, ret2;

int getChar(int idx) {
	if (idx < 26) {
		return 'a' + idx;
	}
	return 'A' + idx - 26;
}

int ABS(int a) {
	return a > 0 ? a : -a;
}

void ConstructMatrix(int tp) {
	int i, j;
	for (i = 0; i < 52; ++i) {
		int from = getChar(i);
		for (j = 0; j < 52; ++j) {
			int to = getChar(j);
			if (tp == 0) {
				AArray[i][j] = ABS(from - to) <= 32 ? 1 : 0;
			}
			else {
				AArray[i][j] = ABS(from - to) < 32 ? 1 : 0;
			}
		}
		BArray[i][0] = 1;
	}
	A.Reset(52, 52, AArray);
	B.Reset(52, 1, BArray);
}

int m;

int main() {
	int t, i;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &m);

		LL ans = 0;

		ConstructMatrix(0);
		Matrix::GetPow(A, m - 1, ret1);
		Matrix::Multiply(ret1, B, ret2);
		for (i = 0; i < 52; ++i)
			ans = (ans + ret2.get(i, 0)) % MOD;

		ConstructMatrix(1);
		Matrix::GetPow(A, m - 1, ret1);
		Matrix::Multiply(ret1, B, ret2);
		for (i = 0; i < 52; ++i)
			ans = (ans - ret2.get(i, 0)) % MOD;

		ans = ((ans % MOD) + MOD) % MOD;

		printf("%I64d\n", ans);

	}

	return 0;
}