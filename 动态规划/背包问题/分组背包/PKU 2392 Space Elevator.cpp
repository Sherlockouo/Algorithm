#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 4010;            // ��Ʒ���� 
const int MAXC = 40010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = 0;       // �����ֵ����С������Сֵ����� 
const ValueType init = 1;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

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


void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? 1 : 0;
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
    for (int k = 0; k < groupSize; ++k) {
        if (GKnap[k].size() <= 0) continue;
        for (int j = GKnap[k].get(0).weight; j >= 0; --j) {
            for (int i = 0, s = GKnap[k].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k].get(i);
                if (j >= item.capacity)
                    dp[j] |= dp[j - item.capacity];
            }
        }
    }
}

//************************************ ���鱳�� ģ�� ************************************

/*
���⣺���� K �����ӣ� ����Ԫ�� (h, a, c) ��ʾ��h ��ʾ�߶ȣ�a ��ʾ���Σ�c ��ʾ����
Ҫ����Щ���Ӵ�����������ÿ�����Ӳ��ܳ���������ĺ������ƣ�����߿��Դ��ߡ�

��⣺��ÿ���������� c ����Ʒ��ÿ����Ʒ�� (��ţ���������ֵ) ��ʾ�ܹ�����
sum(c) = 4000 ����Ʒ��Ȼ���պ��ν�������
��ͬ���εİ����������Ȼ�����һ��ÿ�����Լ����������޵ķ��鱳�������ˡ�
*/

struct Items {
    int h, a, c;

    void read() {
        scanf("%d %d %d", &h, &a, &c);
    }
    bool operator < (const Items& I) const  {
        return a < I.a;
    }
}I[410];

int main() {
    int i, j;
    int K;
    while (scanf("%d", &K) != EOF) {
        for (i = 0; i < K; i++) {
            I[i].read();
        }
        sort(I, I + K);
        int tp = 0;
        for (i = 0; i < K; ++i) {
            for (j = 0; j <= I[i].c && j * I[i].h <= I[i].a; ++j) {
                Knap[tp++] = Knapsack(i, j * I[i].h, I[i].a);
            }
        }
        groupKnapsack(tp, Knap, I[K - 1].a);
        for (i = I[K - 1].a; i >= 0; --i) {
            if (dp[i]) break;
        }
        printf("%d\n", i);

    }

    return 0;
}