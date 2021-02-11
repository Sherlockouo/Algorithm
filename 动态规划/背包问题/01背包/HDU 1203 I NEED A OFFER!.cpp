/*
	���⣺�� m (m <= 10000) ��ѧУ�� ��i��ѧУ��Ҫһ�ʷ��� w[i]�����һ��offer�ĸ��� p[i]��
	������ n (n <= 10000)����Ԫ��Ԥ�������£������յ�һ�� offer ���������Ƕ��٣�
	
	��⣺0/1 ����
	ת�����һ�� offer ���ղ�������С���ʣ�Ȼ������ 1 ȥ�����Ǵ���;
	�����ĸ������ת����ȡ������ĸ�����ӣ�Ȼ������� 0/1 �����ļ�ֵ��Сֵ�ˣ�
	 
*/

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ 01���� ģ�� ************************************
const int MAXN = 10010;           // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
typedef double ValueType;         // ������ֵ������ 
const ValueType inf = 10000000;   // �����ֵ����С������Сֵ����� 
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
	return x < y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity) {
	for(int i = 0; i <= maxCapacity; ++i) {
		dp[i] = (!i) ? init : inf;
	} 
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity) {
	zeroOneKnapsackInit(maxCapacity);
	for(int i = 0; i < knapsackSize; ++i) {
		for(int j = maxCapacity; j >= knap[i].capacity; --j) {
			dp[j] = opt(dp[j], dp[j - knap[i].capacity] + knap[i].weight);
		}
	}
}

//************************************ 01���� ģ�� ************************************

int main() {
	int n, m;
	
	while(scanf("%d %d", &n, &m) != EOF && (n||m)) {
		for(int i = 0; i < m; ++i) {
			int c;
			double p;
			scanf("%d %lf", &c, &p);
			Knap[i] = Knapsack(c, log10(1 - p));
		}
		zeroOneKnapsack(m, Knap, n);
		double ans = 0;
		for(int i = 0; i <= n; ++i) {
			double now = 100 - 100 * pow(10, dp[i]);
			if(now > ans) ans = now;
		}
		printf("%.1lf%%\n", ans);
	} 
	
	return 0;
}
