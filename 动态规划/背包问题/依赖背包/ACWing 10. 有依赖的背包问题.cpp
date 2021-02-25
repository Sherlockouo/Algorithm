#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 110;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
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
    return x > y ? x : y;
}

vector <int> edges[MAXN];

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    int maxCapacity = m - Knap[u].capacity;
    for (i = 0; i <= maxCapacity; ++i)              // 1�����鱳��������ʼ��
        dp[u][i] = init;
    for (i = 0; i < edges[u].size(); ++i) {         // 2�����鱳��ö���飨1������1���飩
        int v = edges[u][i];
        if (v == father) continue;
        treeGroupKnapsack(u, v, maxCapacity);       // 3���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]
        for (j = maxCapacity; j >= 0; --j) {        // 4�����鱳������ö������
            for (k = 0; k <= j; ++k) {               
                                                    // 5��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                                                    // ע��һ��Ҫ��������Ϊ 0 ��������������Ҳ���ܹ�����״̬ת�Ƶ�
                dp[u][j] = opt(
                    dp[u][j], 
                    dp[u][j - k] + dp[v][k]
                );
            }
        }
    }
    for (i = m; i >= Knap[u].capacity; --i)         // 6��������ѡ
        dp[u][i] = dp[u][i - Knap[u].capacity] + Knap[u].weight;
    for (i = 0; i < Knap[u].capacity; ++i) 
        dp[u][i] = init;
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************

int main() {
    int n, m;
    int i;
    while (scanf("%d %d", &n, &m) != EOF) {
        for (i = 1; i <= n; ++i) edges[i].clear();
        int root;
        for (i = 1; i <= n; ++i) {
            int cap, val, fat;
            scanf("%d %d %d", &cap, &val, &fat);
            Knap[i] = Knapsack(cap, val);
            if (fat == -1) {
                root = i;
            }
            else {
                edges[fat].push_back(i);
            }
        }

        treeGroupKnapsack(0, root, m);

        printf("%d\n", dp[root][m]);
    }

    return 0;
}

/*
5 0
10 10
10 10
10 20
1 30
1 35
1 2
1 3
2 4
2 5

10 10
3 4 9
1 3 3
4 5 7
5 9 1
4 4 10
2 3 1
2 6 1
2 1 1
2 1 -1
4 6 2
*/