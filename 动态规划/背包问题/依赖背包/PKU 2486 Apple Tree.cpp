#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 110;            // ��Ʒ���� 
const int MAXC = 210;            // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[2][MAXN][MAXC];

ValueType opt(ValueType x, ValueType y) {
    if (x == inf) return y;
    if (y == inf) return x;
    return x > y ? x : y;
}

ValueType opt(ValueType x, ValueType y, ValueType z) {
    return opt(opt(x, y), z);
}

vector <int> edges[MAXN];
int w[MAXN];


void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;

    int maxCapacity = m;                               // 1����Ҫ������������
    for (i = 1; i <= m; ++i)                           // 2�����鱳��������ʼ��
        dp[0][u][i] = dp[1][u][i] = inf;
    dp[0][u][0] = w[u];
    dp[1][u][0] = w[u];

    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3�����鱳��ö���飨1������1���飩
        int v = edges[u][idx];
        if (v == father) continue;                     // 4���������Ĵ���
        treeGroupKnapsack(u, v, maxCapacity);          // 5���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]

        for (i = m; i >= 0; --i) {
            for (j = 0; j <= i - 1; ++j) {
                int a = dp[0][u][i - 1 - j] + dp[1][v][j];
                int b = j == i - 1 ? inf : dp[0][v][j] + dp[1][u][i - 2 - j];
                dp[1][u][i] = opt(dp[1][u][i], a, b);
            }
        }

        for (i = m; i >= 0; --i) {              // 6�����鱳������ö������
            for (j = 0; j <= i - 2; ++j) {                 // 7��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                dp[0][u][i] = opt(dp[0][u][i], dp[0][u][i - 2 - j] + dp[0][v][j]);
            }
        }


    }
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************

int n, m;

int main() {
    int i;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (i = 1; i <= n; ++i) {
            edges[i].clear();
            scanf("%d", &w[i]);
        }
        for (i = 0; i < n - 1; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            edges[x].push_back(y);
            edges[y].push_back(x);
        }
        treeGroupKnapsack(-1, 1, m);
        int ans = inf;
        for (i = 0; i <= m; ++i) {
            ans = opt(ans, dp[0][1][i]);
            ans = opt(ans, dp[1][1][i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}

/*
2 1
0 11
1 2

3 2
0 1 2
1 2
1 3

10 1
1 2 4 8 16 32 64 128 256 512
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
4 10

10 2
1 2 4 8 16 32 64 128 256 512
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
4 10

10 4
1 2 4 8 16 32 64 128 256 512
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
4 10

10 6
1 2 4 8 16 32 64 128 256 512
1 2
1 3
1 4
2 5
2 6
2 7
3 8
3 9
4 10
*/