#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 160;             // ��Ʒ���� 
const int MAXC = 160;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = 1e9;        // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x < y ? x : y;
}

vector <int> edges[MAXN];

void treeGroupKnapsack(int father, int u, int maxCapacity) {
    int i, j, k;
    int cap[2][MAXC], pre = 0;
    int s = 0;
    for (i = 0; i < edges[u].size(); ++i) {         // 2�����鱳��ö���飨1������1���飩
        int v = edges[u][i];
        if (v == father) continue;
        ++s;
    }

    for (i = 0; i <= maxCapacity; ++i)              // 1�����鱳��������ʼ��
        cap[0][i] = i == 1 ? s : inf;

    for (i = 0; i < edges[u].size(); ++i) {         // 2�����鱳��ö���飨1������1���飩
        int v = edges[u][i];
        if (v == father) continue;
        treeGroupKnapsack(u, v, maxCapacity);      // 3���ݹ�����ӽ���������״̬ dp[v][0 ... maxCapacity - mat[u][v]]
        for (j = maxCapacity; j >= 0; --j) {       // 4�����鱳������ö������        
            cap[pre ^ 1][j] = cap[pre][j];     // ����Ϊ0����ֵΪ0����Ʒ

            for (k = 1; k <= j; ++k) {
                // 5��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                // ע��һ��Ҫ��������Ϊ 0 �����
                cap[pre ^ 1][j] = opt(
                    cap[pre ^ 1][j],
                    cap[pre][j - k] + dp[v][k] - 1
                    );
            }


        }
        pre ^= 1;
    }

    for (i = 0; i <= maxCapacity; ++i) {
        dp[u][i] = cap[pre][i];
    }
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************

int main() {
    int n, t;
    int i;
    while (scanf("%d %d", &n, &t) != EOF) {
        for (i = 1; i <= n; ++i) {
            edges[i].clear();
        }
        for (i = 0; i < n - 1; ++i) {
            int x, y;
            scanf("%d %d", &x, &y);
            edges[x].push_back(y);
            edges[y].push_back(x);
        }

        int ans = inf;
        for (int root = 1; root <= 1; ++root) {
            treeGroupKnapsack(0, root, n);
            for (i = 1; i <= n; ++i) {
                if (root == i) ans = opt(ans, dp[root][t]);
                else {
                    ans = opt(ans, dp[i][t] + 1);
                }
                //printf("%d\n", dp[i][t]);
            }

        }


        printf("%d\n", ans);
    }
    return 0;
}

/*
11 6
1 2
1 3
1 4
1 5
2 6
2 7
2 8
4 9
4 10
4 11

*/