#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 210;             // ��Ʒ���� 
const int MAXC = 40010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

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
        dp[i] = (!i) ? init : inf;
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

void groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int i = 0; i < groupSize; ++i) {
        for (int j = maxCapacity; j >= 0; --j) {
            for (int k = 0, s = GKnap[i].size(); k < s; ++k) {
                const Knapsack &item = GKnap[i].get(k);
                if (j >= item.capacity)
                    dp[j] = opt(dp[j], dp[j - item.capacity] + item.weight);
            }
        }
    }
}

//************************************ ���鱳�� ģ�� ************************************

/*
    ���⣺һ�� n(n <= 10000) ������������ S ���������� K ������Ҫ����������н�㣬����С�ķѣ�
    �ķѷ����ڱ��ϡ�

    ��⣺���� K Ϊ 1 �������
    dp[u][0] ��ʾ�� u ��������������������С���ģ�
    dp[u][1] ��ʾ�� u �����������������ٻص� u ����С���ģ�

    dp[u][1] = sum( dp[v][1] + 2 * cost(u, v) );
    dp[u][0] = min( x ��ʾ��x��ȥ�󲻻����� | dp[u][1] - (dp[x][1] + 2 * cost(u, x)) + dp[x][0] + cost(u, x))
    

    ����Ҷ�ӽ�㣺  dp[u][0] = dp[u][1] = 0;
*/