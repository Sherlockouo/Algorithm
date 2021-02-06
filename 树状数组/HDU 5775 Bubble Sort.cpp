/*
    ���⣺����һ�� n (n <= 100000 ) ��Ԫ�ص����У�����һ��ð�������Ժ���ÿ��Ԫ���ܹ��ﵽ����������Ҿ���ľ���ֵ��

    ��⣺ÿ����һ����һ����ʼλ�ã�һ������λ�ã��Լ�һ��������λ��Ų����λ�á�
    ��������λ������ѡһ������ģ����ҵ�����ֵ���ɡ�
    ������λ��Ų����λ�� ����ͨ����״�������ұ߱���������� x �����������ܹ����������λ�� n-x
*/

#include <iostream>
#include <cstring>
#include <queue>
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

int n;
int a[MAXV], ans[MAXV];
int b[3];

int main() {
    int t, i, cas = 0;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }

        clear();

        for (i = n; i >= 1; --i) {
            int s = sum(n) - sum(a[i]);
            
            b[0] = i;
            b[1] = a[i];
            b[2] = n - s;
            sort(b, b + 3);
            ans[ a[i] ] = b[2] - b[0];
            add(a[i], n, 1);
        }
        printf("Case #%d:", ++cas);

        for (i = 1; i <= n; ++i) {
            printf(" %d", ans[i]);
        }
        puts("");
    }

    return 0;
}

/*
10

7
7 5 4 6 2 3 1
*/