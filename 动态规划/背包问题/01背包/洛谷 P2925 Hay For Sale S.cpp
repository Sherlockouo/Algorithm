#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 5010;            // ��Ʒ���� 
const int MAXC = 50010;           // �������� 
typedef bool ValueType;            // ������ֵ������ 
const ValueType inf = 0;          // �����ֵ����С������Сֵ����� 
const ValueType init = 1;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

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
    return x || y;
}

void zeroOneKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    }
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    zeroOneKnapsackInit(maxCapacity);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = maxCapacity; j >= knap[i].capacity; --j) {
            dp[j] |= dp[j - knap[i].capacity];
        }
    }
}

//************************************ 01���� ģ�� ************************************

int main() {
    int C, H;
    while (scanf("%d %d", &C, &H) != EOF) {
        for (int i = 0; i < H; ++i) {
            int a;
            scanf("%d", &a);
            Knap[i] = Knapsack(a, 0);
        }
        zeroOneKnapsack(H, Knap, C);
        int ans;
        for (int i = C; i >= 0; --i) {
            if (dp[i]) {
                ans = i;
                break;
            }
        }
        printf("%d\n");
    }
    return 0;
}