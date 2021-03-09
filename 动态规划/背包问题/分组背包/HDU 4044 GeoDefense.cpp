#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 1010;             // ��Ʒ���� 
const int MAXC = 210;              // �������� 
typedef int ValueType;             // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;          // һ�����������ֵ������Сֵ�����̶�Ϊ 0 
const ValueType MAX = 1e9;

ValueType dp[MAXN][MAXC];

ValueType opt(ValueType x, ValueType y) {
    if (x == inf) return y;
    if (y == inf) return x;
    return x > y ? x : y;
}

ValueType opt(ValueType x, ValueType y, ValueType z) {
    return opt(opt(x, y), z);
}

vector <int> edges[MAXN];
int c[MAXN][55], w[MAXN][55];
int ksize[MAXN];

struct Knap {
    int c, w;
    Knap() {}

    Knap(int _c, int _w) : c(_c), w(_w) {

    }
};


// ��¼һ�������� �� ��ֵ ����������
vector <Knap> dpv[MAXN];


bool check(int hp, int cap, int father, int u) {
    bool leaves = true;
    for (int idx = 0; idx < edges[u].size(); ++idx) {
        int v = edges[u][idx];
        if (v == father) continue;
        leaves = false;
        int l = 0, r = dpv[v].size() - 1;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (dpv[v][mid].w >= hp) {
                r = mid - 1;
                ans = mid;
            }
            else {
                l = mid + 1;
            }
        }
        // ѡ�� v ����·���Ҳ���Ѫ���ڵ��� hp ��·
        if (ans == -1) {
            return false;
        }
        // ̰�ĵĿ����������ǿ۳��˸��ģ�Ҳ�޷���������
        cap -= dpv[v][ans].c;
        if (cap < 0) {
            return false;
        }
    }
    if (leaves) {
        return hp == 0;
    }
    return true;
}

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    for (int idx = 0; idx < edges[u].size(); ++idx) {
        int v = edges[u][idx];
        if (v == father) continue;
        treeGroupKnapsack(u, v, m);
        dpv[v].clear();
        for (int j = 0; j <= m; ++j) {

            int tidx = dpv[v].size();
            if (tidx == 0 || dp[v][j] > dpv[v][tidx - 1].w) {
                dpv[v].push_back(Knap(j, dp[v][j]));
            }
        }
    }

    for (int i = 0; i <= m; ++i) {
        dp[u][i] = inf;
    }
    dp[u][0] = 0;

    // Ŀǰ���� dp[u][i] ��ʾ���ӽ������ܹ� i ���������ܹ��ﵽ�����ֵ
    for (int i = m; i >= 0; --i) {
        int cap = i;
        int l = 0;
        int r = MAX;
        int ans = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid, cap, father, u)) {
                ans = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        if (ans != -1) {
            // ̰�ĵõ��������С·
            dp[u][i] = opt(dp[u][i], ans);
        }
    }
    int ncap[MAXN];

    for (int i = 0; i <= m; ++i) ncap[i] = dp[u][i];


    for (i = m; i >= 0; --i) {
        for (int ki = 0; ki < ksize[u]; ++ki) {
            if (i - c[u][ki] < 0) {
                continue;
            }
            dp[u][i] = opt(dp[u][i], ncap[i - c[u][ki]] + w[u][ki]);
        }
    }
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************

int n, m;

int main() {
    int i, j;
    int t;

    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 1; i <= n; ++i) {
            edges[i].clear();
        }
        for (i = 0; i < n - 1; ++i) {
            int u, v;
            u = i + 1, v = i + 2;
            scanf("%d %d", &u, &v);

            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        scanf("%d", &m);
        for (i = 1; i <= n; ++i) {
            ksize[i] = 50;
            scanf("%d", &ksize[i]);

            for (j = 0; j < ksize[i]; ++j) {
                c[i][j] = rand() % 200, w[i][j] = rand() % 200;
                scanf("%d %d", &c[i][j], &w[i][j]);

            }
            c[i][ksize[i]] = 0;
            w[i][ksize[i]] = 0;
            ksize[i]++;
        }

        treeGroupKnapsack(-1, 1, m);

        int ans = inf;
        for (i = 0; i <= m; ++i) {
            ans = opt(ans, dp[1][i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*

10
4
1 2
1 3
2 4
6
3 1 20 2 40 3 50
3 1 40 2 60 3 45
3 1 50 2 70 3 315
3 1 60 2 40 3 35


ע����������
2
1 2
1
2 0 22 0 22
2 0 22 0 22



*/