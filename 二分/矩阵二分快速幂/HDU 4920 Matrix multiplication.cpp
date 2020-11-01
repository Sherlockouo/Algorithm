#include <iostream>
using namespace std;

#define MAXN 802
#define LL short
LL MOD = 3;
int H[3][3];

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
                if(v) {
	                 for (j = 0; j < other.m; j++) {
	                    ret.pkData[i][j] += H[v][ other.pkData[k][j] ];
	                }               	
				}
            }
        }
        
        for(i = 0; i < ret.n; ++i) {
            for(j = 0; j < ret.m; ++j) {
                if (ret.pkData[i][j] >= MOD) {
                    ret.pkData[i][j] %= MOD;
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
                if(j) printf(" ");
                printf("%d", pkData[i][j]);
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

// 1. ����ϵ������
// 2. ����������
// 3. �����ݾ��� * ������

Matrix A, B, ret;

int main() {
    int n, i, j, d;
    for(i = 0; i < 3; ++i) {
    	for(j = 0; j < 3; ++j) {
    		H[i][j] = i * j % 3;
		}
	}
    while(scanf("%d", &n) != EOF) {
        for(i = 0; i < n; ++i) {
            for(j = 0; j < n; ++j) {
                scanf("%d", &d);
                AArray[i][j] = d % 3;
            }
        }
        A.Reset(n, n, AArray);
        for(i = 0; i < n; ++i) {
            for(j = 0; j < n; ++j) {
                scanf("%d", &d);
                BArray[i][j] = d % 3;
            }
        }
        B.Reset(n, n, BArray);
        Matrix::Multiply(A, B, ret);
        ret.Print();
    }
    return 0;
} 
