/*
	�� 0/1 ���� 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 3500;              // ��Ʒ���� 
const int MAXC = 13000;             // �������� 
typedef int ValueType;              // ������ֵ������ 
const ValueType inf = -1000000000;  // �����ֵ����С������Сֵ����� 
const ValueType init = 0;            // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

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

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = !i ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	int maxC = 0;
	for(int i = 0; i < knapsackSize; ++i) {
		maxC += knap[i].capacity;
		if(maxC > maxCapacity) {
			maxC = maxCapacity;
		}
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************

int main() {
	int n, w;
	int i, j;
	int p, k;
	
	while(scanf("%d %d", &n, &w) != EOF) {
		for(i = 0; i < n; ++i) {
			int c, w;
			scanf("%d %d", &c, &w);
			Knap[i] = Knapsack(c, w);
		}
		zeroOneKnapsack(n, Knap, w);
		int Max = 0;
		for(i = 0; i <= w; ++i) {
			Max = opt(dp[i], Max);
		}
		printf("%d\n", Max);
	} 
	
	return 0; 
} 





