#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 410;             // ��Ʒ���� 
const int MAXC = 15010;           // ��������
const int CBASE = 7500;           // ������ƫ��ֵ
typedef long long ValueType;      // ������ֵ������ 
const ValueType inf = 0;          // �����ֵ����С������Сֵ����� 
const ValueType init = 1;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[2][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, ValueType w) : groupId(g), capacity(c),  weight(w) {
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

void groupKnapsackInit(int minCapacity, int maxCapacity) {
    for (int i = minCapacity; i <= maxCapacity; ++i) {
        dp[0][i + CBASE] = (!i) ? init : inf;
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

int groupKnapsack(int knapsackSize, Knapsack *knap, int minCapacity, int maxCapacity) {
    groupKnapsackInit(minCapacity, maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    int last = 0, cur = 1;
    for (int k = 0; k < groupSize; ++k) {
        for (int j = minCapacity; j <= maxCapacity; ++j) {
            dp[cur][j + CBASE] = 0;
            for (int i = 0, s = GKnap[k].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k].get(i);

                if (j - item.capacity < minCapacity) continue;
                if (j - item.capacity > maxCapacity) continue;

                dp[cur][j + CBASE] += dp[last][j - item.capacity + CBASE];
            }
        }
        last ^= 1;
        cur ^= 1;
    }
    return last;
}

//************************************ ���鱳�� ģ�� ************************************

/*
    ���⣺
    һ����ƽ��C(C <= 20)�����ӣ�G(G <= 20)������
    ÿ�����ӵķ�Χ -15 ~ 15
    ÿ������ķ�Χ 1 ~ 25

    �ʽ�ÿ��������϶�Ӧ�Ĺ��ӣ����ʹ����ƽƽ��ķ�����

    ���鱳��

    1����ƽƽ��������  ���� = ���� * ����   �������߾���ֵ���
    2��ÿ������ * ÿ��λ�� �õ�һ�� ���أ�ע���������������Զ���ÿ�������飬�� C ��ѡ��
    3������ 20 ������ֵ��Ϊ 25�����������Ե���õ��������Ϊ 15*20*25 = 7500�������ؾ��� -7500
    ���Կ����趨һ�� 7500 ��ƫ�������������������Ϊ 15010 ��10Ϊ�ݴ�ֵ��
    4��Ȼ����Ƕ�ÿ��������������ȡ1���ķ��鱳���ˡ�
    5) ��������������������˳��������ö�ٶ������⣬��õĽ���취���ǹ�������
*/

int pos[25], items[25];

int main() {
    int C, G;
    int i, j;
    while (scanf ("%d %d", &C, &G) != EOF) {
        for (i = 0; i < C; ++i) {
            scanf("%d", &pos[i]);
        }
        for (i = 0; i < G; ++i) {
            scanf("%d", &items[i]);
        }
        int tp = 0;
        int minCap = 0, maxCap = 0;
        for (i = 0; i < G; ++i) {
            for (j = 0; j < C; ++j) {
                Knap[tp++] = Knapsack(i, pos[j] * items[i], 0);
            }
            minCap += items[i] * pos[0];
            maxCap += items[i] * pos[C - 1];
        }

        int last = groupKnapsack(tp, Knap, minCap, maxCap);

        ValueType ans = dp[last][0 + CBASE];

        printf("%lld\n", ans);
    }
    return 0;
}

/*
2 8
-15 15
1 2 3 4 5 6 7 8

2 6
-1 1
1 2 3 4 5 6

2 2
-15 15
25 25

2 3
-1 1
1 2 3

2 20
-15 15
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/