/*
	���⣺�����е�Ǯ����� 10^6�� ����Ʋ�Ʒ������� 40�꣬�� 40���������ʣ�¶���Ǯ�� 
	ע�⣺ÿ����Ʋ�Ʒ�Ĺ���۸��� 1000 �ı�����
	 
	��⣺��ȫ����
	��Ϊÿ����Ʋ�Ʒ�ļ۸��� 1000 �ı��������Կ��Խ���Ʋ�Ʒ������ 1000 �Ժ��ٽ��б����� 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 20;              // ��Ʒ���� 
const int MAXC = 1000000;         // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
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

void completeKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void completeKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	completeKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = knap[i].capacity; j <= maxCapacity; ++j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ ��ȫ���� ģ�� ************************************

int main() {
	int t;
	int s, y;
	int n;
	
	scanf("%d", &t);
	while( t-- ) {
		scanf("%d %d", &s, &y);
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			int c, w;
			scanf("%d %d", &c, &w);
			Knap[i] = Knapsack(c / 1000, w);
		}
		while(y--) {
			int v = s / 1000;
			
			completeKnapsack(n, Knap, v);
			
			int ans = inf;
			for(int i = v; i >= 0; --i) {
				ans = opt(ans, dp[i]);
			}
			s += ans;
			//printf("%d\n", ans);
		}
		printf("%d\n", s);
	}
	return 0;
} 





