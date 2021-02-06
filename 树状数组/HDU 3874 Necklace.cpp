/*
    ���⣺���� n <= 50000 �������ٸ��� m <= 200000 ��ѯ�ʣ�ÿ��ѯ���ʵ��� [L, R] ��������ڲ��ظ����ĺ͡�

    ��⣺ǰ׺�� + ��ͬ��ǰ�� + �����㷨 + ��״����

    Ԥ����ǰ׺�� S[i]
    Ԥ����ǰ�� pre[i]��  a[i] == a[j] && i < j  �� pre[j] = i;

    ���������� ǰ�����ڵ���������״����  add(pre[i], a[i])
    
    ���������β�˵�����Ȼ���ǰ����ö�����䣬�Ѵ�ͷ������β����������������������״���飬
    �������в�ѯ����ѯ����  sum(n) - sum(L[i])  ����� L[i] ����������ĺ� X ��Ȼ���õ�ǰ����ǰ׺�ͼ�ȥ
    X �����������Ĵ��ˡ�
*/

#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

//***************************************** һά��״���� ģ�� *****************************************

#define MAXV 50010
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
    while (x >= 1) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** һά��״���� ģ�� *****************************************

ll s[MAXV];
int a[MAXV], pre[MAXV];
int pos[1000010];
ll ans[MAXV];
int n, m;

struct Interval {
    int l, r;
    int idx;

    void read(int i) {
        scanf("%d %d", &l, &r);
        idx = i;
    }

    bool operator < (const Interval& i) const {
        return r < i.r;
    }
}I[200010];


int main() {
    int t, i, j;
    scanf("%d", &t);
    while (t--) {

        scanf("%d", &n);
        memset(pos, 0, sizeof(pos));
        clear();

        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
            s[i] = s[i - 1] + a[i];
            pre[i] = pos[a[i]];
            pos[a[i]] = i;
        }
        
        scanf("%d", &m);
        for (i = 0; i < m; ++i) {
            I[i].read(i + 1);
        }
        sort(I, I + m);
        int R = 0;
        for (i = 0; i < m; ++i) {
            for (j = R + 1; j <= I[i].r; ++j) {
                if (pre[j])
                    add(pre[j], n, a[j]);
            }
            R = I[i].r;
            ans[I[i].idx] = s[I[i].r] - s[I[i].l-1] - sum(n) + sum(I[i].l - 1);
        }
        for (i = 1; i <= m; ++i) {
            printf("%lld\n", ans[i]);
        }
    }

    return 0;
}