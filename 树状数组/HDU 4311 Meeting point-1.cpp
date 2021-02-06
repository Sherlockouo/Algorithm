/*
    ���⣺��ά�ռ��� n (n <= 100000) ���㣬��Χ�� [-10^9, 10^9]��Ҫ��ѡ��һ���㣬
    ʹ�������������е�������پ���֮����С��

    ��⣺�����Ǽ��������پ��룬���� x �� y ������ȫ����ص�����ά�ȣ��ǿ��Էֿ�����ġ�
    ����x�ᣬ�����е㰴�� x �����򣬼�������������֮��Ĳ�ֵ������״������ά��ǰ׺�͡�
    y��ͬ������
*/

#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

//***************************************** һά��״���� ģ�� *****************************************

#define MAXV 200100
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

struct Point {
    int x, y;
    int idx;
    void read(int i) {
        scanf("%d %d", &x, &y);
        idx = i;
    }

    static bool cmpx1(const Point& a, const Point& b) {
        return a.x < b.x;
    }

    static bool cmpx2(const Point& a, const Point& b) {
        return a.x > b.x;
    }

    static bool cmpy1(const Point& a, const Point& b) {
        return a.y < b.y;
    }
    
    static bool cmpy2(const Point& a, const Point& b) {
        return a.y > b.y;
    }

}P[MAXV];

int n;
ll ans[MAXV];

ll ABS(ll x) {
    return x > 0 ? x : -x;
}

void check(int tp) {
    int i;
    ll sns = sum(n - 1);
    for (i = 0; i < n; ++i) {
        ll sn = sns - sum(i);
        ll sb = (ll)(tp==0?P[i].x:P[i].y) * (n-i-1);
        ans[P[i].idx] += ABS(sn - sb);
    }
}

int main() {
    int t;
    int i;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            P[i].read(i);
        }
        memset(ans, 0, sizeof(ans));

        // ����x���������
        sort(P, P + n, Point::cmpx1);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].x );
        }
        check(0);

        // ����x�ݼ������
        sort(P, P + n, Point::cmpx2);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].x);
        }
        check(0);

        // ����y���������
        sort(P, P + n, Point::cmpy1);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].y);
        }
        check(1);

        // ����y�ݼ������
        sort(P, P + n, Point::cmpy2);
        clear();
        for (i = 1; i < n; ++i) {
            add(i, n, P[i].y);
        }
        check(1);

        int Min = 0;
        for (i = 0; i < n; ++i) {
            if (ans[i] < ans[Min]) {
                Min = i;
            }
        }
        printf("%lld\n", ans[Min]);

    }

    return 0;
}

/*
4
6
-4 -1
-1 -2
2 -4
0 2
0 3
5 -2
6
0 0
2 0
-5 -2
2 -2
-1 2
4 0
5
-5 1
-1 3
3 1
3 -1
1 -1
10
-1 -1
-3 2
-4 4
5 2
5 -4
3 -1
4 3
-1 -2
3 4
-2 2
*/