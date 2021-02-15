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
const int MAXN = 30;              // ��Ʒ���� 
const int MAXC = 1000010;         // �������� 
typedef int ValueType;            // ������ֵ������ 
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

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] += dp[j - knap[i].capacity];
			if(dp[j] >= 1e9) dp[j] -= 1e9;
		}
	}
}

//************************************ ��ȫ���� ģ�� ************************************

int main() {
	int n;
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < 30; ++i) {
			Knap[i] = Knapsack(1<<i, 0);
		} 
		zeroOneKnapsack(30, Knap, n);
		printf("%d\n", dp[n]);
	}
	
	return 0;
} 





