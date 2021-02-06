/*
    ���⣺����һ������Ϊ n(n <= 50000) ������ A��ֻ�� b �� w ��ɣ����ֲ�����
    1�� 0 L R�� �ҳ����� [L, R] ���ж��ٸ� wbw��
    2�� 1 k ch������ k ���ַ���� ch��
    ��⣺��״���� / �������
    
    1������һ��Ԥ����
        n = len - 2
        �������3���ַ��� bwb ���ڶ�Ӧ����״�����в���1��������� 0
        012         ->  1
        123         ->  2
        234         ->  3
        k(k+1)(k+2) ->  k+1

    2������ 0 ������ѯ����״����  SUM(L+1��R-1) �ĺ�;
    3) ���� 1 �������� k ���ַ��ܹ�Ӱ�����״�����λ��Ϊ 
        (k-2)(k-1)k   ->  k-1
        (k-1)k(k+1)   ->  k
        k(k+1)(k+2)   ->  k+1

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
    while (x >= 1) {
        s += c[x];
        x ^= lowbit(x);
    }
    return s;
}
//***************************************** һά��״���� ģ�� *****************************************

ll sum(int l, int r) {
    if (l > r) {
        return 0;
    }
    return sum(r) - sum(l - 1);
}

char str[MAXV];
int len;

int cnt(int a, int b, int c) {
    if (c >= len || a < 0) {
        return 0;
    }
    return (str[a] == 'w' && str[b] == 'b' && str[c] == 'w') ? 1 : 0;
}

int main() {
    int t, cas = 0;
    int n, m;
    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        scanf("%s", str);
        clear();
        len = n;
        for (int i = 0; i + 2 < n; ++i) {
            int v = cnt(i, i + 1, i + 2);
            add(i + 1, n - 2, v);
        }
        printf("Case %d:\n", ++cas);
        while (m--) {
            int tp;
            scanf("%d", &tp);
            if (tp == 0) {
                int L, R;
                scanf("%d %d", &L, &R);
                printf("%d\n", sum(L+1, R-1));
            }
            else {
                int k;
                char ch[10];
                scanf("%d %s", &k, ch);
                for (int i = 0; i < 3; ++i) {
                    char tmp = str[k];
                    int pre = cnt(k - i, k - i + 1, k - i + 2);
                    str[k] = ch[0];
                    int now = cnt(k - i, k - i + 1, k - i + 2);
                    str[k] = tmp;
                    if (pre == 1 && now == 0) {
                        add(k - i + 1, n - 2, -1);
                    }
                    else if(pre == 0 &&now == 1) {
                        add(k - i + 1, n - 2, 1);
                    }
                }
                str[k] = ch[0];
            }
        }

    }

    return 0;
}
