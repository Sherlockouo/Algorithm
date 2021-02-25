#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 510;             // ��Ʒ���� 
const int MAXC = 3010;            // �������� 
typedef double ValueType;         // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];
int pre[MAXN][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    int count;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, int cnt, ValueType w) : groupId(g), capacity(c), count(cnt), weight(w) {
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
        pre[0][i] = -1;
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

int groupKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    groupKnapsackInit(maxCapacity);
    int groupSize = groupKnapsackRegroup(knapsackSize, knap);
    for (int k = 1; k <= groupSize; ++k) {
        for (int j = maxCapacity; j >= 0; --j) {

            dp[k][j] = inf;
            pre[k][j] = -1;

            for (int i = 0, s = GKnap[k-1].size(); i < s; ++i) {
                const Knapsack &item = GKnap[k-1].get(i);

                if (dp[k - 1][j] > dp[k][j]) {
                    dp[k][j] = dp[k - 1][j];
                    pre[k][j] = MAXC * (k - 1) + j;
                }

                if (j >= item.capacity) {
                    if (dp[k - 1][j - item.capacity] + item.weight > dp[k][j]) {
                        dp[k][j] = dp[k - 1][j - item.capacity] + item.weight;
                        pre[k][j] = MAXC * (k - 1) + j - item.capacity;
                    }
                }
            }
        }
    }
    return groupSize;
}

//************************************ ���鱳�� ģ�� ************************************

/*
    ���⣺n(n <= 1000) �������������1��Ұ�ֵĳ�ʼλ�ã�Ұ���ߵ��κ�һ��Ҷ�ӽ�����Ӯ�ˣ������ͨ�����·�ʽ
    ��ֹҰ�ֽ���Ҷ�ӽ�㣻

    1��ÿ����㶼���������� 1 ������
    2����Ұ�־��������㣬��ֻ�ܽ���һ�������
    3��ÿ������ 50��ѡ���� ��ֵv���˺�p ����ʽ������
    4����Ұ�ֵ�Ѫ��С�ڵ���0��Ұ�ֱ����ܣ�
    5���������Ҷ�ӽ���1�Ž�㽨������Ҳ����Ч�ģ�
   
    �ʸ��� m �Ľ�����������������Ұ�ֵ� HP ��������ʱ��������Ϊ����

    ��⣺����˼·��
    1��Ұ���㹻�������϶���ѡ������һ���� 1�Ž�� �� Ҷ�ӽ�� ��·���������ۻأ�
    2������ 1�����˺���С������·���ͳ�Ϊ��ƿ��������������Ҫʹ���˺���С��·��������
    3���� dp[i][j] ��ʾ�� i ��������ӵ�� j �Ľ�Ǯ �ܹ���ɵ� "�����С�˺�"��
    3�������� u Ϊ������������һ�����������ӽڵ㵽Ҷ�ӽ���ܹ�����˺����½� K 
    
    Ҳ���Ǵ� u �����������������ܹ����ܵ��˺� >= K���������������£���ÿ���ӽ��
    ��һ����С���ģ���������ļ�����С�ڵ��ڵ�ǰ

    
*/

