#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 210;             // ��Ʒ���� 
const int MAXC = 210;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1;         // �����ֵ����С������Сֵ����� 
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

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    ssize[u] = 1;
    int maxCapacity = m;                               // 1����Ҫ������������
    for (i = 1; i <= m; ++i)                           // 2�����鱳��������ʼ��
        dp[u][i] = inf;
    dp[u][0] = 0;

    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3�����鱳��ö���飨1������1���飩
        int v = edges[u][idx];
        if (v == father) continue;                     // 4���������Ĵ���
        treeGroupKnapsack(u, v, maxCapacity);          // 5���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]
        ssize[u] += ssize[v];
        for (i = maxCapacity; i >= 0; --i) {           // 6�����鱳������ö������
            for (j = 0; j <= i; ++j) {                 // 7��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о���
                if (dp[u][i - j] == inf || dp[v][j] == inf) continue;
                dp[u][i] = opt(
                    dp[u][i],
                    dp[u][i - j] + dp[v][j]);
            }
        }
    }

    // ���һ��ѡ�񣬸��������
    int s = ssize[u];
    dp[u][s] = opt(dp[u][s], dp[u][0] + Knap[u].weight);

}

//************************************ ���Ϸ��鱳�� ģ�� ************************************

const int MAXL = 110;

char name[50010];
char names[MAXN][MAXL];
char tmpname[MAXN][MAXL];
int namecnt;
int in[MAXN];

int findname(char *name) {
    for (int i = 0; i < namecnt; ++i) {
        if (strcmp(name, names[i]) == 0) {
            return i;
        }
    }
    strcpy(names[namecnt], name);
    return namecnt++;
}

int main() {
    int n, m;
    int i, j;
    while (gets(name)) {
        if (strcmp(name, "#") == 0) {
            break;
        }
        for (i = 0; i < MAXN; ++i) edges[i].clear(), ssize[i] = 0, in[i] = 0;
        namecnt = 0;
        sscanf(name, "%d %d", &n, &m);

        while (n--) {
            gets(name);
            int len = strlen(name);
            int s = 0, now = 0, idx = 0;

            for (i = 0; i <= len; ++i) {
                if (name[i] == ' ' || name[i] == '\0') {
                    if (idx) {
                        tmpname[now++][idx] = '\0';
                        idx = 0;
                    }
                }
                else {
                    tmpname[now][idx++] = name[i];
                }
            }
            int u = findname(tmpname[0]);
            int w;
            sscanf(tmpname[1], "%d", &w);
            Knap[u] = Knapsack(-100000, w);
            for (i = 2; i < now; ++i) {
                int v = findname(tmpname[i]);
                edges[u].push_back(v);
                ++in[v];
            }
        }

        for (i = 0; i < namecnt; ++i) {
            if (!in[i]) {
                edges[namecnt].push_back(i);
            }
        }

        treeGroupKnapsack(-1, namecnt, namecnt);
        int ans = inf;
        for (i = m; i <= namecnt; ++i) {
            ans = opt(ans, dp[namecnt][i]);
        }
        printf("%d\n", ans);
    }

    return 0;
}

/*
9 0
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 1
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 2
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 3
1 10 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000

9 9
1 10000000 2 3 4
2 1 5 6
3 100 8 9
4 1000 7
5 10000
6 100000
7 1000000
8 1000000
9 100000
*/