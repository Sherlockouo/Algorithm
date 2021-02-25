#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 110;           // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, ValueType w) : groupId(g), capacity(c), weight(w) {
    }

    bool operator < (const Knapsack& knap) const {
        return groupId < knap.groupId;
    }
}Knap[MAXN];

struct GroupKnapsack {
    vector <Knapsack> items;
    void clear() {
        items.clear();
    }
    void add(const Knapsack& knap) {
        items.push_back(knap);
    }
    int size() const {
        return items.size();
    }
    int getGroupId() {
        if (size()) {
            return items[0].groupId;
        }
        return -1;
    }
    const Knapsack& get(int idx) const {
        return items[idx];
    }
}GKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[0][i] = (!i) ? init : inf;
    }
}

int groupKnapsackRegroup(int knapsackSize, Knapsack *knap) {
    sort(knap, knap + knapsackSize);
    int groupId = -1;
    for (int i = 0; i < knapsackSize; ++i) {
        if (groupId == -1 || knap[i].groupId != GKnap[groupId].getGroupId())
            GKnap[++groupId].clear();

        GKnap[groupId].add(knap[i]);
    }
    return ++groupId;
}

// ע�⣺
// 1���������������ں�ԭ�������ж���
// 2�������п���Ϊ0��ע��״̬ת��˳���ȼ��㵱ǰ�顢�ټ�����һ��
int groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int k = 1; k <= groupSize; ++k) {
        for (int j = 0; j <= maxCapacity; ++j) {
            dp[k][j] = inf;
        }
        for (int i = 0, s = GKnap[k - 1].size(); i < s; ++i) {
            const Knapsack &item = GKnap[k - 1].get(i);
            for (int j = maxCapacity; j >= item.capacity; --j) {
                // ����ѡ��
                // 1) �ӵ�ǰ��״̬�������������Ʒ���Բ�ѡ��dp[i + 1][j]
                // 2���ӵ�ǰ��״̬�������������Ʒ����ѡ��dp[i + 1][j - item.capacity] + item.weight)
                // 3������һ��״̬�������������Ʒ����ѡ��dp[i][j - item.capacity] + item.weight
                dp[k][j] = opt(dp[k][j], dp[k][j - item.capacity] + item.weight);
                dp[k][j] = opt(dp[k][j], dp[k - 1][j - item.capacity] + item.weight);
            }
        }
    }
    return groupSize;
}

//************************************ ���鱳�� ģ�� ************************************

int main() {
    int n, m, g;
    int i;
    while (scanf("%d %d %d", &n, &m, &g) != EOF) {
        int tp = 0;
        for (i = 0; i < n; ++i) {
            int gid, cap, wei;
            scanf("%d %d %d", &gid, &cap, &wei);
            //gid = rand() % g + 1;
            //cap = rand()%150; wei = rand();
            Knap[tp++] = Knapsack(gid, cap, wei);
        }

        int groupSize = groupKnapsack(tp, Knap, m);
        int ans = inf;
        for (i = 0; i <= m; ++i) {
            ans = opt(ans, dp[groupSize][i]);
        }

        if (groupSize < g || ans < 0) {
            printf("Impossible\n");
        }
        else
        {
            printf("%d\n", ans);
        }

    }

    return 0;
}

/*
5 13 3
1 4 6
2 5 7
3 4 99
1 55 77
2 44 66

5 12 3
1 4 6
2 5 7
3 4 99
1 55 77
2 44 66

3 2 3
1 0 1
1 0 1
1 0 1


100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10
100 10000 10



3 5 2
1 2 2
1 3 10
2 3 2


1 100 2
1 0 0

1 100 1
1 0 0

1 100 1
1 0 1000

2 4 2
1 3 3
2 2 100

3 10000 3
1 4 6
2 5 7
3 4 99

4 0 4
1 0 0
2 0 0
3 0 0
4 0 0

4 0 5
2 0 0
3 0 0
4 0 0
5 0 0

4 0 4
1 0 10
2 0 10000
3 0 10
4 0 10


4
Impossible
0
1000
Impossible
112
0
Impossible
10030

*/