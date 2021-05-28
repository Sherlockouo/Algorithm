/*
������ֿ�����
���ƹ�ʽ���񼶼��٣�ת���ɾ�������⣻
������˵����ڲ�ѭ���Ӻ���������������Ų�ȡģ��
Author: WhereIsHeroFrom
Update Time: 2020-11-03
Algorithm Complexity: O(m^3log(n))
*/
/*
    ��չŷ������ǰ����Ҫ��
        1������ɸѡ
        2��ŷ���������
        3�����ֿ�����
    �� b >= phi(c) ʱ
        a^b mod c = a^(b mod phi(c) + phi(c)) mod c
*/

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory.h>
#include <cmath>
using namespace std;

#pragma warning(disable : 4996)

#define ll long long
#define MAXP 65540

int primes[MAXP];
bool notprime[MAXP];

// �����������ɸѡ�� 
void Eratosthenes() {
    memset(notprime, false, sizeof(notprime));
    notprime[1] = true;
    primes[0] = 0;
    for (int i = 2; i < MAXP; i++) {
        if (!notprime[i]) {
            primes[++primes[0]] = i;
            //��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� long long
            for (ll j = (ll)i * i; j < MAXP; j += i) {
                notprime[j] = true;
            }
        }
    }
}

// ŷ������ - ��ȡС��n��������n���ص����ĸ��� 
// ������
// Phi(10) = 4
// �� 1��3��7��9  �ܹ�4�� 
int Phi(int n) {
    if (n == 1)
        return 1;
    int ans = 1;
    for (int i = 1; i <= primes[0]; i++) {
        int p = primes[i];
        if (0 == n % p) {
            n /= p;
            ans *= (p - 1);
            while (0 == n % p) {
                n /= p;
                ans *= p;
            }
        }
        if (n == 1)
            return ans;
    }
    return ans * (n - 1);
}

ll Exp(ll a, ll n, ll Mod) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans = ans * a % Mod;
        a = a * a % Mod;
        n >>= 1;
    }
    return ans;
}

const int MAXN = 2;
int MOD = 0;

class Matrix {
private:
    int n, m;
    ll** pkData;

    static Matrix s_kMatrix[64], s_kMultiplyTemp;

    void _Alloc() {
        // ֮���԰ѿռ���ڶ��ϣ�����Ϊ��MAXN�ܴ�ʱ��ջ�Ϸ��䲻����ô��ռ�
        pkData = new ll * [MAXN];
        for (int i = 0; i < MAXN; ++i) {
            pkData[i] = new ll[MAXN];
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

    ll get(int i, int j) const {
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

    static void Multiply(const Matrix& me, const Matrix& other, Matrix& ret) {
        // assert(m == other.n);
        ret.Reset(me.n, other.m);
        int i, j, k;
        for (i = 0; i < me.n; i++) {
            for (k = 0; k < me.m; k++) {
                ll v = me.pkData[i][k];
                for (j = 0; j < other.m; j++) {
                    ret.pkData[i][j] += v * other.pkData[k][j];
                    if (ret.pkData[i][j] >= MOD) {
                        ret.pkData[i][j] %= MOD;
                    }
                }
            }
        }
    }

    static void Add(const Matrix& me, const Matrix& other, Matrix& ret) {
        ret.Reset(me.n, other.m);
        int i, j;
        for (i = 0; i < me.n; i++) {
            for (j = 0; j < me.m; j++) {
                ret.pkData[i][j] = (me.pkData[i][j] + other.pkData[i][j]) % MOD;
            }
        }
    }

    void Reset(int nn, int mm, ll data[][MAXN]) {
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

ll AArray[MAXN][MAXN] = { {1, 1}, {1, 0} };
ll BArray[MAXN][MAXN] = { {1, 0}, {1, 0} };

// 1. ����ϵ������
// 2. ����������
// 3. �����ݾ��� * ������

ll F[100];
const int maxf = 50;

Matrix A, B, ret, ret1;

ll f(int n) {
    if (n < maxf) {
        F[0] = F[1] = 1;
        for (int i = 2; i <= n; ++i) {
            F[i] = (F[i - 1] + F[i - 2]);
        }
        return F[n];
    }
    else {
        A.Reset(2, 2, AArray);
        B.Reset(2, 1, BArray);
        Matrix::GetPow(A, n - 1, ret);
        Matrix::Multiply(ret, B, ret1);
        return ret1.get(0, 0) + MOD;
    }
}

int main() {
    Eratosthenes();
    int a, b, P, n;
    int t, cas = 0;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &a, &b, &P, &n);
        MOD = Phi(P);
        ll ans = 0;
        if (n == 1) {
            ans = a % P;
        }
        else if (n == 2) {
            ans = b % P;
        }
        else
            ans = Exp(b, f(n - 2), P) * Exp(a, f(n - 3), P) % P;
        printf("Case #%d: %lld\n", ++cas, ans);
    }

    return 0;
}

/*
10
0 1 10 1
1 0 10 1
0 1 10 2
1 0 10 2
0 1 10 3
1 0 10 3
*/