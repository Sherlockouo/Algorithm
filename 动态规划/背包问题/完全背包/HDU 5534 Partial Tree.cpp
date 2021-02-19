/*
	���ģ�����ͼ�����ܺ� = ���� * 2�����Ķ����ܺ� = 2*n-2
	
	ÿ���ȿ����Ǳ�����������ֵ�����Ǳ����ļ�ֵ��������ȫ���� 
	
	ע�ⱳ����Ʒ�ĸ�������Ϊ n ����������Ҫ����һά���� ��Ʒ����  
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;


//************************************ ��ȫ���� ģ�� ************************************
const int MAXN = 2020;              // ��Ʒ���� 
const int MAXC = 4040;              // �������� 
typedef int ValueType;              // ������ֵ������ 
const ValueType inf = -1e9;         // �����ֵ����С������Сֵ����� 
const ValueType init = 0;           // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

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
		for(int k = knap[i].capacity; k <= maxCapacity; ++k) {
			dp[k] = opt(dp[k], dp[k - knap[i].capacity] + knap[i].weight);			
		}
	}
}

//************************************ ��ȫ���� ģ�� ************************************

int main() {
	int t;
	int n, i, j;
	
	scanf ("%d", &t);
	
	while(t--) {
		scanf("%d", &n);
		int d0 = 0;
		for(i = 0; i < n - 1; ++i) {
			int d;
			scanf("%d", &d);
			if(i == 0) {
				d0 = d;
			}
			if(i > 0)
				Knap[i-1] = Knapsack(i, d - d0);
		}
		completeKnapsack(n - 2, Knap, n-2);
		printf("%d\n", dp[n - 2] + n*d0);
		
	} 
	return 0;
} 





