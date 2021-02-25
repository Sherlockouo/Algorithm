#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 10010;            // ��Ʒ���� 
const int MAXC = 10000010;         // �������� 
typedef long long ValueType;       // ������ֵ������ 
const ValueType inf = -1e9;        // �����ֵ����С������Сֵ����� 
const ValueType init = 0;          // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

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

void completeKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    }
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    completeKnapsackInit(maxCapacity);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = knap[i].capacity; j <= maxCapacity; ++j) {
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

//************************************ ��ȫ���� ģ�� ************************************

int main() {
    int cap, n;
    while (scanf("%d %d", &cap, &n) != EOF) {
        for (int i = 0; i < n; ++i) {
            int cap, wei;
            scanf("%d %d", &cap, &wei);
            Knap[i] = Knapsack(cap, wei);
        }
        completeKnapsack(n, Knap, cap);
        int ans = inf;
        for (int i = 0; i <= cap; ++i) {
            ans = opt(ans, dp[i]);
        }
        printf("%lld\n", ans);
    }
}