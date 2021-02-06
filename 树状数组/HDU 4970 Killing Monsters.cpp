/*
    ���⣺һ��������Ϸ���� n(n <= 100000) ��λ��, M (1 <= M <= 100000) ������ÿ�����Ĺ�����Χ�� [Li, Ri]
    ������Ϊ Di�����ڸ��� K ���֣�ÿ������ Hi ��Ѫ���ʴ� Xi �� λ�� �ߵ� n, �ж���ֻ�ֿ��Ի�������

    ��⣺��״���� + �����㷨
    1�����ȶ������е��������ɶθ��£�������͡�
        �ɶθ��£�add(Li, Di), add(Ri+1, -Di);
        ������ͣ�S[i] = sum(i);
    2�������еĹ��������������Ȼ��� n��ʼ�ۼ� S[i]���ͼ�Ϊ T[i]��ö�ٹ���������λ��Ϊ X[j] == i ��ʱ���ж�
    H[j] > T[i] ��Ϊ�������� + 1��  
*/

#include <iostream>
#include <cstring>
#include <algorithm>
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

struct Monster {
    ll H;
    int x;
    void read() {
        scanf("%lld %d", &H, &x);
    }

    bool operator < (const Monster& m) {
        return x > m.x;
    }

}M[MAXV];

int main() {
    int i, j;
    int m, k;
    while (scanf("%d", &n) != EOF && n) {
        clear();
        scanf("%d", &m);
        while (m--) {
            int L, R, D;
            scanf("%d %d %d", &L, &R, &D);
            add(L, n, D);
            add(R + 1, n, -D);
        }
        scanf("%d", &k);
        for (i = 0; i < k; ++i) {
            M[i].read();
        }
        sort(M, M + k);

        ll s = 0;
        j = 0;
        int cnt = 0;
        for (i = n; i >= 1; --i) {
            s += sum(i);
            while(j < k && M[j].x == i) {
                if (M[j].H > s) {
                    ++cnt;
                }
                ++j;
            }
        }
        printf("%d\n", cnt);

    }
    return 0;
}