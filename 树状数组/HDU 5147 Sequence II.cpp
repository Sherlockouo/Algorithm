/*
    ���⣺����һ�� n(n <= 50000)��Ԫ�ص����� A������Ԫ�� (a, b, c, d) ���㣺
    1. 1 �� a < b < c < d �� n
    2. A[a] < A[b]
    3. A[c] < A[d]

    ��⣺ B[i] ��ʾ j<i && A[j]<A[i] �� j �ĸ�����SumB[i] = sum{ 1<=k<=i| B[i]}
    ˳����һ�� B[i]�� ������һ�� B[i] �������׺��, ����ۼӾ��Ǵ𰸡�
*/

#include <iostream>
#include <cstring>
using namespace std;

//***************************************** һά��״���� ģ�� *****************************************

#define MAXV 100010
#define ll long long

ll c[MAXV];

void clear() {
    memset(c, 0, sizeof(c));
}

int lowbit(int x) {
    return x & -x;
}

void add(int x, int maxn, ll v) {
    while (x <= maxn) {
        c[x] += v;
        x += lowbit(x);
    }
}

ll sum(int x) {
    ll s = 0;
    while (x) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** һά��״���� ģ�� *****************************************

ll A[MAXV];
ll B[2][MAXV];
int n;

int main() {
    int t;
    int i;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            int x;
            scanf("%d", &x);
            A[i] = x;
        }
        memset(B, 0, sizeof(B));

        clear();
        for (i = 1; i <= n; ++i) {
            B[0][i] = sum(A[i] - 1);
            add(A[i], n, 1);
        }

        clear();
        for (i = n; i >= 1; --i) {
            B[1][i] = B[1][i + 1] + ( (n-i) - sum(A[i]) );
            add(A[i], n, 1);
        }

        ll s = 0;
        for (i = 1; i < n; ++i) {
            s += B[0][i] * B[1][i + 1];
        }
        printf("%lld\n", s);
    }

    return 0;
}