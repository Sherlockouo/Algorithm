#include <iostream>

using namespace std;

/*
������ֿ�����
���ƹ�ʽ���񼶼��٣�ת���ɾ�������⣻
������˵����ڲ�ѭ���Ӻ���������������Ų�ȡģ��
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/

#define MAXN 100
#define LL __int64
int MOD = 1234567891;

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

LL AArray[MAXN][MAXN] = { 0 };
LL BArray[MAXN][MAXN] = { 0 };

// 1. ����ϵ������
// 2. ����������
// 3. �����ݾ��� * ������


/*
�䳲����ϵ ģ��
�ǵ�ǰ���ӵı�ż�Ϊ(r, c)��
1��������Ŀ������Ϊ2N-1���������кţ���0��ʼ����ǿ��ء����к�r<N��������Ϊr+N����������Ϊ(3N-2)-r��
2���Ϸ���������ж�һ������(x, y)�Ƿ��ںϷ������ڣ�����x��x�ķ�ΧΪ[0, 2N-1)������y��y�ķ�ΧΪ[0, ����)�������ļ������1����
3��6���ھ����ꡣ
a.�����ھӡ�   (r,c-1)��(r,c+1)��
b.�����ھӡ�   �к�r<Nʱ�������ھ�����(r-1,c-1)��(r-1,c)�����������ھ�����(r-1,c)��(r-1,c+1)��
c.�����ھӡ�    �к�r<N-1ʱ�������ھ�����(r+1,c)��(r-1,c+1)�����������ھ�����(r+1,c-1)��(r+1,c)��
ע�������ھ����궼��Ҫͨ��2���ĺϷ����������⡣
4��N = 6ʱ�ĸ�������Ϊ1 + 6 + 12 + 18 + 24 + 30 = 91�� (ÿ�μ�һȦ��һȦ����Ϊ  6*(N-1))
Author: WhereIsHeroFrom
Update Time: 2018-3-29
Algorithm Complexity: O(N^2)
*/

struct HoneycombNode {
	int r, c;
	HoneycombNode() {}
	HoneycombNode(int _r, int _c) {
		r = _r;
		c = _c;
	}

	HoneycombNode left() {
		return HoneycombNode(r, c - 1);
	}

	HoneycombNode right() {
		return HoneycombNode(r, c + 1);
	}
};

// �䳲����ϵ
#define MAXH 6

class HoneycombAxis {
	int n;
	int id[2 * MAXH][2 * MAXH];
	int idCount;
	HoneycombNode nodes[4 * MAXH*MAXH];

public:
	void init(int _n) {
		n = _n;
		int i, j;
		idCount = 0;
		for (i = 0; i < getRowCount(); ++i) {
			for (j = 0; j < getColCount(i); ++j) {
				id[i][j] = idCount;
				nodes[idCount] = HoneycombNode(i, j);
				++idCount;
			}
		}
	}

	// ��������
	int getRowCount() {
		return 2 * n - 1;
	}

	// ��������
	int getColCount(int r) {
		if (r < n) {
			return n + r;
		}
		else {
			return 3 * n - 2 - r;
		}
	}

	// ���ظ��Ӹ���
	int getIDCount() {
		return idCount;
	}

	// ���ظ����������
	int getNodeID(HoneycombNode& node) {
		return id[node.r][node.c];
	}

	// ͨ��ID���ظ���
	HoneycombNode getNode(int id) {
		return nodes[id];
	}

	// ���ص�ǰ���ӵı���Ƿ�Ϸ�
	bool isValid(HoneycombNode& node) {
		// ����
		if (node.r < 0 || node.r >= getRowCount()) {
			return false;
		}
		// ����
		if (node.c < 0 || node.c >= getColCount(node.r)) {
			return false;
		}
		return true;
	}

	void getNeighbors(HoneycombNode now, int &retSize, HoneycombNode *ret) {
		HoneycombNode tmp[6];
		int i;

		// �����ھ�
		tmp[0] = now.left();
		tmp[1] = now.right();

		// �����ھ�
		if (now.r < n) {
			tmp[2] = HoneycombNode(now.r - 1, now.c - 1);
		}
		else {
			tmp[2] = HoneycombNode(now.r - 1, now.c);
		}
		tmp[3] = tmp[2].right();

		// �����ھ�
		if (now.r < n - 1) {
			tmp[4] = HoneycombNode(now.r + 1, now.c);
		}
		else {
			tmp[4] = HoneycombNode(now.r + 1, now.c - 1);
		}
		tmp[5] = tmp[4].right();


		retSize = 0;
		for (i = 0; i < 6; ++i) {
			if (isValid(tmp[i])) {
				ret[retSize++] = tmp[i];
			}
		}
	}
}HX;

HoneycombNode HN[MAXN];

Matrix A, B, ret1, ret2;

int main() {
	int N, L;
	int i, j, cas = 0;
	while (scanf("%d %d %d", &N, &MOD, &L) != EOF && (N || MOD || L)) {
		HX.init(N);
		int ALL = HX.getIDCount();

		for (i = 0; i < ALL; ++i) {
			for (j = 0; j < ALL; ++j) {
				AArray[i][j] = (i == j) ? 1 : 0;
			}
		}

		for (i = 0; i < ALL; ++i) {
			HoneycombNode node = HX.getNode(i);
			int v;
			scanf("%d", &v);
			BArray[i][0] = v;

			int size = 0;
			HX.getNeighbors(node, size, HN);

			for (j = 0; j < size; ++j) {
				++AArray[HX.getNodeID(HN[j])][i];
			}
		}
		A.Reset(ALL, ALL, AArray);
		B.Reset(ALL, 1, BArray);

		Matrix::GetPow(A, L, ret1);
		Matrix::Multiply(ret1, B, ret2);

		LL ans = 0;
		for (i = 0; i < ALL; ++i) {
			ans += ret2.get(i, 0);
		}

		printf("Case %d: %I64d\n", ++cas, ans);
	}


	return 0;
}