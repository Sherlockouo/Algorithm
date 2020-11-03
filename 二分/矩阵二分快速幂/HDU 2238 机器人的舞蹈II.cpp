#include <iostream>
#include <cstring>
using namespace std;

#define MAXN 40
#define LL __int64
LL MOD = 9937;

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
		ret.copyMatrix(*this, 0, 0);
		ret.copyMatrix(*this, 0, n);
		ret.copyMatrix(I, n, n);
	}

	// ������A���������ھ����(r, c)λ��
	void copyMatrix(Matrix& A, int r, int c) {
		for (int i = r; i < r + A.n; i++) {
			for (int j = c; j < c + A.n; j++) {
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

LL AArray[MAXN][MAXN] = { 0 };
LL BArray[MAXN][MAXN] = { 0 };

// 1. ����ϵ������
// 2. ����������
// 3. �����ݾ��� * ������


int n, m;
Matrix A, B, ret1, ret2;

void getState(int s, int a[4]) {
	int i;
	for (i = 0; i < 4; ++i) {
		a[3 - i] = s % 5;
		s /= 5;
	}
}

int packState(int a[4]) {
	int s = 0;
	for (int i = 0; i < 4; ++i) {
		s = s * 5 + a[i];
	}
	return s;
}

int from[4], to[4];
int states[625], stateCount;
int stateHash[625];
int NState;

int dir[4][3] = {
	{ 0, 1, 2 },
	{ 1, 3, 0 },
	{ 2, 3, 0 },
	{ 3, 2, 1 },
};


int c;
void dfs(int index, int predir, int fromstate, int from[4], int to[4]) {

	if (index == 4) {
		++AArray[stateHash[fromstate]][stateHash[packState(to)]];
		return;
	}

	if (from[index] == 0 && predir == 2) {
		dfs(index + 1, -1, fromstate, from, to);
	}
	else {

		int max = from[index];

		for (int cnt = 0; cnt <= max; ++cnt) {
			from[index] -= cnt;

			if (predir < 2) {
				int go = dir[index][predir + 1];
				to[go] += cnt;
				dfs(index, predir + 1, fromstate, from, to);
				to[go] -= cnt;
			}

			from[index] += cnt;
		}

	}
}

int main() {
	int t;
	int i, j;
	stateCount = 0;
	memset(AArray, 0, sizeof(AArray));

	// 1. ��Ϊ�ĸ�����������ͬ�ģ�����״̬���Խ���ѹ��
	for (i = 0; i < 625; ++i) {
		getState(i, from);
		int s = 0;
		for (j = 0; j < 4; ++j) {
			s += from[j];
		}
		if (s == 4) {
			states[stateCount] = i;
			stateHash[i] = stateCount;

			if (from[0] == from[1] && from[0] == from[2] && from[0] == from[3]) {
				BArray[stateCount][0] = 1;
				NState = stateCount;
			}
			else {
				BArray[stateCount][0] = 0;
			}

			++stateCount;
		}
	}


	for (i = 0; i < stateCount; ++i) {
		getState(states[i], from);
		dfs(0, -1, states[i], from, to);

	}

	A.Reset(stateCount, stateCount, AArray);
	B.Reset(stateCount, 1, BArray);

	//A.Print();

	while (scanf("%d", &n) != EOF) {
		Matrix::GetPow(A, n, ret1);
		Matrix::Multiply(ret1, B, ret2);
		printf("%d\n", (int)ret2.get(NState, 0));
	}
	return 0;
}

/*
9
309
3668
7219
3619


*/