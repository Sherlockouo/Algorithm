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

#define MAXN 2
#define LL int
#define eps 1e-6
int MOD = 8191;

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
int SquareNumber[100];
int X1, Y1;

int main() {
	int n, k;
	int i;
	SquareNumber[1] = SquareNumber[4] = SquareNumber[9] = SquareNumber[16] = SquareNumber[25] = 1;
	while(scanf("%d %d", &n, &k) != EOF) {
		if( SquareNumber[n] ) {
			printf("No answers can meet such conditions\n");
		}else {
			for(i = 2; ; ++i) {
				__int64 v = (__int64)i*(__int64)i;
				v -= 1;
				if(v % n == 0) {
					v /= n;
					Y1 = int( sqrt(v * 1.0) + 1e-6 );
					
					if( (__int64)Y1*(__int64)Y1 == v) {
						X1 = i;
						break;
					}
				}
			} 	
			
			AArray[0][0] = X1 % MOD;
			AArray[0][1] = Y1 % MOD * n % MOD;
			AArray[1][0] = Y1 % MOD;
			AArray[1][1] = X1 % MOD;
			
			BArray[0][0] = X1 % MOD;
			BArray[1][0] = Y1 % MOD;
			
			
			A.Reset(2, 2, AArray);
			B.Reset(2, 1, BArray);
			
			Matrix::GetPow(A, k-1, ret1);
			Matrix::Multiply(ret1, B, ret2);
			printf("%d\n", ret2.get(0, 0));
		}
	}
	return 0;	
} 
