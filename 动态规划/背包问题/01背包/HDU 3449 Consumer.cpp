/*
	���⣺ n (n <= 40) ����Ʒ��ÿ����ƷҪ����֮ǰ�������ȹ���һ�����ӣ���
	����õ�������ֵ��
	
	��⣺ 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 50;              // ��Ʒ���� 
const int MAXC = 200010;          // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1000000000;// �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

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

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity, int base) {
	
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= base + knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - base - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************

int main() {
	int n, w;
	int i, j;
	int p, k;
	
	while(scanf("%d %d", &n, &w) != EOF) {
		zeroOneKnapsackInit(w);
		for(i = 0; i < n; ++i) {
			
			scanf("%d %d", &p, &k);
			for(j = 0; j < k; ++j) {
				int c, v;
				scanf("%d %d", &c, &v);
				Knap[j] = Knapsack(c, v);
			}
			zeroOneKnapsack(n, Knap, w, p);
		}
		int Max = 0;
		for(i = 0; i <= w; ++i) {
			Max = opt(dp[i], Max);
			if(dp[i] > 0) {
				printf("%d %d\n", i, dp[i]);
			}
		}
		printf("%d\n", Max);
	} 
	
	return 0; 
} 





