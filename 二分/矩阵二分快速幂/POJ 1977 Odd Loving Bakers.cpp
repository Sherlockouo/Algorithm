#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cstdio>
using namespace std;


/*
������ֿ�����
���ƹ�ʽ���񼶼��٣�ת���ɾ�������⣻
������˵����ڲ�ѭ���Ӻ���������������Ų�ȡģ��
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 200
#define LL int
int MOD = 2;

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
				if (!v) continue;
				for (j = 0; j < other.m; j++) {
					ret.pkData[i][j] ^= (v & other.pkData[k][j]);
					ret.pkData[i][j] &= 1;
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

LL AArray[MAXN][MAXN] = {
};

LL BArray[MAXN][MAXN] = {
};
bool Map[MAXN][MAXN];

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
char names[MAXN][30];
int totalname;

int finds(const char *name){
	int i;
	for (i = 0; i < totalname; ++i) {
		if (!strcmp(names[i], name)) {
			return i;
		}
	}
	strcpy(names[i], name);
	++totalname;
	return i;
}

char aa[100000000];

int main() {
	int t;
	int dd, T;
	int i, j;
	scanf("%d", &t);

	while (t--) {
		scanf("%d %d", &dd, &T);
		totalname = 0;
		int N = dd;
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				AArray[i][j] = (i == j) ? 1 : 0;
				Map[i][j] = 0;
			}
			BArray[i][0] = 0;
		}

		while (dd--) {
			char name[30];
			scanf("%s", name);
			int to = finds(name);
			scanf("%s", aa);
			BArray[to][0] = (aa[strlen(aa) - 1] - '0') & 1;

			int q;
			scanf("%d", &q);
			while (q--) {
				scanf("%s", name);
				int from = finds(name);
				Map[from][to] = 1;
			}
		}
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				AArray[i][j] = AArray[i][j] ^ Map[i][j];
			}
		}

		A.Reset(N, N, AArray);
		B.Reset(N, 1, BArray);

		//A.Print();
		//B.Print();

		Matrix::GetPow(A, T - 1, ret1);
		//ret1.Print();
		Matrix::Multiply(ret1, B, ret2);
		//ret2.Print();
		int cnt = 0;
		for (i = 0; i < totalname; ++i) {
			if (ret2.get(i, 0) & 1) ++cnt;
		}
		printf("%d\n", cnt);

	}

	return 0;
}
/*
10
6 1
A 2 5 B C D E F
B 1 1 C
C 0 2 D F
D 1 2 A B
E 1 3 C D A
F 1 4 A B C F

4


6 2
A 2 5 B C D E F
B 1 1 C
C 0 2 D F
D 1 2 A B
E 1 3 C D A
F 1 4 A B C F

5

1 0 0 1 1 1
1 1 0 1 0 1
1 1 1 0 1 1
1 0 1 1 1 0
1 0 0 0 1 0
1 0 1 0 0 2


6 1000000000
A 0 5 B C D E F
B 0 1 C
C 0 2 D F
D 0 2 A B
E 0 3 C D A
F 0 4 A B C F


3 0
A 1 3 A B C
B 1 3 A B C
C 1 3 A B C

4 4
A 1 0
B 1 4 A B C D
C 0 1 B
D 1 0

*/