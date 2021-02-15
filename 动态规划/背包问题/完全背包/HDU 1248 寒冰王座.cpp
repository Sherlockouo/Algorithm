/*
	���⣺3����Ʒ���ֱ�۸�Ϊ 150��200��350�����ڸ���һ���۸� n (n <= 10000);
	
	��⣺��ȫ����
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 3;               // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
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
	Knap[0] = Knapsack(150, 0);
	Knap[1] = Knapsack(200, 0);
	Knap[2] = Knapsack(350, 0);
	zeroOneKnapsack(3, Knap, 10000);
	
	int t, n, ans;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = n; i >= 0; --i) {
			if(dp[i]) {
				ans = n - i;
				break;
			}
		}
		printf("%d\n", ans);
	}

	
	return 0;
} 





