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
    int cap[2][MAXN], pre = 0;

    int maxCapacity = m - Knap[u].capacity;
    for (i = 0; i <= maxCapacity; ++i)              // 1�����鱳��������ʼ��
        cap[0][i] = 0;
    for (i = 0; i < edges[u].size(); ++i) {         // 2�����鱳��ö���飨1������1���飩
        int v = edges[u][i];
        if (v == father) continue;
        treeGroupKnapsack(u, v, maxCapacity);       // 3���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]
        for (j = maxCapacity; j >= 0; --j) {        // 4�����鱳������ö������
            cap[pre ^ 1][j] = cap[pre][j];
            for (k = 0; k <= j; ++k) {
                // 5��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                // ע��һ��Ҫ��������Ϊ 0 �����
                cap[pre ^ 1][j] = opt(
                    cap[pre^1][j],
                    cap[pre][j - k] + dp[v][k]
                    );
            }
        }
        pre ^= 1;
    }
    for (i = m; i >= Knap[u].capacity; --i)         // 6��������ѡ
        dp[u][i] = cap[pre][i - Knap[u].capacity] + Knap[u].weight;
    for (i = 0; i < Knap[u].capacity; ++i)
        dp[u][i] = 0;

    // ����ʱ�������� bugs Ϊ 0ҲҪ������һ��ɡ����ȥ
    dp[u][0] = 0;
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************
int main() {
    int n, m;
    int i;
    while (scanf("%d %d", &n, &m) != EOF && (n != -1 || m != -1)) {
        for (int i = 1; i <= n; ++i) {
            int cap, val;
            scanf("%d %d", &cap, &val);
            cap = (cap + 19) / 20;
            Knap[i] = Knapsack(cap, val);
            edges[i].clear();
        }
        for (i = 0; i < n - 1; ++i) {
            int u, v;
            scanf("%d %d", &u, &v);
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        treeGroupKnapsack(0, 1, m);
        printf("%d\n", dp[1][m]);
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


5 0
10 1
0 2
0 3
1 3
0 4
1 2
2 3
3 4
4 5

8 2
0 0
0 9
0 8
0 4
0 7
0 3
0 2
0 1
1 2
1 3
2 4
2 5
4 6
6 7
7 8
*/