#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 3010;            // ��Ʒ���� 
const int MAXC = 3010;            // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = 1e9;       // �����ֵ����С������Сֵ����� 
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
    if (x == inf) return y;
    if (y == inf) return x;
    return x < y ? x : y;
}

vector <int> edges[MAXN];
int ssize[MAXN];
int c[MAXN], w[MAXN];

void calcSon(int father, int u) {
    ssize[u] = 1;
    for (int idx = 0; idx < edges[u].size(); ++idx) {
        int v = edges[u][idx];
        if (v == father) continue;                     // 4���������Ĵ���
        calcSon(u, v);
        ssize[u] += ssize[v];
    }
}

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;

    int maxCapacity = m;                               // 1����Ҫ������������
    for (i = 0; i <= m; ++i)                           // 2�����鱳��������ʼ��
        dp[u][i] = inf;
    if (ssize[u] == 1) {
        dp[u][1] = w[u];
    }
    dp[u][0] = 0;

    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3�����鱳��ö���飨1������1���飩
        int v = edges[u][idx];
        if (v == father) continue;                     // 4���������Ĵ���
        treeGroupKnapsack(u, v, maxCapacity);          // 5���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]

        for (i = ssize[u]; i >= 0; --i) {              // 6�����鱳������ö������
            for (j = 0; j <= i; ++j) {                 // 7��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                dp[u][i] = opt(
                    dp[u][i],
                    dp[u][i - j] + dp[v][j] + Knap[v].weight);
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
            ssize[i] = 0;
        }
        Knap[1].capacity = 0;
        Knap[1].weight = 0;
        for (i = 0; i < n - m; ++i) {
            int k;
            scanf("%d", &k);
            while (k--) {
                int c, w;
                scanf("%d %d", &c, &w);
                Knap[c].capacity = 0;
                Knap[c].weight = w;
                edges[i + 1].push_back(c);
            }
        }
        for (i = n - m + 1; i <= n; ++i) {
            int wv;
            scanf("%d", &wv);
            w[i] = -wv;
        }
        calcSon(-1, 1);
        treeGroupKnapsack(-1, 1, n);
        int ans = inf;
        for (i = m; i >= 0; --i) {
            if (dp[1][i] <= 0) {
                break;
            }
        }
        printf("%d\n", i);
    }
    return 0;
}