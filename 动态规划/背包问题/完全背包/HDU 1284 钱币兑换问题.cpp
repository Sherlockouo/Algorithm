/*
    ���⣺3����Ʒ���ֱ�۸�Ϊ 1,2,3�����ڸ���һ���۸� n (n <= 32767);
    ���ж�����Ϸ�����
     
    ��⣺��ȫ����
     
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 3;               // ��Ʒ���� 
const int MAXC = 32768;           // �������� 
typedef long long ValueType;      // ������ֵ������ 
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
    return x + y;
}

void zeroOneKnapsackInit(int maxCapacity) {
    for(int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
    } 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
    zeroOneKnapsackInit(maxCapacity);
    for(int i = 0; i < knapsackSize; ++i) {
        for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
            dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
        }
    }
}

//************************************ ��ȫ���� ģ�� ************************************

int main() {
    Knap[0] = Knapsack(1, 0);
    Knap[1] = Knapsack(2, 0);
    Knap[2] = Knapsack(3, 0);
    zeroOneKnapsack(3, Knap, MAXC-1);
    
    int n;
    while(scanf("%d", &n) != EOF) {
        printf("%lld\n", dp[n]);
    }
    
    return 0;
} 

