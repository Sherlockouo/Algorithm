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
const int MAXN = 4;               // ��Ʒ���� 
const int MAXC = 2000010;         // �������� 
typedef bool ValueType;           // ������ֵ������ 
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
	int t;
	scanf("%d\n", &t);
	while(t--) {
		for(int i = 0; i < 4; ++i) {
			int x;
			scanf("%d", &x);
			Knap[i] = Knapsack(x, 0);
		}
		zeroOneKnapsack(4, Knap, 2000000);
		
		int ans = 0;
		int val = -1;
		for(int i = 1; i <= 2000000; ++i) {
			if(!dp[i] && i <= 1000000) {
				ans ++;
				val = i;
			}
			if( i > 1000000 && !dp[i]) {
				val = -1;
				break;
			}
		}
		printf("%d\n%d\n", ans, val);
		
	}
	
	return 0;
} 





